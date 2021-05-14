/**
 * simulator.c
 * @author pluveto <i@pluvet.com>
 */

#if !defined(__BASE_H__)
#define __BASE_H__

/**
 * @var void* 当前对象引用
 */
void *_this;

/*! \cond PRIVATE */
/**
 * @function void* 设置当前对象引用
 * @param void* obj 设置为的对象引用
 * @return void* 当前对象引用
 */
void *_o(void *obj) {
  _this = obj;
  return _this;
}
/*! \endcond */

#endif // __BASE_H__
