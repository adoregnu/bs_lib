
#if !defined(__BS_LIB_STACK_H__)
#define __BS_LIB_STACK_H__

typedef void* stack_data_t;

EXTERN void  bs_stack_push(stack_data_t data);
EXTERN stack_data_t bs_stack_pop(void);

#endif /*__BS_LIB_STACK_H__*/
