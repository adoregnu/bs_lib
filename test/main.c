
#include "bs_lib_pal.h"
#include "bs_lib_avl.h"

#include "bs_lib_debug.h"


int32_t compare_func(avl_node_data_t arg1, avl_node_data_t arg2)
{
	if((int32_t)arg1 < (int32_t)arg2)
		return -1;
	else if((int32_t)arg1 > (int32_t)arg2)
		return 1;
	else 
		return 0;
}

int32_t main()
{
	bs_avl_t avl;

	bs_debug("bs_lib test!! \n");

	bs_avl_init(&avl, compare_func);

	bs_avl_insert(&avl, 'a');
	bs_avl_insert(&avl, 'z');
	bs_avl_insert(&avl, 's');
	bs_avl_insert(&avl, 't');

	bs_avl_deinit(&avl);
	return 0;
}
