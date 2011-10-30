
#if !defined(__BS_LIB_PAL_H__)
#define __BS_LIB_PAL_H__

#include "bs_lib_types.h"

#define max(a, b) ((a>b) ? (a) : (b))

EXTERN void* bs_malloc(int32_t size);
EXTERN void bs_free(void* ptr);
EXTERN void* bs_memset(void *src, int32_t init_val, int32_t size);

#endif  /*__BS_LIB_PAL_H__*/
