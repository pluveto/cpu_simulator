#if !defined(__REQUIRE_H__)
#define __REQUIRE_H__

#define DEBUG false
#define private static
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type/base.h"
#include "type/debugger.h"

/**
 * @struct _MemoryMan,MemoryMan,*pMemoryMan 内存管理器类（结构体）
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


#include "type/memory_man.h"
#include "type/simulator.h"

#endif // __REQUIRE_H__

