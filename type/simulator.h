/**
 * simulator.h
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__SIMULATOR_H__)
#define __SIMULATOR_H__

#include "../require.h"
#include "memory_man.h"
/**
 * @enum InstructionType 指令类型枚举
 */

enum InstructionType {
  Stop,     // 停止执行
  Move,     //传送
  Plus,     //加法
  Minus,    //剪发
  Times,    //乘法
  Over,     // 除法
  And,      //逻辑与
  Or,       //逻辑或
  Not,      //逻辑非
  Compare,  // 比较
  Jump,     // 跳转
  Input,    //输入
  Output    // 输出
};

/**
 * @function _instruction_type_string 指令类型枚举字符串形式（用于调试）
 * @param InstructionType type 指令类型
 * @return string 指令类型枚举字符串形式
 */
static inline char *_instruction_type_string(enum InstructionType type) {
  static char *strings[] = {
      "Stop", "Move", "Plus",    "Minus", "Times", "Over",   "And",
      "Or",   "Not",  "Compare", "Jump",  "Input", "Output",
  };
  return strings[type];
}

/**
 * @struct _Registers,Registers,*pRegisters 寄存器结构体
 */
typedef struct _Registers {
  int64_t ip;  // 指令指针寄存器
  int16_t flag;
  int16_t ir;  // 指令寄存器
  int16_t ax1;
  int16_t ax2;
  int16_t ax3;
  int16_t ax4;
  int16_t ax5;
  int16_t ax6;
  int16_t ax7;
  int16_t ax8;
} Registers, *pRegisters;

/**
 * @struct _Instruction,Instruction,*pInstruction 指令结构体
 */
typedef struct _Instruction {
  enum InstructionType type;
  int8_t target;  //目标寄存器
  int8_t source;  //源头寄存器
  int16_t imm;    // 立即数
} Instruction, *pInstruction;

/**
 * @struct _Simulator,Simulator,*pSimulator 模拟器类（结构体）
 */
typedef struct _Simulator {
  char *name;
  // pnode instructions;
  pMemoryMan memoryMan;
  pRegisters registers;

  /**
   * @function Simulator->init 初始化模拟器对象
   * @param char* name 名称
   * @param int64_t memsize 内存空间大小（字节）
   * @return pSimulator 模拟器引用
   */
  struct _Simulator *(*init)(char *name, int64_t memsize);

  /**
   * @function Simulator->load 载入指令文件
   * @param char* file_name 文件名
   * @return pSimulator 模拟器引用
   */
  struct _Simulator *(*load)(char *file_name);

  /**
   * @function Simulator->Display 打印内存状态
   * @return pSimulator 模拟器引用
   */
  struct _Simulator *(*display)();
  /**
   * @function Simulator->Run 运行模拟器
   * @return pSimulator 模拟器引用
   */
  struct _Simulator *(*run)();
} Simulator, *pSimulator;

/**
 * @function SimulatorConstruct 构造函数
 * @return pSimulator 模拟器引用
 */
pSimulator SimulatorConstruct();

/**
 * @function _simulator_get_this 获取当前模拟器对象
 * @return pSimulator 模拟器引用
 */
private pSimulator _simulator_get_this();

/**
 * @function select_simulator 选取模拟器对象
 * @param pSimulator ins 所选实例
 * @return pSimulator 模拟器引用
 */
pSimulator select_simulator(pSimulator ins);

/**
 * @function _simulator_init 初始化模拟器对象
 * @param char* name 名称
 * @param int64_t memsize 内存空间大小（字节）
 * @return pSimulator 模拟器引用
 */
private pSimulator _simulator_init(char *name, int64_t memsize);

/**
 * @function _simulator_load 载入指令文件
 * @param char* file_name 文件名
 * @return pSimulator 模拟器引用
 */
private pSimulator _simulator_load(char *file_name);

/**
 * @function _simulator_run 运行模拟器
 * @return pSimulator 模拟器引用
 */
private pSimulator _simulator_run();

/**
 * @function _simulator_analyze_instruction 分析一条指令
 * @param int32_t instRaw 指令的 32 位整数表示
 * @return pInstruction 指令结构体的引用
 */
private pInstruction _simulator_analyze_instruction(int32_t instRaw);

/**
 * @function _simulator_execute 运算型指令处理（即返回运算结果）
 * @param InstructionType type 指令的类型
 * @param int16_t opr1 操作数 1
 * @param int16_t opr2 操作数 2
 * @return int16_t 运算结果
 */
private bool _simulator_execute(pInstruction inst);

/**
 * @function _simulator_calculate 运算型指令处理（即返回运算结果）
 * @param InstructionType type 指令的类型
 * @param int16_t opr1 操作数 1
 * @param int16_t opr2 操作数 2
 * @return int16_t 运算结果
 */
private int16_t _simulator_calculate(enum InstructionType type, int16_t opr1,
                             int16_t opr2);

/**
 * @function _simulator_get_register_value_by_id 通过 id 取寄存器引用
 * @param int8_t id 寄存器编号
 * @return int16_t* 寄存器引用
 */
private int16_t *_simulator_get_register_value_by_id(int8_t id);

/**
 * @function _simulator_print_registers 打印寄存器状态
 * @return pSimulator 模拟器引用
 */
private pSimulator _simulator_print_registers();

/**
 * @function _simulator_display 打印内存状态
 * @return pSimulator 模拟器引用
 */
private pSimulator _simulator_display();

/**
 * @function simulator_free 释放模拟器和寄存器占用的内存
 * @return void
 */
void simulator_free();

/**
 * simulator.c
 * @author pluveto <i@pluvet.com>
 */

#include "simulator.h"
/*! \cond PRIVATE */

private pSimulator _simulator_get_this() { return ((pSimulator)_this); }
/*! \endcond */

/*! \cond PRIVATE */

pSimulator select_simulator(pSimulator ins) {
  _this = ins;
  return _this;
}
/*! \endcond */
private pSimulator _simulator_print_registers() {
  pRegisters regs = _simulator_get_this()->registers;
  printf("ip = %" PRId64 "\n", regs->ip);
  printf("flag = %" PRId32 "\n", regs->flag);
  printf("ir = %" PRId32 "\n", regs->ir);
  printf("ax1 = %" PRId32 " ax2 = %" PRId32 " ax3 = %" PRId32 " ax4 = %" PRId32
         "\n",
         regs->ax1, regs->ax2, regs->ax3, regs->ax4);
  printf("ax5 = %" PRId32 " ax6 = %" PRId32 " ax7 = %" PRId32 " ax8 = %" PRId32
         "\n",
         regs->ax5, regs->ax6, regs->ax7, regs->ax8);
  debugf("\n");
  return _simulator_get_this();
}

private pSimulator _simulator_init(char *name, int64_t memsize) {
  pSimulator simulator = _simulator_get_this();
  debugf("simulator: initializing...\n");
  _simulator_get_this()->name = name;
  // 初始化内存管理器
  pMemoryMan memman = _simulator_get_this()->memoryMan;
  _o(memman);
  memman->init(memsize);
  _o(simulator);
  debugf("memory size: %lld\n", memsize);
  // 初始化寄存器序列
  pRegisters regs = malloc(sizeof(Registers));
  memset(regs, 0x0, sizeof(Registers));
  regs->ax1 = regs->ax2 = regs->ax3 = regs->ax4 = regs->ax5 = regs->ax6 =
      regs->ax7 = regs->ax8 = regs->flag = regs->ip = regs->ir = 0;
  _simulator_get_this()->registers = regs;
  debugf("simulator: registerd loaded:\n");
  _o(simulator);
  return _this;
}

private pSimulator _simulator_load(char *file_name) {
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memMan = _simulator_get_this()->memoryMan;
  if (NULL == (memMan->memory)) {
    printf("Memory not initialized!");
    exit(1);
  }
  // 读取指令文件
  debugf("simulator: loading instructions from `%s`...\n", file_name);
  FILE *file = fopen(file_name, "r");
  char ch;
  int8_t counter = 0;    // 读取 bit 循环计数器。32 个一组。
  int64_t offset = 0;    // 内存偏移量，单位为 byte
  int32_t instruct = 0;  // 指令的整数值
  while (EOF != (ch = fgetc(file))) {
    if (counter == 32) {
      // 完成一轮读取
      select_memory_man(memMan);
      memMan->writeInt32(instruct, offset);
      select_simulator(simulator);
      debugf("---> %" PRId32 "\n", instruct);
      if (instruct == 0) {
        debugf("simulator: instructions loaded.\n");
        break;
      }
      offset += 4;
      instruct = 0;
      counter = 0;
    }
    if (ch == '0' || ch == '1') {
      debugf("%c", ch);
      instruct = (instruct << 1) + ((int)ch - '0');
      counter++;

      if (!(counter % 8)) {
        debugf(" ");
      }
    } else if (isspace(ch)) {
      continue;
    } else {
      // 如果读到非命令字符，就停止读取
      if (counter != 0) {
        fprintf(stderr, "Wrong length of instruction!\n");
      }
      break;
    }
  }
  fclose(file);
  return _this;
}

private pSimulator _simulator_display() {
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memman = simulator->memoryMan;
  debugf("=========== Status ===========\n");
  debugf("Name: %s\n", simulator->name);
  debugf("Memory Size: %lld\n", memman->size);
  // ========= 打印代码段 ==========
  printf("\ncodeSegment :\n");

  debugf("range: [0, 512): \n");
  int counter = 0;
  select_memory_man(memman);
  for (int64_t i = 0; i < 512 / 4; i++) {
    int32_t byte_offset = i * 4;
    int32_t value = memman->readInt32(byte_offset);
    printf("%" PRId32, value);
    if (counter == 7) {
      counter = 0;
      printf("\n");
    } else {
      printf(" ");
      counter++;
    }
  }
  select_simulator(simulator);
  // ========= 打印数据段 ==========
  printf("\ndataSegment :\n");
  int32_t data_seg_print_range = memman->size / 2 + 512;

  debugf("range: [%d, %d): \n", memman->size / 2, data_seg_print_range);
  counter = 0;
  select_memory_man(memman);
  for (int64_t i = memman->size / 2 / 2; i < data_seg_print_range / 2; i++) {
    int32_t byte_offset = i * 2;
    int32_t value = memman->readInt16(byte_offset);
    printf("%" PRId16, value);
    if (counter == 15) {
      counter = 0;
      printf("\n");
    } else {
      printf(" ");
      counter++;
    }
  }
  select_simulator(simulator);

  return _this;
}

// 指令分析
private pInstruction _simulator_analyze_instruction(int32_t instRaw) {
  pInstruction inst = malloc(sizeof(Instruction));
  memset(inst, 0x0, sizeof(Instruction));

  // 取出 立即数 bit[0-15]
  inst->imm = (instRaw << 16) >> 16;
  // 取出 源寄存器编号和目标寄存器编号 bit[16-19] bit[20-23]
  inst->source = (instRaw << 12) >> 28;
  inst->target = (instRaw << 8) >> 28;
  // 取出 指令类型编号 bit[24-31]
  inst->type = instRaw >> 24;
  return inst;
}

private int16_t *_simulator_get_register_value_by_id(int8_t id) {
  if (id == 1)
    return (int16_t *)&_simulator_get_this()->registers->ax1;
  else if (id == 2)
    return (int16_t *)&_simulator_get_this()->registers->ax2;
  else if (id == 3)
    return (int16_t *)&_simulator_get_this()->registers->ax3;
  else if (id == 4)
    return (int16_t *)&_simulator_get_this()->registers->ax4;
  else if (id == 5)
    return (int16_t *)&_simulator_get_this()->registers->ax5;
  else if (id == 6)
    return (int16_t *)&_simulator_get_this()->registers->ax6;
  else if (id == 7)
    return (int16_t *)&_simulator_get_this()->registers->ax7;
  else if (id == 8)
    return (int16_t *)&_simulator_get_this()->registers->ax8;
  return NULL;
}
private int16_t _simulator_calculate(enum InstructionType type, int16_t opr1,
                             int16_t opr2) {
  if (type == Plus) return opr1 + opr2;
  if (type == Minus) return opr1 - opr2;
  if (type == Times) return opr1 * opr2;
  if (type == Over) return opr1 / opr2;
  if (type == And) return opr1 && opr2;
  if (type == Or) return opr1 || opr2;
  if (type == Not) return !opr1;
  if (type == Compare) return opr1 == opr2 ? 0 : (opr1 > opr2 ? 1 : -1);
  return 0;
}

private int __total = 0;
// 指令执行
private bool _simulator_execute(pInstruction inst) {
  __total++;
  if (__total == 200) exit(-1);
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memman = simulator->memoryMan;
  bool jumped = false;  // 是否在执行过程中已经跳转;
  debugf(" * executing inst: (type = (%" PRId8 ") %s, target = %" PRId8
         ", source = %" PRId8 ", imm = %" PRId16 ")\n",
         inst->type, _instruction_type_string(inst->type), inst->target,
         inst->source, inst->imm);
  bool running = true;  // 是否退出程序
  switch (inst->type) {
    case Stop:
      running = false;
      break;
    case Move:
      if (inst->source == 0) {
        // 将一个立即数（绿色部分）传送至寄存器 x
        *_simulator_get_register_value_by_id(inst->target) = inst->imm;
      } else if (8 >= inst->source && inst->source >= 5) {
        int16_t offset = *_simulator_get_register_value_by_id(inst->source);
        int16_t value = select_memory_man(memman)->readInt16(offset);
        select_simulator(simulator);
        int16_t *target = _simulator_get_register_value_by_id(inst->target);
        // 将寄存器5（5、6、7、8号寄存器为地址寄存器）中地址所指向的内存单元（2个字节）的内容传送至寄存器1
        *target = value;
      } else if (8 >= inst->target && inst->target >= 5) {
        //将寄存器1的内容传送至寄存器5中地址所指向的内存单元（2个字节）5、6、7、8号寄存器为地址寄存器）。
        int16_t value = *_simulator_get_register_value_by_id(inst->source);
        int16_t offset = *_simulator_get_register_value_by_id(inst->target);
        select_memory_man(memman)->writeInt16(value, offset);
        select_simulator(simulator);
      } else {
        debugf("Error: invalid instruction!");
      }
      break;
    case Plus:
    case Minus:
    case Times:
    case Over:
    case And:
    case Or:
    case Not:
    case Compare:
      if (inst->source == 0) {
        // 将寄存器1内的数与一个立即数（绿色部分）相加，结果保存至寄存器1
        int16_t value = *_simulator_get_register_value_by_id(inst->target);
        *_simulator_get_register_value_by_id(inst->target) =
            _simulator_calculate(inst->type, value, inst->imm);
      } else if (8 >= inst->source && inst->source >= 5) {
        int16_t offset = *_simulator_get_register_value_by_id(inst->source);
        int16_t value = inst->type == Not
                            ? 0
                            : select_memory_man(memman)->readInt16(offset);
        select_simulator(simulator);
        int16_t *target =
            inst->type == Compare
                ? (int16_t *)&_simulator_get_this()->registers->flag
                : _simulator_get_register_value_by_id(inst->target);
        // 将寄存器5（5、6、7、8号寄存器为地址寄存器）中地址所指向的内存单元（2个字节）的内容传送至寄存器1
        int16_t opr1 = *_simulator_get_register_value_by_id(inst->target);
        *target = _simulator_calculate(inst->type, opr1, value);

        debugf("new value in register: %d\n", *target);
      } else {
        debugf("Error: invalid instruction!");
      }
      break;
    case Jump:
      if (inst->source == 0) {
        // 无条件跳转
        _simulator_get_this()->registers->ip += inst->imm;
        jumped = true;
      } else if (inst->source == 1) {
        // 如果标志寄存器内的值为0则转移至程序计数器加一个立即数（绿色部分）处执行。
        if (0 == _simulator_get_this()->registers->flag) {
          _simulator_get_this()->registers->ip += inst->imm;
          jumped = true;
        }
      } else if (inst->source == 2) {
        if (1 == _simulator_get_this()->registers->flag) {
          _simulator_get_this()->registers->ip += inst->imm;
          jumped = true;
        }
      } else if (inst->source == 3) {
        if (-1 == _simulator_get_this()->registers->flag) {
          _simulator_get_this()->registers->ip += inst->imm;
          jumped = true;
        }
      } else {
        debugf("Error: invalid instruction!");
      }
      break;
    case Input: {
      int16_t number;
      printf("in:\n");
      scanf("%d", &number);
      *_simulator_get_register_value_by_id(inst->target) = number;
      break;
    }
    case Output: {
      int16_t number = *_simulator_get_register_value_by_id(inst->target);
      printf("out: ");
      printf("%d\n", number);
      break;
    }
    default:
      break;
  }
  if (!jumped) {
    _simulator_get_this()->registers->ip += 4;
  }

  free(inst);
  return running;
}

// 正式运行
private pSimulator _simulator_run() {
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memman = simulator->memoryMan;
  bool stopFlag = false;
  // 指令执行主循环
  while (!stopFlag) {
    // 取指令
    int64_t offset = simulator->registers->ip;

    int32_t instRaw = select_memory_man(memman)->readInt32(offset);
    select_simulator(simulator);
    simulator->registers->ir = instRaw >> 16;
    // 分析指令
    pInstruction inst = _simulator_analyze_instruction(instRaw);
    // 执行指令
    stopFlag = !_simulator_execute(inst);

    _simulator_print_registers();
  }
  return _this;
}

void simulator_free(pSimulator simulator) {
  free(simulator->registers);
  free(simulator);
  return;
}
pSimulator SimulatorConstruct() {
  pSimulator ins = (pSimulator)malloc(sizeof(Simulator));
  memset(ins, 0x0, sizeof(Simulator));
  select_simulator(ins);
  _simulator_get_this()->init = _simulator_init;
  _simulator_get_this()->display = _simulator_display;
  _simulator_get_this()->run = _simulator_run;
  _simulator_get_this()->load = _simulator_load;
  _simulator_get_this()->memoryMan = MemoryManConstruct();
  select_simulator(ins);
  debugf("simulator: object created!\n");
  return ins;
}


#endif  // __SIMULATOR_H__

