#include "LL.h"

#include <stdlib.h>

void create_node(node **p_n, int data) {
    *p_n = (node *)malloc(sizeof(node));
    (*p_n)->next = NULL;
    (*p_n)->data = data;
}

void create_LL_from_data(LL **p_LL, int *data_arr, int size) {
    (*p_LL) = (LL *)malloc(sizeof(LL));
    (*p_LL)->head = NULL;
    (*p_LL)->size = 0;

    node *cur = NULL;
    for (int i = 0; i < size; i++) {
        node *n;
        create_node(&n, data_arr[i]);
        if (cur == NULL) {
            (*p_LL)->head = n;
        } else {
            cur->next = n;
        }
        cur = n;
        (*p_LL)->size++;
    }
}

void LL_append(LL *my_list, int new_elem) {
    node *n;
    create_node(&n, new_elem);

    if (my_list->head == NULL) {
        my_list->head = n;
        my_list->size++;
        return;
    }

    node *cur = my_list->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = n;
    my_list->size++;
}

void LL_insert(LL *my_list, int new_elem, int index) {
    if (index < 0 || index > my_list->size) {
        return;
    }

    node *n;
    create_node(&n, new_elem);

    if (index == 0) {
        n->next = my_list->head;
        my_list->head = n;
        my_list->size++;
        return;
    }

    node *cur = my_list->head;
    for (int i = 0; i < index - 1; i++) {
        cur = cur->next;
    }

    n->next = cur->next;
    cur->next = n;
    my_list->size++;
}

void LL_delete(LL *my_list, int index) {
    if (index < 0 || index >= my_list->size || my_list->head == NULL) {
        return;
    }

    if (index == 0) {
        node *to_delete = my_list->head;
        my_list->head = to_delete->next;
        free(to_delete);
        my_list->size--;
        return;
    }

    node *cur = my_list->head;
    for (int i = 0; i < index - 1; i++) {
        cur = cur->next;
    }

    node *to_delete = cur->next;
    cur->next = to_delete->next;
    free(to_delete);
    my_list->size--;
}

void LL_free_all(LL *my_list) {
    node *cur = my_list->head;
    while (cur != NULL) {
        node *next = cur->next;
        free(cur);
        cur = next;
    }
    free(my_list);
}

static int LL_get_rec_helper(node *cur, int index) {
    if (index == 0) {
        return cur->data;
    }
    return LL_get_rec_helper(cur->next, index - 1);
}

int LL_get_rec(LL *my_list, int index) {
    if (index < 0 || index >= my_list->size) {
        return 0;
    }
    return LL_get_rec_helper(my_list->head, index);
}
