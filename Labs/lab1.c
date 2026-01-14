#include <stdio.h>

// Q2
void setter(int *p_a) {
    *p_a = 10;
}

// Q3
void arrchanger(char *arr) {
    arr[0] = 'x';
}

// Q4
void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// Q5
int length(const char *s) {
    int count = 0;
    while (s[count] != '\0') count++;
    return count; // O(n)
}

// Q6
void seq_replace(int *arr1, unsigned long arr1_sz,
                 int *arr2, unsigned long arr2_sz) {
    if (arr2_sz == 0 || arr2_sz > arr1_sz) return;

    for (unsigned long i = 0; i + arr2_sz <= arr1_sz; i++) {
        int match = 1;
        for (unsigned long j = 0; j < arr2_sz; j++) {
            if (arr1[i + j] != arr2[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            for (unsigned long j = 0; j < arr2_sz; j++) {
                arr1[i + j] = 0;
            }
        }
    }
}

int main(void) {
    // Q2
    int a = 5;
    printf("Before: %d\n", a);
    setter(&a);
    printf("After: %d\n\n", a);

    // Q3
    char arr[100] = "abc";
    arrchanger(arr);
    printf("new array: %s\n\n", arr);

    // Q4 (EXACT assignment code)
    int i = 0;
    int a2[5] = {5, 2, 4, 6, 3};   
    for(i = 0; i < 5; i++){
        printf("%d\n", a2[i]);
    }
    i = 0;
    while(i < 5){
        printf("%d\n", a2[i]);
        i++; // same as i = i + 1
    }
 
    // Q5
    printf("Length: %d\n\n", length(arr));

    // Q6
    int c[] = {5, 6, 7, 8, 6, 7};
    int b[] = {6, 7};
    seq_replace(c, 6, b, 2);
    for (int x = 0; x < 6; x++) {
        printf("%d\n", c[x]);
    }

    return 0;
}
