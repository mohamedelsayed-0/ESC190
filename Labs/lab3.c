#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student1.h"

// Q1
void set_int1(int x) {
    x = 42;
}
 // passes to local value
void set_int2(int *p_x) {
    *p_x = 42;
}
// change the address value

// Q2 
void print_student(student1 s) {
    printf("name: %s\n", s.name);
    printf("student number: %s\n", s.student_number);
    printf("year: %d\n", s.year);
}

// Q3A
void set_default_name(student1 *p_s) {
    strcpy(p_s->name, "default Student");
    p_s->year = 0;
}

// Q3B, doesn't work because s is a copy
void set_default_name_wrong(student1 s) {
    strcpy(s.name, "default Student");
    s.year = 0;
}

// Q4
void create_block1(student1 **p_p_s, int n_students) {
    *p_p_s = malloc(n_students * sizeof(student1));
}

// Q5 
void set_name(student1 *p_s, const char *str) {
    int i = 0;
    while (str[i] != '\0' && i < 199) {
        p_s->name[i] = str[i];
        i++;
    }
    p_s->name[i] = '\0';
}

// Q6
void destroy_block1(student1 *p_block) {
    free(p_block);
}

// Q7
typedef struct student2 {
    char *name;
    char *student_number;
    int year;
} student2;

void create_block2(student2 **p_p_s, int num_students) {
    *p_p_s = malloc(num_students * sizeof(student2));
    for (int i = 0; i < num_students; i++) {
        (*p_p_s)[i].name = NULL;
        (*p_p_s)[i].student_number = NULL;
        (*p_p_s)[i].year = 0;
    }
}

// Q8
void set_name2(student2 *p_s, const char *str) {
    if (str == NULL) {
        p_s->name = NULL;
        return;
    }
    p_s->name = malloc(strlen(str) + 1);
    strcpy(p_s->name, str);
}

// Q9
void destroy_block2(student2 *p_block, int num_students) {
    for (int i = 0; i < num_students; i++) {
        free(p_block[i].name);
        free(p_block[i].student_number);
    }
    free(p_block);
}

// Q10
void modify_student1_byval(student1 s) {
    strcpy(s.name, "Modified");  // won't change original
}

void modify_student2_byval(student2 s) {
    if (s.name != NULL) {
        strcpy(s.name, "Modified");  // changes original
    }
}

// Q13
void print_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("could not open file\n");
        return;
    }
    
    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

// Q14
double get_average(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("could not open file\n");
        return 0.0;
    }
    
    char line[200];
    int sum = 0;
    int count = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        sum += atoi(line);
        count++;
    }
    fclose(fp);
    
    if (count == 0) return 0.0;
    return (double)sum / count;
}

int main() {
    // Q1
    printf("Q1: pass by value vs pointer ---\n");
    int a = 5;
    set_int1(a);
    printf("after set_int1: a = %d\n", a);  // dosent change pointer value
    set_int2(&a);
    printf("after set_int2: a = %d\n\n", a);  // now 42

    // Q2
    printf("Q2: student:\n");
    student1 s1 = {"yassine", "1234567890", 1};
    print_student(s1);
    printf("\n");

    // Q3
    printf("Q3: default name\n");
    student1 s2 = {"original", "0000000000", 3};
    set_default_name(&s2);
    printf("correct version: %s, year %d\n", s2.name, s2.year);
    
    student1 s3 = {"original", "0000000000", 3};
    set_default_name_wrong(s3);
    printf("wrong version: %s, year %d\n\n", s3.name, s3.year);

    // Q4/5/6
    printf("block of student1 \n");
    student1 *block1 = NULL;
    create_block1(&block1, 3);
    set_name(&block1[0], "alice");
    printf("block1[0].name = %s\n", block1[0].name);
    destroy_block1(block1);
    printf("block destroyed\n\n");

    // Q7/8/9
    printf("block of student2\n");
    student2 *block2 = NULL;
    create_block2(&block2, 3);
    set_name2(&block2[0], "bob");
    printf("block2[0].name = %s\n", block2[0].name);
    destroy_block2(block2, 3);
    printf("block destroyed\n\n");

    // Q10
    printf("student1 vs student2 comparison:\n");
    student1 test1 = {"test1", "111", 1};
    modify_student1_byval(test1);
    printf("student1 after modify: %s (unchanged)\n", test1.name);

    student2 test2;
    test2.name = malloc(200);
    test2.student_number = NULL;
    strcpy(test2.name, "test2");
    modify_student2_byval(test2);
    printf("student2 after modify: %s (changed)\n", test2.name);
    free(test2.name);

    return 0;
}