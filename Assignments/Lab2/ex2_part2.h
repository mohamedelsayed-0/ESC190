#ifndef EX2_PART2_H
#define EX2_PART2_H

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap();
void insert(MinHeap *h, int key);
int pop(MinHeap *h);

#endif