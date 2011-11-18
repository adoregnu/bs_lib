
#include "bs_lib_pal.h"
#include "bs_lib_debug.h"

#include "bs_lib_stack.h"

typedef struct _node_t
{
	stack_data_t data;
	struct _node_t* next;
} node_t;

static node_t *stack_top = NULL;

static node_t *new_stack_item(stack_data_t data)
{
	node_t* item = bs_malloc(sizeof(node_t));
	item->data = data;
	item->next = NULL;
}

void bs_stack_push(stack_data_t data)
{
	node_t *pre_top = NULL;

	if(NULL == stack_top)
	{
		stack_top = new_stack_item(data);
	}
	else
	{
		pre_top = stack_top;
		stack_top = new_stack_item(data);
		stack_top->next = pre_top;
	}
}

stack_data_t bs_stack_pop(void)
{
	node_t* item;
	stack_data_t data;

	if(NULL == stack_top)
		return NULL;

	item = stack_top;
	stack_top =  stack_top->next;

	data = item->data;
	bs_free(item);

	return data;
}
