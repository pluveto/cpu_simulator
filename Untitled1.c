#if !defined(__REQUIRE_H__)
#define __REQUIRE_H__

#define DEBUG true
#define private static
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * simulator.c
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__BASE_H__)
#define __BASE_H__

/**
 * @var void* ???????????
 */
void *_this;

/*! \cond PRIVATE */
/**
 * @function void* ??????????????
 * @param void* obj ??????????????
 * @return void* ???????????
 */
void *_o(void *obj) {
  _this = obj;
  return _this;
}
/*! \endcond */

#endif  // __BASE_H__

/**
 * debugger.h
 * ??????
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__DEBUGGER_H__)
#define __DEBUGGER_H__
#include <stdarg.h>
/**
 * @function debugf ????????
 * @param const char* fmt ??????????
 * @return void
 */
void debugf(const char *fmt, ...) {
#if DEBUG
  va_list vl;
  va_start(vl, fmt);
  vprintf(fmt, vl);
  va_end(vl);
#endif  // DEBUG
}

/**
 * @function releasef ???????????
 * @param const char* fmt ??????????
 * @return void
 */
void releasef(const char *fmt, ...) {
#if !DEBUG
  va_list vl;
  va_start(vl, fmt);
  vprintf(fmt, vl);
  va_end(vl);
#endif  // DEBUG
}

#endif  // __DEBUGGER_H__

/**
 * @struct _MemoryMan,MemoryMan,*pMemoryMan ?????????????壩
 */
typedef struct _MemoryMan {
  void *memory;
  int64_t size;
  struct _MemoryMan *(*init)(int64_t size);
  struct _MemoryMan *(*clean)();
  struct _MemoryMan *(*writeInt16)(int16_t data, int64_t offset);
  struct _MemoryMan *(*writeInt32)(int32_t data, int64_t offset);
  int16_t (*readInt16)(int64_t offset);
  int32_t (*readInt32)(int64_t offset);
  struct _MemoryMan *(*display)();
} MemoryMan, *pMemoryMan;

/**
 * memory_man.h
 * ?????????
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__MEMORY_MAN_H_)
#define __MEMORY_MAN_H_

/**
 * @function _memory_man_clean ???????
 * @return pMemoryMan ????????????
 */
private
pMemoryMan _memory_man_clean();

/**
 * @function _memory_man_get_this ??????????????????
 * @return pMemoryMan ????????????
 */
private
pMemoryMan _memory_man_get_this();

/**
 * @function _memory_man_init ?????????????????
 * @param int64_t size ??????С??????
 * @return pMemoryMan ????????????
 */
private
pMemoryMan _memory_man_init(int64_t size);

/**
 * @function _memory_man_read_int16 ?? 16 λ????
 * @param int64_t offset ???????????
 * @return int16_t ??????
 */
private
int16_t _memory_man_read_int16(int64_t offset);

/**
 * @function _memory_man_read_int32 ?? 32 λ????
 * @param int64_t offset ???????????
 * @return int32_t ??????
 */
private
int32_t _memory_man_read_int32(int64_t offset);

/**
 * @function _memory_man_set_int16 д 16 λ????
 * @param int16_t data ?д???????
 * @param int64_t offset ???????????
 * @return pMemoryMan ???????????
 */
private
pMemoryMan _memory_man_set_int16(int16_t data, int64_t offset);

/**
 * @function _memory_man_set_int32 д 32 λ????
 * @param int32_t data ?д???????
 * @param int64_t offset ???????????
 * @return pMemoryMan ???????????
 */
private
pMemoryMan _memory_man_set_int32(int32_t data, int64_t offset);

/**
 * @function MemoryManConstruct ??????????????
 * @return pMemoryMan ???????????
 */
pMemoryMan MemoryManConstruct();

/**
 * @function select_memory_man ??????????
 * @param pMemoryMan ins ????????????
 * @return pMemoryMan ???????????
 */
pMemoryMan select_memory_man(pMemoryMan ins);

private
pMemoryMan _memory_man_get_this() { return ((pMemoryMan)_this); }

private
pMemoryMan _memory_man_init(int64_t size) {
  debugf("memory_man: allocating memory...\n");
  void *mem = malloc(size);
  memset(mem, 0x0, size);
  _memory_man_get_this()->memory = mem;
  _memory_man_get_this()->size = size;
  return _memory_man_get_this();
}

/**
 * ???????
 */
private
pMemoryMan _memory_man_clean() {
  debugf("memory_man: cleaning memory...\n");
  void *mem = _memory_man_get_this()->memory;
  free(mem);
  return _memory_man_get_this();
}

private
pMemoryMan _memory_man_set_int32(int32_t data, int64_t offset) {
  void *mem = _memory_man_get_this()->memory;
  *((int32_t *)(((int8_t *)mem + offset))) = data;
  debugf(" * write data (%" PRId32 ") at %" PRId32 "\n", data, offset);
  return _memory_man_get_this();
}

private
pMemoryMan _memory_man_set_int16(int16_t data, int64_t offset) {
  if (offset < 16384) {
    debugf("Write to inaccessible area!\n");
    // exit(-1);
    return _memory_man_get_this();
  }
  void *mem = _memory_man_get_this()->memory;
  *((int16_t *)(((int8_t *)mem + offset))) = data;
  debugf(" * write data (%" PRId16 ") at %" PRId16 "\n", data, offset);
  return _memory_man_get_this();
}

private
int32_t _memory_man_read_int32(int64_t offset) {
  void *mem = _memory_man_get_this()->memory;
  int32_t ret = *((int32_t *)((int8_t *)mem + offset));
  return ret;
}

private
int16_t _memory_man_read_int16(int64_t offset) {
  void *mem = _memory_man_get_this()->memory;
  int16_t ret = *((int16_t *)((int8_t *)mem + offset));
  return ret;
}

/*! \cond PRIVATE */
pMemoryMan select_memory_man(pMemoryMan ins) {
  _this = ins;
  return _this;
}
/*! \endcond */

pMemoryMan MemoryManConstruct() {
  pMemoryMan ins = (pMemoryMan)malloc(sizeof(MemoryMan));
  memset(ins, 0x0, sizeof(MemoryMan));
  select_memory_man(ins);
  _memory_man_get_this()->init = _memory_man_init;
  _memory_man_get_this()->clean = _memory_man_clean;
  _memory_man_get_this()->writeInt16 = _memory_man_set_int16;
  _memory_man_get_this()->writeInt32 = _memory_man_set_int32;
  _memory_man_get_this()->readInt16 = _memory_man_read_int16;
  _memory_man_get_this()->readInt32 = _memory_man_read_int32;
  debugf("memory_man: object created!\n");
  return ins;
}

#endif  // __MEMORY_MAN_H_

/**
 * simulator.h
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__SIMULATOR_H__)
#define __SIMULATOR_H__
/**
 * @enum InstructionType ??????????
 */

enum InstructionType {
  Stop,     // ?????
  Move,     //????
  Plus,     //???
  Minus,    //???
  Times,    //???
  Over,     // ????
  And,      //?????
  Or,       //?????
  Not,      //?????
  Compare,  // ???
  Jump,     // ???
  Input,    //????
  Output    // ???
};

/**
 * @function _instruction_type_string ????????????????????????????
 * @param InstructionType type ???????
 * @return string ??????????????????
 */
static inline char *_instruction_type_string(enum InstructionType type) {
  static char *strings[] = {
      "Stop", "Move", "Plus",    "Minus", "Times", "Over",   "And",
      "Or",   "Not",  "Compare", "Jump",  "Input", "Output",
  };
  return strings[type];
}

/**
 * @struct _Registers,Registers,*pRegisters ?????????
 */
typedef struct _Registers {
  int64_t ip;  // ??????????
  int16_t flag;
  int16_t ir;  // ???????
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
 * @struct _Instruction,Instruction,*pInstruction ??????
 */
typedef struct _Instruction {
  enum InstructionType type;
  int8_t target;  //???????
  int8_t source;  //???????
  int16_t imm;    // ??????
} Instruction, *pInstruction;

/**
 * @struct _Simulator,Simulator,*pSimulator ??????????壩
 */
typedef struct _Simulator {
  char *name;
  // pnode instructions;
  pMemoryMan memoryMan;
  pRegisters registers;

  /**
   * @function Simulator->init ??????????????
   * @param char* name ????
   * @param int64_t memsize ??????С??????
   * @return pSimulator ?????????
   */
  struct _Simulator *(*init)(char *name, int64_t memsize);

  /**
   * @function Simulator->load ??????????
   * @param char* file_name ?????
   * @return pSimulator ?????????
   */
  struct _Simulator *(*load)(char *file_name);

  /**
   * @function Simulator->Display ????????
   * @return pSimulator ?????????
   */
  struct _Simulator *(*display)();
  /**
   * @function Simulator->Run ?????????
   * @return pSimulator ?????????
   */
  struct _Simulator *(*run)();
} Simulator, *pSimulator;

/**
 * @function SimulatorConstruct ??????
 * @return pSimulator ?????????
 */
pSimulator SimulatorConstruct();

/**
 * @function _simulator_get_this ???????????????
 * @return pSimulator ?????????
 */
private
pSimulator _simulator_get_this();

/**
 * @function select_simulator ???????????
 * @param pSimulator ins ??????
 * @return pSimulator ?????????
 */
pSimulator select_simulator(pSimulator ins);

/**
 * @function _simulator_init ??????????????
 * @param char* name ????
 * @param int64_t memsize ??????С??????
 * @return pSimulator ?????????
 */
private
pSimulator _simulator_init(char *name, int64_t memsize);

/**
 * @function _simulator_load ??????????
 * @param char* file_name ?????
 * @return pSimulator ?????????
 */
private
pSimulator _simulator_load(char *file_name);

/**
 * @function _simulator_run ?????????
 * @return pSimulator ?????????
 */
private
pSimulator _simulator_run();

/**
 * @function _simulator_analyze_instruction ??????????
 * @param int32_t instRaw ???? 32 λ???????
 * @return pInstruction ???????????
 */
private
pInstruction _simulator_analyze_instruction(int32_t instRaw);

/**
 * @function _simulator_execute ??????????????????????????
 * @param InstructionType type ????????
 * @param int16_t opr1 ?????? 1
 * @param int16_t opr2 ?????? 2
 * @return int16_t ??????
 */
private
bool _simulator_execute(pInstruction inst);

/**
 * @function _simulator_calculate ??????????????????????????
 * @param InstructionType type ????????
 * @param int16_t opr1 ?????? 1
 * @param int16_t opr2 ?????? 2
 * @return int16_t ??????
 */
private
int16_t _simulator_calculate(enum InstructionType type, int16_t opr1,
                             int16_t opr2);

/**
 * @function _simulator_get_register_value_by_id ??? id ??????????
 * @param int8_t id ????????
 * @return int16_t* ?????????
 */
private
int16_t *_simulator_get_register_value_by_id(int8_t id);

/**
 * @function _simulator_print_registers ??????????
 * @return pSimulator ?????????
 */
private
pSimulator _simulator_print_registers();

/**
 * @function _simulator_display ????????
 * @return pSimulator ?????????
 */
private
pSimulator _simulator_display();

/**
 * @function simulator_free ?????????????????????
 * @return void
 */
void simulator_free();

/**
 * simulator.c
 * @author pluveto <i@pluvet.com>
 */

/*! \cond PRIVATE */

private
pSimulator _simulator_get_this() { return ((pSimulator)_this); }
/*! \endcond */

/*! \cond PRIVATE */

pSimulator select_simulator(pSimulator ins) {
  _this = ins;
  return _this;
}
/*! \endcond */
private
pSimulator _simulator_print_registers() {
  pSimulator sim = _simulator_get_this();
  pRegisters regs = sim->registers;
  printf("ip = %" PRId64 "\n", regs->ip);
  printf("flag = %" PRId32 "\n", regs->flag);
  printf("ir = %" PRId32 "\n", regs->ir);
  printf("ax1 = %" PRId32 " ax2 = %" PRId32 " ax3 = %" PRId32 " ax4 = %" PRId32
         "\n",
         regs->ax1, regs->ax2, regs->ax3, regs->ax4);
  printf("ax5 = %" PRId32 " ax6 = %" PRId32 " ax7 = %" PRId32 " ax8 = %" PRId32
         "\n",
         regs->ax5, regs->ax6, regs->ax7, regs->ax8);
  debugf("m_ax5 = %" PRId16 " m_ax6 = %" PRId16 " m_ax7 = %" PRId16
         " m_ax8 = %" PRId16 "\n",
         select_memory_man(sim->memoryMan)->readInt16(regs->ax5),
         select_memory_man(sim->memoryMan)->readInt16(regs->ax6),
         select_memory_man(sim->memoryMan)->readInt16(regs->ax7),
         select_memory_man(sim->memoryMan)->readInt16(regs->ax8));
  debugf("\n");
  return select_simulator(sim);
}

private
pSimulator _simulator_init(char *name, int64_t memsize) {
  pSimulator simulator = _simulator_get_this();
  debugf("simulator: initializing...\n");
  _simulator_get_this()->name = name;

  pMemoryMan memman = _simulator_get_this()->memoryMan;
  _o(memman);
  memman->init(memsize);
  _o(simulator);
  debugf("memory size: %lld\n", memsize);
  // ??????????????
  pRegisters regs = malloc(sizeof(Registers));
  memset(regs, 0x0, sizeof(Registers));
  regs->ax1 = regs->ax2 = regs->ax3 = regs->ax4 = regs->ax5 = regs->ax6 =
      regs->ax7 = regs->ax8 = regs->flag = regs->ip = regs->ir = 0;
  _simulator_get_this()->registers = regs;
  debugf("simulator: registerd loaded:\n");
  _o(simulator);
  return _this;
}

private
pSimulator _simulator_load(char *file_name) {
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memMan = _simulator_get_this()->memoryMan;
  if (NULL == (memMan->memory)) {
    printf("Memory not initialized!");
    exit(1);
  }
  // ?????????
  debugf("simulator: loading instructions from `%s`...\n", file_name);
  FILE *file = fopen(file_name, "r");
  char ch;
  int8_t counter = 0;  // ??? bit ???????????32 ????顣
  int64_t offset = 0;    // ????????????λ? byte
  int32_t instruct = 0;  // ?????????
  while (EOF != (ch = fgetc(file))) {
    if (counter == 32) {
      // ????????
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
      // ?????????????????????????
      if (counter != 0) {
        fprintf(stderr, "Wrong length of instruction!\n");
      }
      break;
    }
  }
  fclose(file);
  return _this;
}

private
pSimulator _simulator_display() {
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memman = simulator->memoryMan;
  debugf("=========== Status ===========\n");
  debugf("Name: %s\n", simulator->name);
  debugf("Memory Size: %lld\n", memman->size);
  // ========= ???????? ==========
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
  // ========= ???????? ==========
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

// ??????
private
pInstruction _simulator_analyze_instruction(int32_t instRaw) {
  pInstruction inst = malloc(sizeof(Instruction));
  memset(inst, 0x0, sizeof(Instruction));

  // ??? ?????? bit[0-15]
  inst->imm = (instRaw << 16) >> 16;
  // ??? ???????????????????? bit[16-19] bit[20-23]
  inst->source = (instRaw << 12) >> 28;
  if (inst->source < 0) inst->source = -inst->source;
  // if (inst->source < 0 || inst->source > 8) {
  //   debugf("Failed to analize instruction: out of range (inst: %" PRId32
  //   ")\n",
  //          instRaw);
  //   exit(-1);
  // }
  inst->target = (instRaw << 8) >> 28;
  if (inst->target < 0) inst->target = -inst->target;
  // if (inst->target < 0 || inst->target > 8) {
  //   debugf("Failed to analize instruction: out of range (inst: %" PRId32
  //   ")\n",
  //          instRaw);
  //   exit(-1);
  // }
  // ??? ????????? bit[24-31]
  inst->type = instRaw >> 24;
  return inst;
}

private
int16_t *_simulator_get_register_value_by_id(int8_t id) {
  if (id == 1)
    return (int16_t *)&(_simulator_get_this()->registers->ax1);
  else if (id == 2)
    return (int16_t *)&(_simulator_get_this()->registers->ax2);
  else if (id == 3)
    return (int16_t *)&(_simulator_get_this()->registers->ax3);
  else if (id == 4)
    return (int16_t *)&(_simulator_get_this()->registers->ax4);
  else if (id == 5)
    return (int16_t *)&(_simulator_get_this()->registers->ax5);
  else if (id == 6)
    return (int16_t *)&(_simulator_get_this()->registers->ax6);
  else if (id == 7)
    return (int16_t *)&(_simulator_get_this()->registers->ax7);
  else if (id == 8)
    return (int16_t *)&(_simulator_get_this()->registers->ax8);
  return NULL;
}
private
int16_t _simulator_calculate(enum InstructionType type, int16_t opr1,
                             int16_t opr2) {
  if (type == Over && opr2 == 0) {
    debugf("What the f**k? You are dividing ZERO.");
    return -1;
  }
  if (type == Plus) return opr1 + opr2;
  if (type == Minus) return opr1 - opr2;
  if (type == Times) return opr1 * opr2;
  if (type == Over) return opr1 / opr2;
  if (type == And) return opr1 && opr2;
  if (type == Or) return opr1 || opr2;
  if (type == Not) return opr1 == 0 ? !opr2 : !opr1;
  if (type == Compare) return opr1 == opr2 ? 0 : (opr1 > opr2 ? 1 : -1);
  return 0;
}

private
int __total = 0;
// ??????
private
bool _simulator_execute(pInstruction inst) {
  __total++;
  if (__total == 200) exit(-1);
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memman = simulator->memoryMan;
  bool jumped = false;  // ???????й???????????;
  debugf(" * executing inst: (type = (%" PRId8 ") %s, target = %" PRId8
         ", source = %" PRId8 ", imm = %" PRId16 ")\n",
         inst->type, _instruction_type_string(inst->type), inst->target,
         inst->source, inst->imm);
  bool running = true;  // ??????????
  switch (inst->type) {
    case Stop:
      running = false;
      break;
    case Move: {
      if (inst->source == 0) {
        // 将一个立即数（绿色部分）传送至寄存器 x
        *_simulator_get_register_value_by_id(inst->target) = inst->imm;
        // 如果数据来自地址寄存器
      } else if (8 >= inst->source && inst->source >= 5) {
        int16_t offset = *_simulator_get_register_value_by_id(inst->source);
        int16_t value = select_memory_man(memman)->readInt16(offset);
        select_simulator(simulator);
        // 如果目标是地址寄存器
        if (8 >= inst->target && inst->target >= 5) {
          int16_t offset = *_simulator_get_register_value_by_id(inst->target);
          select_memory_man(memman)->writeInt16(value, offset);
          // 如果目标是普通寄存器
        } else {
          int16_t *target = _simulator_get_register_value_by_id(inst->target);
          // 将寄存器5（5、6、7、8号寄存器为地址寄存器）中地址所指向的内存单元（2个字节）的内容传送至寄存器1
          *target = value;
        }
        select_simulator(simulator);
        // 如果数字来自普通寄存器
      } else if (4 >= inst->source && inst->source >= 1) {
        int16_t value = *_simulator_get_register_value_by_id(inst->source);
        // 如果目标是地址寄存器
        if (8 >= inst->target && inst->target >= 5) {
          //将寄存器1的内容传送至寄存器5中地址所指向的内存单元（2个字节）5、6、7、8号寄存器为地址寄存器）。
          int16_t offset = *_simulator_get_register_value_by_id(inst->target);
          select_memory_man(memman)->writeInt16(value, offset);
        }
        //如果目标是普通寄存器
        else {
          int16_t *target = _simulator_get_register_value_by_id(inst->target);
          *target = value;
        }
        select_simulator(simulator);
      } else {
        debugf("Error: invalid instruction!");
      }
      break;
    }
    case Plus:
    case Minus:
    case Times:
    case Over:
    case And:
    case Or:
    case Not:
    case Compare: {
      int16_t value, opr1, opr2;
      if (0 == inst->target) {
        opr1 = 0;
      } else {
        opr1 = *_simulator_get_register_value_by_id(inst->target);
      }
      if (inst->target >= 5) {
        opr1 = select_memory_man(memman)->readInt16(opr1);
        select_simulator(simulator);
      }
      if (inst->source == 0) {
        opr2 = inst->imm;
      } else if (inst->source < 5) {
        opr2 = *_simulator_get_register_value_by_id(inst->target);
      } else {
        int16_t offset = *_simulator_get_register_value_by_id(inst->source);
        opr2 = select_memory_man(memman)->readInt16(offset);
      }
      int16_t result = _simulator_calculate(inst->type, opr1, opr2);
      select_simulator(simulator);
      if (inst->type == Compare) {
        int16_t *target = (int16_t *)&(_simulator_get_this()->registers->flag);
        *target = result;
        select_simulator(simulator);
        break;
      }
      if (inst->target == 0) {
        if (inst->type == Not) {
          int16_t offset = *_simulator_get_register_value_by_id(inst->source);
          select_memory_man(memman)->writeInt16(result, offset);
          select_simulator(simulator);
          break;
        }
        int16_t *target = (_simulator_get_register_value_by_id(inst->source));
        *target = result;
      } else if (inst->target <= 4) {
        int16_t *target = (_simulator_get_register_value_by_id(inst->target));
        *target = result;
      } else {
        int16_t offset = *_simulator_get_register_value_by_id(inst->target);
        select_memory_man(memman)->writeInt16(result, offset);
      }
      select_simulator(simulator);
      break;
    }
    case Jump:
      if (inst->source == 0) {
        // ?????????
        _simulator_get_this()->registers->ip += inst->imm;
        jumped = true;
      } else if (inst->source == 1) {
        // ????????????????0?????????????????????????????????????????С?
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
        debugf("Error: invalid instruction!\n");
      }
      break;
    case Input: {
      int16_t value;
      printf("in:\n");
      scanf("%" SCNd16, &value);
      if (8 >= inst->target && inst->target >= 5) {
        int16_t offset = *_simulator_get_register_value_by_id(inst->target);
        select_memory_man(memman)->writeInt16(value, offset);
      } else if (1 <= inst->target && inst->target <= 4) {
        *_simulator_get_register_value_by_id(inst->target) = value;
      } else {
        debugf("Error: invalid instruction!\n");
      }
      select_simulator(simulator);

      break;
    }
    case Output: {
      int16_t number = *_simulator_get_register_value_by_id(inst->target);
      if (inst->target >= 5) {
        number = select_memory_man(memman)->readInt16(number);
      }
      printf("out: ");
      printf("%d\n", number);
      select_simulator(simulator);
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

// ???????
private
pSimulator _simulator_run() {
  pSimulator simulator = _simulator_get_this();
  pMemoryMan memman = simulator->memoryMan;
  bool stopFlag = false;
  // ???????????
  while (!stopFlag) {
    // ????
    int64_t offset = simulator->registers->ip;

    int32_t instRaw = select_memory_man(memman)->readInt32(offset);
    select_simulator(simulator);
    simulator->registers->ir = instRaw >> 16;
    // ???????
    pInstruction inst = _simulator_analyze_instruction(instRaw);
    // ??????
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
  pMemoryMan memman = MemoryManConstruct();
  select_simulator(ins);
  _simulator_get_this()->memoryMan = memman;
  select_simulator(ins);
  debugf("simulator: object created!\n");
  return ins;
}

#endif  // __SIMULATOR_H__

#endif  // __REQUIRE_H__

/**
 * @define MEMORY_SIZE 模拟电脑的内存大小
 */

#define MEMORY_SIZE (32 * 1024)

int main(int argc, char **argv) {
  pSimulator simulator = SimulatorConstruct();
  simulator->init("Simulator I", MEMORY_SIZE);
  simulator->load("dict.dic");
  simulator->run();
  simulator->display();
  simulator_free(simulator);
  return 0;
}
