
#if !defined(__BS_LIB_AVL_H__)
#define __BS_LIB_AVL_H__

typedef u_int32_t avl_data_t;
typedef int32_t (*compare_func_t)(avl_data_t arg1, avl_data_t arg2);

typedef struct _bs_avl_t
{
	void* root;
	compare_func_t compare;
}bs_avl_t;

typedef int32_t (*trevers_func_t)(bs_avl_t *avl);

EXTERN void bs_avl_init(bs_avl_t* avl, compare_func_t comp);
EXTERN void bs_avl_deinit(bs_avl_t* avl);
EXTERN int32_t bs_avl_insert(bs_avl_t* avl, avl_data_t data);
EXTERN int32_t bs_avl_remove(bs_avl_t* avl, avl_data_t data);
EXTERN avl_data_t bs_avl_search(bs_avl_t* avl, avl_data_t data);

EXTERN void bs_avl_trevers(bs_avl_t* avl);
#endif /*__BS_LIB_AVL_H__*/
