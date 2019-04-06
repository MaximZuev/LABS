#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
}spisok;

spisok *create(int data){
    spisok *tmp = (spisok *) malloc(sizeof(spisok));
    tmp -> value = data;
    tmp -> next = NULL;
    return tmp;
}
void add_element_start(spisok **head, int data)
{
    spisok *tmp = (spisok *) malloc(sizeof(spisok));
    tmp -> value = data;
    tmp -> next = *head;
    *head = tmp;
}

void *remove_all(spisok *head)
{
    while(head != NULL){
        spisok *p = head;
        head = head -> next;
        free(p);
    }
}

void dynamic_array_initialize(spisok **A, int N, int n)
{
    int b, e;
    for (int i = 0; i < n; i++){
        if (scanf("%d%d", &b, &e) != EOF) {
            if ((b < 1) || (b > N) || (e < 1) || (e > N)){
                printf("bad vertex");
                exit(0);
            }
            if (A[b - 1] == NULL){
                A[b - 1] = create(e);
            } else {
                add_element_start(&A[b - 1], e);
            }
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

void DFS(int start, int *visited, spisok **graph,  int N, int *k, int *sort_g)
{
    spisok *p = graph[start - 1];
    visited[start-1] = 1;
    while (p) {
        if (visited[(p -> value) - 1] == 0) {
            DFS(p -> value , visited, graph, N, k, sort_g);
        }
        if (visited[(p -> value) - 1] == 1) {
            printf("impossible to sort");
            exit(0);
        }
        p = p -> next;
    }
    visited[start-1] = 2;
    sort_g[*k] = start;
    *k = *k + 1;
}

int main() {
    int i, N, n, *visited, *sort_g, k = 0;
    spisok ** graph;

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
    if ((n < 0) || (n > N * (N + 1) / 2)){
        printf("bad number of edges");
        exit(0);
    }

    sort_g = (int *) malloc(N * sizeof(int));

    visited = (int *) calloc(N, sizeof(int));

    graph = (spisok **) malloc(N * sizeof(spisok *));
    for(i = 0; i < N; i++){
        graph[i] = NULL;
    }
    dynamic_array_initialize(graph, N, n);

    for (i = 0; i < N; i++) {
        if (visited[i] != 2) {
            DFS(i + 1, visited, graph, N, &k, sort_g);
        }
    }
    for(i = N - 1; i >= 0; i--){
        printf("%d ", sort_g[i]);
    }

    for (i = 0; i < N; i++){
        remove_all(graph[i]);
    }
    free(sort_g);
    free(visited);
    free(graph);
    return 0;
}
