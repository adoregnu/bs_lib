
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bs_lib_pal.h"

void* bs_malloc(int32_t _size)
{
	return malloc(_size);
}

void bs_free(void* _ptr)
{
	free(_ptr);
}

void* bs_memset(void* _src, int32_t _set_val, int32_t _size)
{
	return memset(_src, _set_val, _size);
}
