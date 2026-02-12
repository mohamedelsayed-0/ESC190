#include "intlist.h"
#include <stdlib.h>

/* from intlist_common.c */
void shift_right(IntList *list, int index);
void shift_left(IntList *list, int index);

static void ensure_capacity_double(IntList *list) {
    if (list->size < list->capacity) return;

    int new_cap = (list->capacity <= 0) ? 1 : (list->capacity * 2);
    int *tmp = realloc(list->data, new_cap * (int)sizeof(int));
    if (!tmp) return;  /* leave unchanged if realloc fails */

    list->data = tmp;
    list->capacity = new_cap;
}

void list_append(IntList *list, int new_elem) {
    ensure_capacity_double(list);
    list->data[list->size] = new_elem;
    list->size += 1;
}

void list_insert(IntList *list, int new_elem, int index) {
    if (index < 0 || index > list->size) return;

    ensure_capacity_double(list);

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
}
