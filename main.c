#include <stdio.h>
#include "MemMen.h"

int main(void)
{
    void *top = malloc(SIZE_TOP);

    int i = 0;
    int c_arr_size = 10;
    int i_arr_size = 20;
    int d_arr_size = 2250;
    char *ptr = (char*)my_malloc(top, c_arr_size);
    int *ptr1 = (int*)my_malloc(top, i_arr_size * sizeof(int));
    double *ptrd = (double*)my_malloc(top, d_arr_size * sizeof(double));

    if (ptr == NULL)
    {
        printf("Error ptr - NULL pointer\n");
    }
    else
    {
        for (i = 0; i < c_arr_size - 2; i++)
        {
            //  fill array with A, B, C, D, etc
            ptr[i] = 65 + i;
        }
        ptr[c_arr_size - 1] = '\0';
        printf("char* address - %d    val - %s\n", ptr, ptr);
        i = 0;
    }

    if (ptr1 == NULL)
    {
        printf("Error ptr1 - NULL pointer\n");
    }
    else
    {
        while (i < i_arr_size)
        {
            ptr1[i] = i;
            printf("int* address - %d    val - %d\n", &ptr1[i], ptr1[i]);
            i++;
        }
    }

    if (ptrd == NULL)
    {
        printf("Error ptdr - NULL pointer\n");
    }
    else
    {
        printf("double* begin ptdr - %d  end ptrd - %d\n", &ptrd[0], &ptrd[d_arr_size]);
    }

    my_free(ptr1);
    my_free(ptrd);

    //  making integer array size 15 for looking where in memory it will be located
    i_arr_size = 15;
    ptr1 = (int*)my_malloc(top, i_arr_size * sizeof(int));

    if (ptr1 == NULL)
    {
        printf("Error ptr1 - NULL pointer\n");
    }
    else
    {
        i = 0;
        while (i < i_arr_size)
        {
            ptr1[i] = i;
            printf("int* address - %d    val - %d\n", &ptr1[i], ptr1[i]);
            i++;
        }
    }

    //  return size to 20 for realloc use, to see where it will be located
    //  this value of ptr1 must be the same as ptr1 at the beggining of programm
    i_arr_size = 20;
    ptr1 = (int*)my_realloc(top, ptr1, i_arr_size * sizeof(int));

    if (ptr1 == NULL)
    {
        printf("Error ptr1 - NULL pointer\n");
    }
    else
    {
        i = 0;
        printf("After called realloc\n");
        while (i < i_arr_size)
        {
            ptr1[i] = i;
            printf("int* address - %d    val - %d\n", &ptr1[i], ptr1[i]);
            i++;
        }
    }

    my_free(ptr);
    my_free(ptr1);

    //  after deleting char pointer and integer pointer try to put there array of char with the same size as both of them
    //  10 bytes + 4 * 20 bytes == 90 bytes
    c_arr_size = 90;
    ptr = (char*)my_malloc(top, c_arr_size * sizeof(char));

    if (ptr == NULL)
    {
        printf("Error ptr - NULL pointer\n");
    }
    else
    {
        for (i = 0; i < c_arr_size - 2; i++)
        {
            ptr[i] = 'A';
        }
        ptr[c_arr_size - 1] = '\0';
        printf("char* address - %d    val - %s\n", ptr, ptr);
    }

    //  try to alloc memory witch is bigger then SIZE_TOP == 20000
    //  current memory have 90 bytes alloceted
    //  2500 * 8 + 90 > 20000 bytes
    d_arr_size = 2500;
    ptrd = (double *)my_malloc(top, d_arr_size * sizeof(double));

    if (ptrd == NULL)
    {
        printf("Error ptdr - NULL pointer\n");
    }
    else
    {
        printf("double* begin ptdr - %d  end ptrd - %d\n", &ptrd[0], &ptrd[d_arr_size]);
    }

    my_free(ptrd);

    //  begging and the end of our heap
    printf("begin - %10d\n  end - %10d\n", top, (char*)top + SIZE_TOP);

    free(top);
    return 0;
}
