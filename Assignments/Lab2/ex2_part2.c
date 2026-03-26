#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap* createHeap() {
    MinHeap *h = malloc(sizeof(MinHeap));
    if (h == NULL) return NULL;

    h->capacity = 3;
    h->size = 0;
    h->data = malloc(h->capacity * sizeof(int));

    if (h->data == NULL) {
        free(h);
        return NULL;
    }

    return h;
}

void insert(MinHeap *h, int key) {
    if (h == NULL || key < 0) return;

    if (h->size == h->capacity) {
        h->capacity *= 2;
        int *new_data = realloc(h->data, h->capacity * sizeof(int));
        if (new_data == NULL) return;
        h->data = new_data;
    }

    h->data[h->size] = key;
    int i = h->size;
    h->size++;

    // sift up
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[parent] <= h->data[i]) break;

        swap(&h->data[parent], &h->data[i]);
        i = parent;
    }
}

int pop(MinHeap *h) {
    if (h == NULL || h->size == 0) return -1;

    int min_val = h->data[0];
    h->size--;

    if (h->size == 0) return min_val;

    h->data[0] = h->data[h->size];

    int i = 0;

    // sift down
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if (left < h->size && h->data[left] < h->data[smallest])
            smallest = left;

        if (right < h->size && h->data[right] < h->data[smallest])
            smallest = right;

        if (smallest == i) break;

        swap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }

    return min_val;
}

int main() {
    MinHeap *h = createHeap();

    insert(h, 27);
    insert(h, 89);
    insert(h, 29);
    insert(h, 13);
    insert(h, 83);
    insert(h, 48);
    insert(h, 9);
    insert(h, 50);
    insert(h, 2);
    insert(h, 26);

    for (int i = 0; i < 11; i++) {
        printf("%d\n", pop(h));
    }

    free(h->data);
    free(h);
    return 0;
}