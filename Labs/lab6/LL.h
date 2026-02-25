#if !defined(LL_H)
#define LL_H

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct LL {
    node *head;
    int size;
} LL;

void create_node(node **p_n, int data);

void create_LL_from_data(LL **p_LL, int *data_arr, int size);

void LL_append(LL *my_list, int new_elem);
void LL_insert(LL *my_list, int new_elem, int index);
void LL_delete(LL *my_list, int index);
void LL_free_all(LL *my_list);
int LL_get_rec(LL *my_list, int index);

#endif
