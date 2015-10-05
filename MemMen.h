#ifndef MEMMEN_H
#define MEMMEN_H
#include <stdlib.h>

#define SIZE_TOP 20000

void *my_malloc(void * top, size_t size);
void *my_realloc(void * top, void *ptr, size_t size);
void my_free(void *ptr);

#endif // MEMMEN_H
