#include "intlist.h"
#include <stdlib.h>
#include <string.h>

//Q1a Shared shift helpers (memmove is required because ranges overlap) 
void shift_right(IntList *list, int index) {
    if (index < 0 || index > list->size) return;
    memmove(&list->data[index + 1],
            &list->data[index],
            (list->size - index) * (int)sizeof(int));
}

void shift_left(IntList *list, int index) {
    if (index < 0 || index >= list->size) return;
    memmove(&list->data[index],
            &list->data[index + 1],
            (list->size - index - 1) * (int)sizeof(int));
}

/* Common functions required by intlist.h */
void create_list_from_data(IntList **p_IntList, int *data_arr, int size) {
    IntList *list = malloc(sizeof(IntList));
    if (!list) { *p_IntList = NULL; return; }

    list->size = size;
    list->capacity = (size > 0) ? size : 1;

    list->data = malloc(list->capacity * sizeof(int));
    if (!list->data) {
        free(list);
        *p_IntList = NULL;
        return;
    }

    if (size > 0) {
        memmove(list->data, data_arr, size * sizeof(int));
    }

    *p_IntList = list;
}

int list_get(IntList *list, int index) {
    return list->data[index];
}

void list_destroy(IntList *list) {
    if (!list) return;
    free(list->data);
    free(list);
}
