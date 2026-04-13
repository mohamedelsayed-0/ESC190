#include <stdio.h>
#include <stdlib.h>
// Implemntations done in lecture - C
//  note this wont actually run cuz i have multiple mains

/*
LECTURE 5: more on arrays and pointer arithmetic
*/
// Swapping 2 pointers (came up on midterm)

void swap(int *p_a, int *p_b) {
  int temp = *p_a; // Create a temp variable in local frame
  *p_a = *p_b;
  *p_b = temp;
}

int main() {
  int x = 7;
  int y = 8;
  swap(&x, &y);

  return 0;
}

// strings can be stored as pointers
char *str = "hello";
printf("%c\n", str[1]); // prints 'e'
// here even tho our variable is of type char, C treats it as an array
// an equivelent formulation would be:
char *str_2 = "hello";
printf("%c\n", *(str_2 + 1));

// When we have multiple oeprations we perform what is in the parentheses
//  first (similar to PEMDAS). Therefore, this code tells us
//  to get the value of str, which is the address that holds the character 'h',
//  then increase it by 1 byte (which is the address that holds the next
//  character, 'e'). Finally, the dereferencing operator gets the value stored
//  at the address str + 1.

// in C we have heap memory and stack memory
// stack is the localframework while heap is theoverall memory table
// since a stacks memory no longer exists after a function ends, we cant return
// a pointer to a local variable
// this is why we use malloc to allocate memory in the heap
// example:
int *make_array_wrong() {
  int arr[5] = {1, 2, 3, 4, 5};
  return arr;
}
// here stack frame is destroyed, arr memory is gone
// but if we use malloc:

#include <stdio.h>
#include <stdlib.h>

int *make_array_right() {
  int *a = (int *)malloc(5 * sizeof(int));
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  a[3] = 4;
  a[4] = 5;

  return a;
}
int main() {
  int *a_good = make_array_right();
  printf("%d", a_good[0]);

  free(a_good);
}
// a is still a local variable here, but its memory dosent go away

/*
LECTURE 8: Double Pointers
Suppose we wish to make a function that constructs an array of integers from an
input. We need a double pointer because we can describe an array using its
address, and we need the address to this address such that we can actually
modify it. We can implement it the following way:
*/
void get_int_arr_from_input(int **p_arr, int *p_n) {
  printf("Number of elements that are coming: ");
  scanf("%d", p_n);                           // n
  *p_arr = (int *)malloc(*p_n * sizeof(int)); // allocate arr
  for (int i = 0; i < *p_n; i++) {
    scanf("%d",
          &(*p_arr)[i]); // essentially &arr[i], what we insert into the array
  }
}

int main() {
  int *arr;
  int n;
  get_int_arr_from_input(&arr, &n);
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }

  free(arr);
}

/*
LECTURE 10: Memory Model for Structures & Header Files
Practice excersises
*/
// Excersise 1:
// Consider the following code. What's going to happen?
// a) Nothing happens.
// b) It crashes.
// C) The name gets changed to "abc"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student1 {
  char name[5];
  int f;
} student1;

void set_name1a(student1 s) { strcpy(s.name, "abc"); }

int main() {
  student1 s1;
  set_name1a(s1);
}
// ANSWER: a) ; nothing happens since we passed by value not by pointer

// Excersise 2:
// Consider the following code. What's going to happen?
// a) Nothing happens.
// b) It crashes.
// c) The name gets changed to "abc"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student2 {
  char *name;
  int f;
} student2;

void set_name2b(student2 s) {
  s.name = (char *)malloc(5); // issue is here, malloced copy of var
  strcpy(s.name, "abc");
} // here once the func ends, destoryed -> not freed -> mem leak

int main() {
  student2 s2;
  set_name2b(s2);
}
// ANSWER: none of the above ; memory leak

/*
LECTURE 11: Qsort & Reading Files
*/
// compare ints (given on cheatsheet):
int compare_ints(const void *p_a, const void *p_b) {
  int x = *(const int *)p_a;
  int y = (const int *)p_b;
  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return 0;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  qsort(arr, 5, sizeof(int), compare_ints);
}

// we can also use qsort to sort our structs
// Suppose we have a struct to represent students, and we wish to sort them by
// their age. If two students have the same age then we wish to sort them by
// their name. the comparison func + qsort for this would be:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student3 {
  char name[20];
  int age;
} student3;

int compare_student3s(const void *p_a, const void *p_b) {
  // Want to sort student3's by age
  // If students have the same age, sort by name

  student3 *p_a_s = (student3 *)p_a;
  student3 *p_b_s = (student3 *)p_b;
  int age_diff = p_a_s->age - p_b_s->age;
  if (age_diff != 0) {
    return age_diff;
  } else {
    return strcmp(p_a_s->name, p_b_s->name);
  }
}

int main() {
  student3 s1_arr[] = {{"John", 20}, {"Jill", 21}, {"Jack", 21}};

  qsort(s1_arr, 3, sizeof(student3), compare_student3s);

  for (int i = 0; i < 3; i++)
    printf("%s %d\n", s1_arr[i].name, s1_arr[i].age);
}

// File reading
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *fp = fopen("cities.txt", "r"); // pointer fp now points to cities.txt
  char line[200];
  fgets(line, 200, fp);
  line[strlen(line) - 1] =
      '\0'; // replaces last character(\n) with null terminator
  int num_items = atoi(line); // converts string to int
  return 0;
}

/*
LECTURE 12: Bubble Sort
*/
// expanded upon to fit any data type
// normal bubble sort:
#include <stdio.h>

void bubble_sort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        // swap
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
  int arr[] = {5, 3, 8, 1, 2};
  int n = 5;

  bubble_sort(arr, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }

  return 0;
}
// optimization (early stop):
void bubble_sort2(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int swapped = 0;

    for (int j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swapped = 1;
      }
    }

    if (!swapped)
      break; // already sorted
  }
}
// However in lecture, it was implemented like this to account for any given
// data type: the idea is to sort raw memory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort3(void *arr, int num_items, int item_size,
                  int (*compare)(const void *, const void *)) {
  int i, j;
  void *temp = malloc(item_size); // used to swap elemnts

  for (i = 0; i < num_items - 1; i++) {
    for (j = 0; j < num_items - i - 1; j++) {
      // compare arr[j] and arr[j + 1], swap if necessary
      // here we cant access arr[j] bcz its of type void*
      // instead we do manual pointer artimetic through memory
      void *p_j = arr + j * item_size;        // address of a[j]
      void *p_j1 = arr + (j + 1) * item_size; // address of a[j+1]

      // Now can compute compare(p_j, p_j1)
      if (compare(p_j, p_j1) > 0) { // if arr[j] > arr[j+1], swap
        // kind of want to swap *p_j and *p_j1
        // swap using memcpy bcz type is unknown
        memcpy(temp, p_j, item_size);  // temp = arr[j]
        memcpy(p_j, p_j1, item_size);  // arr[j] = arr[j+1]
        memcpy(p_j1, temp, item_size); // arr[j+1] = temp
      }
    }
  }
  free(temp);
}

int compare_int(const void *p_a, const void *p_b) // same as in aidsheet
{
  const int *x = (const int *)p_a;
  const int *y = (const int *)p_b;
  return *x - *y;
}

int main() {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int num_items = sizeof(arr) / sizeof(arr[0]);
  bubble_sort3(arr, num_items, sizeof(int), compare_int);

  for (int i = 0; i < num_items; i++)
    printf("%d ", arr[i]);

  return 0;
}

// we may optimize this the same way as before, by adding a break func halfway
// thru

/*
LECTURE 16: Best practices (getitng better at coding)
*/
// as a practice, q2 of lab4
// core idea of the problem: Read a file line by line → extract numbers →
// convert → sum file reading is mostly the same throughout, works like:
FILE *fp = fopen(filename, "r");
if (fp == NULL)
  return;

char line[100];
while (fgets(line, 100, fp) != NULL) {
  // process line
}
fclose(fp);

// to extract number from string, skip until you hit a digit (or -)
int is_digit_or_minus(char c) { return (c >= '0' && c <= '9') || c == '-'; }

const char *get_double_str(const char *line) {
  while (!is_digit_or_minus(*line) && *line != '\0') {
    line++;
  }
  return line;
}
// to convert to double, use ASCII trick from midterm q6:
// i got lazy but final code is:

void print_sum_of_constants(const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    return;
  }

  double sum = 0;
  char line[100]; // Assume no line is longer than 100 characters
  while (fgets(line, 100, fp) != NULL) {
    const char *double_str = get_double_str(line);
    sum += atof(double_str);
  }

  printf("Sum of constants in %s is %f\n", filename, sum);
  fclose(fp);
}

/*
LECTURE 18: Linked Lists
*/
// Implementation from lecture:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct LL {
  node *head;
  int size;
} LL;

void create_node(node **p_n, int data) {
  *p_n = (node *)malloc(sizeof(node));
  (*p_n)->data = data;
  (*p_n)->next = NULL;
}

void create_LL_from_data(LL **p_LL, int *data_arr, int size) {
  (*p_LL) = (LL *)malloc(sizeof(LL));
  (*p_LL)->size = 0; // initialize size to 0

  // keep track of the last node of the linked list
  node *tail = 0;

  for (int i = 0; i < size; i++) {

    // n is a pointer to a node with data = data[i], next = NULL
    node *n;
    create_node(&n, data_arr[i]);

    // If the last node is the 1st node, it must be head
    if (tail == 0) {
      (*p_LL)->head = n;
    }

    // If the last node is not the 1st node, update tail
    else {
      // append the new node to the end of the linked list
      tail->next = n;
    }

    // update the tail
    tail = n;

    // update the size
    (*p_LL)->size++;
  }
}

/*
LECTURE 23: PyInteger (2023 midterm q5)
# Asked to implement an ADT, pyinteger
# this ADT allows us to represent arbitrarily large integers and perform two
basic operations # plusplus(n1) -> adds 1 to the pyinteger n1 # add(n1,n2) ->
adds the pyinteger n2 to the pyinteger n1 # first we're asked to make a .h file,
and a .c file with necessary funcs:
*/
// pyinteger.h
#if !defined(PYINTEGER_H)
#define PYINTEGER_H

typedef struct pyinteger {
  int *digits;  // array of digits of the integer
  int size;     // # of digits
  int capacity; // maximum # of digits, every time reached -> double
} pyinteger;

void plusplus(pyinteger *n1);
void add(pyinteger *n1, pyinteger *n2);
#endif

// pyinteger.c
// lecture notes do this preformative implementation that makes no sense, here's
// how i would do it:
void createpyinteger(pyinteger *n, int capacity) {
  n->digits = (int *)malloc(capacity * sizeof(int));
  n->size = 0;
  n->capacity = capacity;
}
// implemnenting plusplus requires us to consider two cases, 9 and not 9
// if 9, long addition

void plusplus(pyintger *n1) {
  int index;
  for (index = n1->size - 1; index >= 0; index--) {
    if (n1->digits[index] == 9) {
      n1->digits[index] = 0;
    } else {
      n1->digits[index]++;
      break;
    }
  }
  if (index == -1) { // loop ran and only 9s were found
    n1->size++;
    if (n1->size > n1->capacity) { // capacity has to be updated
      n1->capacity *= 2;
      n1->digits = (int *)realloc(
          n1->digits,
          n1->capacity * sizeof(int)); // reallocates memory in array of digits
    }
    n1->digits[0] = 1;
    n1->digits[n1->size - 1] = 0;
  }
}

// add wasn't implemented in lecture, but the best way to do it is probably to
// Modify the pyintegers such that the units digit align. This can be done by
// shifting the digits
// over and filling everything before the leading digit with 0s.
// then u can just do long division

// htats everything from lecture, for algorithims part of the course c
// lectures.py ptactice: practice. & practice.py both in this file