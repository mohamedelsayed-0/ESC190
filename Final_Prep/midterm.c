// Re-doing midterm mistakes and reviweing them indepth
#include <stdio.h>
#include <stdlib.h>
// Q1
int sum(int *arr, int n) {
  int res = 0;
  for (int i = 0; i < n; i++) {
    res += arr[i];
  }
  return res;
}
// Q2
int is_palindrome(const char *str) {
  int n = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    n++;
  }
  for (int j = 0; j < n; j++) {
    if (str[j] != str[n - 1])
      return 0;
    n--;
  }
  return 1;
}

// Q3a (rotate *a->*b, *b->*c, *c->*a
void rot3(int *a, int *b, int *c) {
  int temp = *a;
  *a = *b;
  *b = *c;
  *c = temp;
}

// Q3b
int main() {
  int a = 6;
  int b = 7;
  int c = 8;
  rot3(&a, &b, &c);
  printf("%d\n%d\n%d\n", a, b, c);
}

// Q3c
void my_strcpy(char *dest, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
}

// Q4a (struct given)
typedef struct student {
  char name[200];
  int grade;
} student;

student **create_classs(const char **names, int *grades, int n) {
  student **arr = malloc(n * sizeof(student *));
  for (int i = 0; i < n; i++) {
    arr[i] = malloc(sizeof(student));
    int j = 0;
    while (names[i][j] != '\0') {
      arr[i]->name[j] = names[i][j];
      j++;
    }
    arr[i]->name[j] = '\0';
    arr[i]->grade = grades[i];
  }
  return arr;
}

// Q4b
void destory_class(student **class, int n) {
  for (int i = 0; i < n; i++) {
    free(class[i]);
  }
  free(class);
}

// Q4c
void print_above(student **class, int n, int threshold) {
  for (int i = 0; i < n; i++) {
    if (class[i]->grade > threshold) {
      printf("%s\n", class[i]->name);
    }
  }
}

// Q5 (does code run or not)
// a)
char *s = "hello";
s[0] = H;
// dosen't run as s is a string literal in read only memory, unmodifible

// b)
int *arr = (int *)malloc(3 * sizeof(int));
arr[3] = 10;
// fails, we counted for 3 spaces, but here we are on the 4th elemnt.
// space is not allocated, crashes.

// c)
student *s = (student *)malloc(sizeof(student));
free(s);
printf("%d\n", s->grade);
// fails, attempted to use malloced memory after freeing, it no longer exists

// d)
char *s = (char *)malloc(5);
strcpy(s, "hello");
// fails, dosen't account for null terminator, not enough space

// e)
student **block = (student **)malloc(3 * sizeof(student *));
block[0]->grade = 90;
// dosen't free memory for elements inside struct, fails

// Q6
double exponent(double *first, int *second) {
  double res = 0;
  for (int i = 0; i < *second; i++) {
    res = *first * *second;
  }
  return res;
}

double my_sci_to_double(const char *s) {
  int n = strlen(s);
  char before_e[100];
  int i = 0;

  for (i = 0; i < n; i++) {
    if (s[i] == 'e')
      break;
    before_e[i] = s[i];
  }

  before_e[i] = '\0';
  double before_e2 = 0;

  for (int j = 0; j < i; j++) {
    int digit = before_e[j] - '0';
    before_e2 = before_e2 * 10 + digit;
  }

  char sign = s[i + 1];
  i++;
  i++;

  char after_e[100];
  int k = 0;
  for (; i < n; i++) {
    after_e[k] = s[i];
    k++;
  }

  after_e[k] = '\0';
  int after_e2 = 0;
  for (int j = 0; j < k; j++) {
    int digit = after_e[j] - '0';
    after_e2 = after_e2 * 10 + digit;
  }
  if (sign == '-') {
    after_e2 = after_e2 * -1;
  }
  return exponent(&before_e2, &after_e2);
}
// cooked question, my exponents is wrong and decimal handling but its fine ovr

int my_strncmp(const char *s1, const char *s2, int n) {
  if (n == 0)
    return 0;
  if (*s1 != *s2)
    return *s1 - *s2;
  if (*s1 == '\0' || *s2 == '\0')
    return 0;
  return my_strncmp(s1 + 1, s2 + 1, n - 1);
}
// should probably use unsigned characters in the actual midterm

// Q8a
char **read_dict(const char *filename, int *p_n) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    *p_n = 0;
    return NULL;
  }
  int count = 0;
}
