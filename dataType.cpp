#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum dataType {
   TYPE_INT = 0,
   TYPE_CHAR
}dataType;

typedef struct arr_obj {
   void *ptr;
   dataType type;
} arr_obj;

arr_obj *arr_obj_create(size_t size){
   arr_obj *new_arr = (arr_obj*) malloc(sizeof(arr_obj) * size);
   return new_arr;
}

void push_arr(arr_obj *arr, void *ptr, dataType type, size_t idx){
   arr[idx].ptr = ptr;
   arr[idx].type = type;
}

int main() {
   arr_obj *arr = arr_obj_create(12);
   int *ptr = (int*) malloc(sizeof(int));
   *ptr = 10;

   push_arr(arr, (void*)ptr, TYPE_INT, 0);

   printf("%d\n", *((int*)arr[0].ptr));

   return 0;
}