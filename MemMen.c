#include "MemMen.h"
#include <stdio.h>

struct map
{
    void *pointer;
    size_t size;
};

struct map dataStruct[SIZE_TOP];
int count = -1;
int usedSpace = 0;

void *my_malloc(void *top, size_t size)
{
    int findFirstZero = 0;
    int findFirstNotZero = 0;
    count++;
    if (size > SIZE_TOP - usedSpace)
                return NULL;
    if (count > 0)
    {
        while (dataStruct[findFirstZero].size != 0) findFirstZero++;
        while (dataStruct[findFirstNotZero].size == 0) findFirstNotZero++;

        if (dataStruct[0].size == 0)
        {
            if (size > (char*)dataStruct[findFirstNotZero].pointer - (char*)dataStruct[findFirstZero].pointer)
                return NULL;
        }
        else
        {
            if (count > findFirstZero && size > (char*)dataStruct[count].pointer - (char*)dataStruct[findFirstZero].pointer)
            {
                return NULL;
            }
        }
        dataStruct[findFirstZero].pointer = (char*)dataStruct[count - 1].pointer + dataStruct[count - 1].size;
        dataStruct[findFirstZero].size = size;
        usedSpace += size;
        return dataStruct[findFirstZero].pointer;
    }
    else
    {
        dataStruct[count].pointer = top;
        dataStruct[count].size = size;
        usedSpace += size;
        return dataStruct[count].pointer;
    }

    if (dataStruct[count].pointer > (char*)top + SIZE_TOP)
        return NULL;

}

void my_free(void *ptr)
{
    int i = 0;
    int n = 0;
    if (ptr == NULL) return;
    count--;
    while (ptr != dataStruct[n].pointer)
    {
        n++;
    }
    usedSpace -= dataStruct[n].size;
    dataStruct[n].size = 0;
}

void *my_realloc(void *top, void *ptr, size_t size)
{
    int i = 0;
    int n = 0;
    void *temp = ptr;
    void *temp2;
    while (ptr != dataStruct[n].pointer)
    {
        n++;
    }

    if (dataStruct[n + 1].pointer != NULL)
    {
        temp2 = dataStruct[n + 1].pointer;
    }
    else
    {
        my_free(ptr);
        return my_malloc(top, size);
    }

    while(temp != dataStruct[n + 1].pointer)
    {
        temp = (char*)temp + 1;
        i++;
    }

    if (i >= size)
    {
        my_free(ptr);
        return my_malloc(top, size);
    }
}
