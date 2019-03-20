#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct stack
{
    int data;
    struct stack *next;
}stack;

stack *makestack(int value)
{
    stack *stack1 = (stack *) malloc(sizeof(stack));
    stack1->data = value;
    return stack1;
}

void s_push(stack **top, int value)
{
    stack *q;
    q=makestack(value);
    if (top == NULL) {
        *top = q;
    }
    else{
        q->next = *top;
        *top = q;
    }
}

void s_print(stack *top) {
    stack *q = top;
    while (q) {
        printf("%d ", q->data);
        q = q->next;
    }
}

void freestack(stack *top)
{
    if (top == NULL) {
        return;
    }
    freestack(top->next);
    free(top);
}

void check_vertex(int v, int N)
{
    if ((v < 1) || (v > N)){
        printf("bad vertex");
        exit(0);
    }
}

void dynamic_array_initialize(stack **A, int N, int n)
{
    int b, e;
    for (int i = 0; i < n; i++){
        if (scanf("%d%d", &b, &e) != EOF) {
            check_vertex(b, N);
            check_vertex(e, N);
            s_push(&A[b-1], e);
            if (b == e){
                printf("impossible to sort");
                exit(0);
            }
        } else {
            printf("bad number of lines");
            exit(0);
        }
    }
}

void DFS(int start, int *visited, stack **graph,  int N, stack **top)
{
    visited[start-1] = 1;
    while (graph[start - 1]) {
        if (visited[(graph[start - 1]->data) - 1] == 0) {
            DFS(graph[start - 1]->data , visited, graph, N, top);
        }
        if (visited[(graph[start - 1]->data) - 1] == 1) {
            printf("impossible to sort");
            exit(0);
        }
        graph[start - 1] = graph[start - 1]->next;
    }
    visited[start-1] = 2;
    s_push(top, start);
}

int main() {
    int i, N, n, *visited;
    stack ** graph, * top = NULL;

    if (scanf("%d", &N) == EOF) {
        printf("bad number of lines");
        exit(0);
    }
    if (scanf("%d", &n) == EOF) {
        printf("bad number of lines");
        exit(0);
    }
    if ((N < 0) || (N > 1000)){
        printf("bad number of vertices");
        exit(0);
    }
    if ((n < 0) || (n > N*(N+1)/2)){
        printf("bad number of edges");
        exit(0);
    }

    visited = (int *)malloc(N*sizeof(int));
    for(i = 0; i < N; i++){
        visited[i] = 0;
    }

    graph = (stack **) malloc(N*sizeof(stack *));
    for(i = 0; i < N; i++){
        graph[i] = NULL;
    }
    dynamic_array_initialize(graph, N, n);

    for (i = 0; i < N; i++) {
        if (visited[i] != 2) {
            DFS(i + 1, visited, graph, N, &top);
        }
    }

    s_print(top);

    for (i = 0; i < N; i++){
        freestack(graph[i]);
    }
    freestack(top);
    free(visited);
    free(graph);

    return 0;
}
