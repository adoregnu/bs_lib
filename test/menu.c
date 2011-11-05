
#include "bs_lib_pal.h"
#include "bs_lib_avl.h"
#include "bs_lib_debug.h"

#include "menu.h"

typedef int32_t (*menu_fn_t)(u_int32_t arg);

int32_t  avl_test(u_int32_t arg1);

menu_fn_t menu_fn[] = 
{
	avl_test,
};

int32_t compare_func(avl_node_data_t arg1, avl_node_data_t arg2)
{
	if((int32_t)arg1 < (int32_t)arg2)
		return -1;
	else if((int32_t)arg1 > (int32_t)arg2)
		return 1;
	else 
		return 0;
}

int32_t avl_test(u_int32_t arg1)
{
	int32_t i;

	bs_avl_t avl;
	avl_node_data_t data;

	bs_debug("avl tree test!! \n");
	srand(0);

	bs_avl_init(&avl, compare_func);

	for(i = 0;  i <= 100; i++)
	{
		bs_avl_insert(&avl, rand()%100 + 1);
	}
	bs_avl_trevers(&avl);

	data = bs_avl_search(&avl, 55);
	if(data == 0)
	{
		bs_debug("not found!!\n");
	}

	bs_avl_remove(&avl, 9);
	bs_avl_trevers(&avl);

	bs_avl_deinit(&avl);

	return 0;
}

int32_t process_menu(int32_t choice)
{
	return menu_fn[choice](0);
}

int32_t menu(void)
{
	process_menu(0);

	return 0;
}

