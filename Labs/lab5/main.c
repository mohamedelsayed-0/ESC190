#include "intlist.h"
#include <stdio.h>

static void print_list(const IntList *list) {
    printf("size=%d cap=%d : ", list->size, list->capacity);
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main(void) {
    int init_data[] = {10, 20, 30};
    IntList *list = NULL;

    create_list_from_data(&list, init_data, 3);
    if (!list) {
        printf("Failed to create list\n");
        return 1;
    }

    print_list(list);

    list_append(list, 40);
    print_list(list);

    /* Put breakpoint on the next line for the TA demo */
    list_insert(list, 99, 1);
    print_list(list);

    list_delete(list, 2);
    print_list(list);

    printf("get index 1 = %d\n", list_get(list, 1));

    list_destroy(list);
    return 0;
}
