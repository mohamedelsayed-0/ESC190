#include <stdio.h>
#include <ctype.h>

//Q1
void set_even_to_zero(int *block, int size) {
    for (int i = 0; i < size; i += 2) {
        block[i] = 0;
    }
}

// Q2
void cat(char *dest, const char *src) {
    int i = 0;
    int j = 0;
    while (dest[i] != '\0') {
        i++;
    }
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

void cat2(char *dest, const char *src) {
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// Q3
int my_strcmp_rec(const char *s1, const char *s2) {
    if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0') {
        return (unsigned char)*s1 - (unsigned char)*s2;
    }
    return my_strcmp_rec(s1 + 1, s2 + 1);
}

/* Q4
def binary_search_deluxe_right(L, target):
    left = 0
    right = len(L) - 1
    while left <= right:
        mid = (left + right) // 2
        if L[mid] <= target:
            left = mid + 1
        else:
            right = mid - 1
    return right
     # should be logn
 */

// Q5
int my_atoi(char *str) {
    int number = 0;
    for (int i = 0; isdigit((unsigned char)str[i]); i++) {
        number = number * 10 + (str[i] - '0');
    }
    return number;
}

// main
int main() {
    // Q1
    int arr[] = {7, 6, 6, 7};
    set_even_to_zero(arr, 4);
    for (int i = 0; i < 4; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Q2
    char a[50] = "six ";
    char b[] = "or seven";
    cat(a, b);
    printf("%s\n", a);

    // Q5
    int c = my_atoi("123");
    printf("%d\n", c);

    return 0;
}
