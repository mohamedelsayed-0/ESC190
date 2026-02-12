#include "intlist.h"
#include <stdlib.h>

/* from intlist_common.c */
void shift_right(IntList *list, int index);
void shift_left(IntList *list, int index);

static void grow_by_one_if_full(IntList *list) {
    if (list->size < list->capacity) return;

    int new_cap = (list->capacity <= 0) ? 1 : (list->capacity + 1);
    int *tmp = realloc(list->data, new_cap * (int)sizeof(int));
    if (!tmp) return;

    list->data = tmp;
    list->capacity = new_cap;
}

static void shrink_by_two_if_possible(IntList *list) {
    if (list->capacity <= 1) return;
    if (list->size > list->capacity / 2) return;

    int new_cap = list->capacity / 2;
    if (new_cap < 1) new_cap = 1;

    int *tmp = realloc(list->data, new_cap * (int)sizeof(int));
    if (!tmp) return;

    list->data = tmp;
    list->capacity = new_cap;
}

void list_append(IntList *list, int new_elem) {
    grow_by_one_if_full(list);
    list->data[list->size] = new_elem;
    list->size += 1;
}

void list_insert(IntList *list, int new_elem, int index) {
    if (index < 0 || index > list->size) return;

    grow_by_one_if_full(list);

    if (index < list->size) {
        shift_right(list, index);
    }

    list->data[index] = new_elem;
    list->size += 1;
}

void list_delete(IntList *list, int index) {
    if (index < 0 || index >= list->size) return;

    if (index < list->size - 1) {
        shift_left(list, index);
    }

    list->size -= 1;
    shrink_by_two_if_possible(list);
}
