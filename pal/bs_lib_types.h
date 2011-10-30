
#if !defined(__BS_LIB_TYPES_H__)
#define __BS_LIB_TYPES_H__

#if defined(EXTERN)
#undef EXTERN
#endif

#if defined(_cplusplus)
#define EXTERN extern "C"
#else /*_cplusplus*/
#define EXTERN
#endif /*!_cplusplus*/

#if !defined(__GNUC__)
typedef char int8_t;
typedef unsigned char u_int8_t;
typedef short int16_t;
typedef unsigned short u_int16_t;
typedef int int32_t;
typedef unsigned int u_int32_t;
#else /*__GNUC__*/
#include <sys/types.h>
#endif /*!__GNUC__*/

#endif /*__BS_LIB_TYPES_H__*/
