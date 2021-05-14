/**
 * memory_man.h
 * 内存管理模块
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__MEMORY_MAN_H_)
#define __MEMORY_MAN_H_

#include "../require.h"


/**
 * @function _memory_man_clean 清理内存
 * @return pMemoryMan 内存管理器引用
 */
private pMemoryMan _memory_man_clean();

/**
 * @function _memory_man_get_this 获取当前内存管理器引用
 * @return pMemoryMan 内存管理器引用
 */
private pMemoryMan _memory_man_get_this();

/**
 * @function _memory_man_init 初始化内存管理器对象
 * @param int64_t size 内存空间大小（字节）
 * @return pMemoryMan 内存管理器引用
 */
private pMemoryMan _memory_man_init(int64_t size);

/**
 * @function _memory_man_read_int16 读 16 位整数
 * @param int64_t offset 偏移量（字节）
 * @return int16_t 读取结果
 */
private int16_t _memory_man_read_int16(int64_t offset);

/**
 * @function _memory_man_read_int32 读 32 位整数
 * @param int64_t offset 偏移量（字节）
 * @return int32_t 读取结果
 */
private int32_t _memory_man_read_int32(int64_t offset);

/**
 * @function _memory_man_set_int16 写 16 位整数
 * @param int16_t data 要写入的数据
 * @param int64_t offset 偏移量（字节）
 * @return pMemoryMan 当前对象引用
 */
private pMemoryMan _memory_man_set_int16(int16_t data, int64_t offset);

/**
 * @function _memory_man_set_int32 写 32 位整数
 * @param int32_t data 要写入的数据
 * @param int64_t offset 偏移量（字节）
 * @return pMemoryMan 当前对象引用
 */
private pMemoryMan _memory_man_set_int32(int32_t data, int64_t offset);

/**
 * @function MemoryManConstruct 内存管理器构造函数
 * @return pMemoryMan 当前对象引用
 */
pMemoryMan MemoryManConstruct();

/**
 * @function select_memory_man 选取内存管理器
 * @param pMemoryMan ins 要选取的对象引用
 * @return pMemoryMan 当前对象引用
 */
pMemoryMan select_memory_man(pMemoryMan ins);

#include "memory_man.h"

private pMemoryMan _memory_man_get_this() { return ((pMemoryMan)_this); }

private pMemoryMan _memory_man_init(int64_t size) {
  debugf("memory_man: allocating memory...\n");
  void *mem = malloc(size);
  memset(mem, 0x0, size);
  _memory_man_get_this()->memory = mem;
  _memory_man_get_this()->size = size;
  return _memory_man_get_this();
}

/**
 * 清理内存
 */
private pMemoryMan _memory_man_clean() {
  debugf("memory_man: cleaning memory...\n");
  void *mem = _memory_man_get_this()->memory;
  free(mem);
  return _memory_man_get_this();
}

private pMemoryMan _memory_man_set_int32(int32_t data, int64_t offset) {
  void *mem = _memory_man_get_this()->memory;
  *((int32_t *)(((int8_t *)mem + offset))) = data;
  debugf(" * write data (%" PRId32 ") at %" PRId32 "\n", data, offset);
  return _memory_man_get_this();
}

private pMemoryMan _memory_man_set_int16(int16_t data, int64_t offset) {
  void *mem = _memory_man_get_this()->memory;
  *((int16_t *)(((int8_t *)mem + offset))) = data;
  debugf(" * write data (%" PRId16 ") at %" PRId16 "\n", data, offset);
  return _memory_man_get_this();
}

private int32_t _memory_man_read_int32(int64_t offset) {
  void *mem = _memory_man_get_this()->memory;
  int32_t ret = *((int32_t *)((int8_t *)mem + offset));
  return ret;
}

private int16_t _memory_man_read_int16(int64_t offset) {
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
