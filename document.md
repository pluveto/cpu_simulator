#### type/simulator.h

|类型|名称|说明|参数|返回值|
|---|---|---|---|---|
|函数|`_instruction_type_string`|指令类型枚举字符串形式（用于调试）|**type**: 类型: `InstructionType` <br> 指令类型<br><br>|返回值类型: `string` <br>指令类型枚举字符串形式<br><br>|
|函数|`_simulator_get_this`|获取当前模拟器对象||返回值类型: `pSimulator` <br>模拟器引用<br><br>|
|函数|`select_simulator`|选取模拟器对象|**ins**: 类型: `pSimulator` <br> 所选实例<br><br>|返回值类型: `pSimulator` <br>模拟器引用<br><br>|
|函数|`_simulator_init`|初始化模拟器对象|**name**: 类型: `char*` <br> 名称<br><br>**memsize**: 类型: `int64_t` <br> 内存空间大小（字节）<br><br>|返回值类型: `pSimulator` <br>模拟器引用<br><br>|
|函数|`_simulator_load`|载入指令文件|**file_name**: 类型: `char*` <br> 文件名<br><br>|返回值类型: `pSimulator` <br>模拟器引用<br><br>|
|函数|`_simulator_run`|运行模拟器||返回值类型: `pSimulator` <br>模拟器引用<br><br>|
|函数|`_simulator_analyze_instruction`|分析一条指令|**32**: 类型: `指令的` <br> 位整数表示<br><br>|返回值类型: `pInstruction` <br>指令结构体的引用<br><br>|
|函数|`_simulator_execute`|运算型指令处理（即返回运算结果）|**type**: 类型: `InstructionType` <br> 指令的类型<br><br>**操作数**: 类型: `opr1` <br> 1<br><br>**操作数**: 类型: `opr2` <br> 2<br><br>|返回值类型: `int16_t` <br>运算结果<br><br>|
|函数|`_simulator_calculate`|运算型指令处理（即返回运算结果）|**type**: 类型: `InstructionType` <br> 指令的类型<br><br>**操作数**: 类型: `opr1` <br> 1<br><br>**操作数**: 类型: `opr2` <br> 2<br><br>|返回值类型: `int16_t` <br>运算结果<br><br>|
|函数|`_simulator_get_register_value_by_id`|通过 id 取寄存器引用|**id**: 类型: `int8_t` <br> 寄存器编号<br><br>|返回值类型: `int16_t*` <br>寄存器引用<br><br>|
|函数|`_simulator_print_registers`|打印寄存器状态||返回值类型: `pSimulator` <br>模拟器引用<br><br>|
|函数|`_simulator_display`|打印内存状态||返回值类型: `pSimulator` <br>模拟器引用<br><br>|
|函数|`simulator_free`|释放模拟器和寄存器占用的内存||返回值类型: `void` <br><br><br>|

#### type/debugger.h

|类型|名称|说明|参数|返回值|
|---|---|---|---|---|
|函数|`debugf`|调试时打印|**fmt**: 类型: `char*` <br> 要打印的内容<br><br>|返回值类型: `void` <br><br><br>|
|函数|`releasef`|正式发行时打印|**fmt**: 类型: `char*` <br> 要打印的内容<br><br>|返回值类型: `void` <br><br><br>|

#### type/base.h

|类型|名称|说明|参数|返回值|
|---|---|---|---|---|
|函数|`void*`|设置当前对象引用|**obj**: 类型: `void*` <br> 设置为的对象引用<br><br>|返回值类型: `void*` <br>当前对象引用<br><br>|

#### type/memory_man.h

|类型|名称|说明|参数|返回值|
|---|---|---|---|---|
|函数|`_memory_man_clean`|清理内存||返回值类型: `pMemoryMan` <br>内存管理器引用<br><br>|
|函数|`_memory_man_get_this`|获取当前内存管理器引用||返回值类型: `pMemoryMan` <br>内存管理器引用<br><br>|
|函数|`_memory_man_init`|初始化内存管理器对象|**size**: 类型: `int64_t` <br> 内存空间大小（字节）<br><br>|返回值类型: `pMemoryMan` <br>内存管理器引用<br><br>|
|函数|`_memory_man_read_int16`|读 16 位整数|**offset**: 类型: `int64_t` <br> 偏移量（字节）<br><br>|返回值类型: `int16_t` <br>读取结果<br><br>|
|函数|`_memory_man_read_int32`|读 32 位整数|**offset**: 类型: `int64_t` <br> 偏移量（字节）<br><br>|返回值类型: `int32_t` <br>读取结果<br><br>|
|函数|`_memory_man_set_int16`|写 16 位整数|**data**: 类型: `int16_t` <br> 要写入的数据<br><br>**offset**: 类型: `int64_t` <br> 偏移量（字节）<br><br>|返回值类型: `pMemoryMan` <br>当前对象引用<br><br>|
|函数|`_memory_man_set_int32`|写 32 位整数|**data**: 类型: `int32_t` <br> 要写入的数据<br><br>**offset**: 类型: `int64_t` <br> 偏移量（字节）<br><br>|返回值类型: `pMemoryMan` <br>当前对象引用<br><br>|
|函数|`MemoryManConstruct`|内存管理器构造函数||返回值类型: `pMemoryMan` <br>当前对象引用<br><br>|
|函数|`select_memory_man`|选取内存管理器|**ins**: 类型: `pMemoryMan` <br> 要选取的对象引用<br><br>|返回值类型: `pMemoryMan` <br>当前对象引用<br><br>|

