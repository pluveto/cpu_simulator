import glob
import os
import sys

outtype = ["function"]
titleprefix = "#### "


def getDoc(result):
    if not result['type'] in outtype:
        return ""

    s = ""
    if result['type'] == "none":
        return s
    if result['type'] == "struct":
        s = s + "|结构体|"
        s = s + "`" + result['normal'][0] + "`|"
        s = s + result['normal'][1] + "|"
        s = s + "/|/|"
    if result['type'] == "enum":
        s = s + "|枚举|"
        s = s + "`" + result['normal'][0] + "`|"
        s = s + result['normal'][1] + "|"
        s = s + "/|/|"
    if result['type'] == "define":
        s = s + "|宏定义|"
        s = s + "`" + result['normal'][0] + "`|"
        s = s + result['normal'][1] + "|"
        s = s + "/|/|"
    if result['type'] == "function":
        s = s + "|函数|"
        s = s + "`" + result['func'][0] + "`|"
        s = s + result['func'][1] + "|"
        for param in result['param']:
            s = s + \
                ("**{1}**: 类型: `{0}` <br> {2}<br><br>").format(
                    param[0], param[1], param[2])
        s = s + "|"
        s = s + \
            "返回值类型: `{}` <br>{}<br><br>".format(
                result['ret'][0], result['ret'][1]) + "|"
    return s+"\n"


cwd = os.getcwd()

print('---------------------------------')
print("  文档生成器 - by pluveto")
print("  工作目录：" + cwd)
print('---------------------------------')

files = glob.glob(cwd + "/**/*.*", recursive=True)
out = open("document.md", "w")

print("发现文件：")
for fn in files:
    print("\t." + fn[len(cwd):])


for fn in files:
    flag = False
    fd = open(fn, "r")

    docType = "none"
    func = []
    normal = []
    param = []
    ret = []
    title = (titleprefix + "{0}\n\n".format(fn[len(cwd)+1:]))

    lineNum = 1

    head = ('|类型|名称|说明|参数|返回值|\n|---|---|---|---|---|\n')

    alldoc = ""
    while True:
        line = fd.readline()

        if not line:
            break

        lineNum = lineNum + 1

        if line.startswith("/**"):
            flag = True
            continue
        elif flag and line.lstrip().startswith("*/"):
            result = {
                "type": docType,
                "func": func,
                "normal": normal,
                "param": param,
                "ret": ret
            }
            doc = getDoc(result)
            if (len(doc)):
                alldoc = alldoc + (doc)

            docType = "none"
            func = []
            normal = []
            param = []
            ret = []
            flag = False
            continue

        if not flag:
            continue
        try:
            line = line.strip(' \t\n\r*')
            if line.startswith("@struct"):
                docType = "struct"
                line = line.split(" ", 2)
                normal = ([line[1], line[2]])
                continue
            if line.startswith("@enum"):
                docType = "enum"
                line = line.split(" ", 2)
                normal = ([line[1], line[2]])
                continue
            if line.startswith("@define"):
                docType = "define"
                line = line.split(" ", 2)
                normal = ([line[1], line[2]])
                continue
            if line.startswith("@function"):
                docType = "function"
                line = line.split(" ", 2)
                func.append(line[1])
                func.append(line[2])
                continue
            if line.startswith("@param"):
                line = line.rsplit(" ", 3)
                param.append([line[1], line[2], line[3]])
                continue
            if line.startswith("@return"):
                line = line.split(" ", 3)
                if line[1] == "void":
                    ret = ([line[1], ""])
                else:
                    ret = ([line[1], line[2]])
                continue
            pass
        except:
            print("Unexpected error:", sys.exc_info()[
                  0], "file: ", fn, " line: ", lineNum)
    if (len(alldoc)):
        out.write(title + head + alldoc + "\n")
    fd.close()
out.close()

print("处理完毕！")
