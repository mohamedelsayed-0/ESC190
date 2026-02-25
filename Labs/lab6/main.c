#include "LL.h"
#include <stdio.h>

static void print_list(const LL *my_list) {
    node *cur = my_list->head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main(void) {
    int data_arr[] = {1, 2, 3, 4, 5};
    int expected[] = {0, 1, 99, 3, 4, 5, 6};
    LL *my_list = NULL;

    create_LL_from_data(&my_list, data_arr, 5);
    LL_append(my_list, 6);
    LL_insert(my_list, 0, 0);
    LL_insert(my_list, 99, 3);
    LL_insert(my_list, 7, my_list->size);

    LL_delete(my_list, 2);
    LL_delete(my_list, my_list->size - 1);

    printf("Final list: ");
    print_list(my_list);

    if (my_list->size != 7) {
        printf("failed: expected size 7, got %d\n", my_list->size);
        LL_free_all(my_list);
        return 1;
    }

    for (int i = 0; i < my_list->size; i++) {
        int value = LL_get_rec(my_list, i);
        if (value != expected[i]) {
            printf("failed at index %d: expected %d, got %d\n", i, expected[i], value);
            LL_free_all(my_list);
            return 1;
        }
    }

    printf("tests passed.\n");
    LL_free_all(my_list);
    return 0;
}
