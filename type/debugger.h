/**
 * debugger.h
 * 调试器
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__DEBUGGER_H__)
#define __DEBUGGER_H__
#include <stdarg.h>
/**
 * @function debugf 调试时打印
 * @param const char* fmt 要打印的内容
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
 * @function releasef 正式发行时打印
 * @param const char* fmt 要打印的内容
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
