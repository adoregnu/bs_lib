
#include "bs_lib_pal.h"

#include "bs_lib_avl.h"
#include "bs_lib_debug.h"

typedef struct _avl_node_t
{
	avl_node_data_t data;
	struct _avl_node_t *left_child;
	struct _avl_node_t *right_child;
} avl_node_t;

static avl_node_t* bs_avl_rotate_ll(avl_node_t* parent)
{
	avl_node_t *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;

	return child;
}

static avl_node_t* bs_avl_rotate_rr(avl_node_t* parent)
{
	avl_node_t *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;

	return child;
}

static avl_node_t* bs_avl_rotate_lr(avl_node_t* parent)
{
	avl_node_t *child = parent->left_child;

	parent->left_child = bs_avl_rotate_rr(child);
	return bs_avl_rotate_ll(parent);
}

static avl_node_t* bs_avl_rotate_rl(avl_node_t* parent)
{
	avl_node_t *child = parent->right_child;

	parent->right_child = bs_avl_rotate_ll(child);
	return bs_avl_rotate_rr(parent);
}

static int32_t bs_avl_get_height(avl_node_t* node)
{
	if(NULL == node)
		return 0;

	return 1 + max(bs_avl_get_height(node->left_child), 
				bs_avl_get_height(node->right_child));
}

static int32_t bs_avl_get_balance(avl_node_t* node)
{
	if(NULL == node)
	{
		return 0;
	}
	return bs_avl_get_height(node->left_child) - 
			bs_avl_get_height(node->right_child);
}

static avl_node_t* bs_avl_rebalance(avl_node_t *root)
{
	avl_node_t *node = root;
	int32_t height_diff = bs_avl_get_balance(root);

	if(height_diff > 1)
	{
		if(bs_avl_get_balance(node->left_child) > 0)
		{
			node = bs_avl_rotate_ll(root);
		}
		else
		{
			node = bs_avl_rotate_lr(root);
		}
	}
	else if(height_diff < -1)
	{
		if(bs_avl_get_balance(node->right_child) < 0)
		{
			node = bs_avl_rotate_rr(root);
		}
		else
		{
			node = bs_avl_rotate_rl(root);
		}
	}

	return node;
}

static avl_node_t* bs_avl_insert_new_node(
	bs_avl_t* avl, 
	avl_node_t *parent, 
	avl_node_data_t data)
{
	avl_node_t *new_node = NULL;

	if(NULL == avl || NULL == avl->compare)
	{
		return NULL;
	}

	if(NULL == parent)
	{
		new_node = (avl_node_t*)bs_malloc(sizeof(avl_node_t));
		if(NULL == new_node)
		{
			bs_debug("Failed to allocate memory!\n");
			return NULL;
		}
		new_node->left_child = NULL;
		new_node->right_child = NULL;
		new_node->data = data;
		//bs_debug("insert %c  \n", (int8_t)data);
		return new_node;
	}
	else if(avl->compare(parent->data, data) < 0)
	{
		//bs_debug("parent->data[%c] < data[%c] \n", parent->data, data);
		parent->right_child = 
			bs_avl_insert_new_node(avl,  parent->right_child, data);
		return bs_avl_rebalance(parent);
	}
	else if(avl->compare(parent->data, data) > 0)
	{
		//bs_debug("parent->data[%c] > data[%c] \n", parent->data, data);
		parent->left_child = 
			bs_avl_insert_new_node(avl, parent->left_child, data);
		return bs_avl_rebalance(parent);
	}
	else
	{
		bs_debug("same data!! \n");
	}

	return NULL;
}


/**
 */
int32_t bs_avl_insert(bs_avl_t* avl, avl_node_data_t data)
{
	avl->root = (void*)bs_avl_insert_new_node(avl, 
						(avl_node_t*)avl->root, data);
	//bs_debug("root:%p\n", avl->root);

	if(NULL == avl->root) 
		return -1;

	return 0;
}

static avl_node_data_t avl_search_node(bs_avl_t* avl, avl_node_t* root, avl_node_data_t data)
{
	if(NULL == root)
		return (avl_node_data_t)0;

	if(avl->compare(root->data, data) < 0)
	{
		avl_search_node(avl, root->right_child, data);
	}
	else if(avl->compare(root->data, data) > 0)
	{
		avl_search_node(avl, root->left_child, data);
	}
	else
	{
		return root->data;
	}
}

avl_node_data_t bs_avl_search(bs_avl_t* avl, avl_node_data_t data)
{
	return avl_search_node(avl, (avl_node_t*)avl->root, data);
}

int32_t bs_avl_remove(bs_avl_t* avl, avl_node_data_t data)
{
	return 0;
}

static void avl_trevers_node(avl_node_t* root)
{
	if(root == NULL) 
		return;

	avl_trevers_node(root->left_child);

	bs_debug("%d ", root->data);

	avl_trevers_node(root->right_child);
}

void bs_avl_trevers(bs_avl_t* avl)
{
	avl_node_t *root = (avl_node_t *)avl->root;
	avl_trevers_node(root);

	bs_debug("\n");
}


void bs_avl_init(bs_avl_t* avl, compare_func_t comp)
{
	bs_memset(avl, 0, sizeof(bs_avl_t));
	avl->compare = comp;
	avl->root = NULL;
}

static void avl_free_node(avl_node_t *root)
{
	if(root == NULL)
		return;

	avl_free_node(root->left_child);
	avl_free_node(root->right_child);
	bs_free(root);
}

void bs_avl_deinit(bs_avl_t* avl)
{
	avl_node_t* node;
	if(NULL == avl->root)
	{
		return ;
	}

	avl_free_node((avl_node_t*)avl->root);
}

