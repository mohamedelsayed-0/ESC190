#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Q0
struct student {
    int grade;
};

struct student* create_student(int grade) {
    struct student *s = malloc(sizeof(struct student));
    s->grade = grade;
    return s;
}

struct student** create_student_array(int size) {
    struct student **arr = malloc(size * sizeof(struct student*));
    return arr;
}

//Q1
typedef struct node {
    int vertex;
    struct node *next;
} node;

typedef struct graph {
    int n_vertices;
    node **adj_list;  
} graph;


int random_step(graph *g, int current) {
    node *temp = g->adj_list[current];
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (count == 0) {
        return current;
    }

    int r = rand() % count;
    temp = g->adj_list[current];


    for (int i = 0; i < r; i++) {
        temp = temp->next;
    }

    return temp->vertex;
}

void random_walk(graph *g, int start, int n_steps) {
    int current = start;

    printf("Random walk: ");
    printf("%d ", current);

    for (int i = 0; i < n_steps; i++) {
        current = random_step(g, current);
        printf("%d ", current);
    }

    printf("\n");
}


//Q2
double *create_transition_matrix(graph *g) {
    int n = g->n_vertices;
    double *M = malloc(n * n * sizeof(double));

    for (int i = 0; i < n * n; i++) {
        M[i] = 0.0;
    }
    for (int j = 0; j < n; j++) {
        node *temp = g->adj_list[j];
        int count = 0;

        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        if (count == 0) {
            continue;
        }
        temp = g->adj_list[j];

        while (temp != NULL) {
            int i = temp->vertex;
            M[i * n + j] = 1.0 / count;
            temp = temp->next;
        }
    }
    return M;
}


void print_matrix(double *M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", M[i * n + j]);
        }
        printf("\n");
    }
}

//Q3
void mat_vec_mult(double *M, double *v, double *result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = 0.0;
        for (int j = 0; j < n; j++) {
            result[i] += M[i * n + j] * v[j];
        }
    }
}

void pagerank(double *M, double *v, int n, int k) {
    double *temp = malloc(n * sizeof(double));

    for (int iter = 0; iter < k; iter++) {
        mat_vec_mult(M, v, temp, n);

        for (int i = 0; i < n; i++) {
            v[i] = temp[i];
        }
    }
    free(temp);
}

void print_vector(double *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.6f ", v[i]);
    }
    printf("\n");
}

int main(void) {
    struct student **students = create_student_array(3);
    students[0] = create_student(90);
    students[1] = create_student(91);
    students[2] = create_student(92);
    for(int i = 0; i < 3; i++){
    printf("Student %d grade: %d\n", i, students[i]->grade);
    }


    srand(time(NULL));
    graph g;
    g.n_vertices = 5;
    g.adj_list = malloc(g.n_vertices * sizeof(node *));


    for (int i = 0; i < g.n_vertices; i++) {
        g.adj_list[i] = NULL;
    }

    node *n0 = malloc(sizeof(node));
    n0->vertex = 1;
    n0->next = NULL;
    g.adj_list[0] = n0;


    node *n1a = malloc(sizeof(node));
    node *n1b = malloc(sizeof(node));
    node *n1c = malloc(sizeof(node));
    n1a->vertex = 0;
    n1b->vertex = 2;
    n1c->vertex = 3;
    n1a->next = n1b;
    n1b->next = n1c;
    n1c->next = NULL;
    g.adj_list[1] = n1a;


    node *n2a = malloc(sizeof(node));
    node *n2b = malloc(sizeof(node));
    n2a->vertex = 1;
    n2b->vertex = 4;
    n2a->next = n2b;
    n2b->next = NULL;
    g.adj_list[2] = n2a;

    node *n3 = malloc(sizeof(node));
    n3->vertex = 1;
    n3->next = NULL;
    g.adj_list[3] = n3;

    node *n4 = malloc(sizeof(node));
    n4->vertex = 2;
    n4->next = NULL;
    g.adj_list[4] = n4;


    random_walk(&g, 0, 10);
    free(n0);
    free(n1a);
    free(n1b);
    free(n1c);
    free(n2a);
    free(n2b);
    free(n3);
    free(n4);
    free(g.adj_list);

    graph g2;
    g2.n_vertices = 4;
    g2.adj_list = malloc(g2.n_vertices * sizeof(node *));

for (int i = 0; i < g2.n_vertices; i++) {
    g2.adj_list[i] = NULL;
}

    node *m0a = malloc(sizeof(node));
    node *m0b = malloc(sizeof(node));
    m0a->vertex = 1;
    m0b->vertex = 2;
    m0a->next = m0b;
    m0b->next = NULL;
    g2.adj_list[0] = m0a;

    node *m1 = malloc(sizeof(node));
    m1->vertex = 2;
    m1->next = NULL;
    g2.adj_list[1] = m1;

node *m2a = malloc(sizeof(node));
node *m2b = malloc(sizeof(node));
m2a->vertex = 0;
m2b->vertex = 3;
m2a->next = m2b;
m2b->next = NULL;
g2.adj_list[2] = m2a;

    node *m3 = malloc(sizeof(node));
m3->vertex = 0;
m3->next = NULL;
g2.adj_list[3] = m3;

    double *M = create_transition_matrix(&g2);

    printf("Transition matrix:\n");
    print_matrix(M, g2.n_vertices);

free(M);
free(m0a);
free(m0b);
free(m1);
free(m2a);
free(m2b);
free(m3);
free(g2.adj_list);
    return 0;
}