#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct edge{
    int from;
    int to;
    unsigned int length;
}edge;

edge makeedge(int from, int to, unsigned int length){
    edge edge1;
    edge1.from = from;
    edge1.to = to;
    edge1.length = length;
    return edge1;
}

void check_vertex(int v, int N){
    if ((v < 1) || (v > N)){
        printf("bad vertex");
        exit(0);
    }
}

void dynamic_array_initialize(unsigned int **A, int N, int n){
    int b, e;
    unsigned int l;
    for (int i = 0; i < n; i++){
        if (scanf("%d%d%u", &b, &e, &l) != EOF) {
            check_vertex(b, N);
            check_vertex(e, N);
            if (l > INT_MAX){
                printf("bad length");
                exit(0);
            }
            A[b - 1][e - 1] = l;
            A[e - 1][b - 1] = l;
        } else {
            printf("bad number of lines");
            exit(0);
        }
    }
}

void prim(unsigned int **graph, edge *span_tree, int *visited, int N){
    int i, j, priority_top = 0;
    unsigned int priority_length;
    span_tree[priority_top].length = 0;
    for(i = 0; i < N; ++i){
        visited[priority_top] = 1;
        for(j = 0; j < N; ++j){
            if((graph[priority_top][j] < span_tree[j].length)  && (visited[j] == 0)){
                span_tree[j].length = graph[priority_top][j];
                span_tree[j].from = priority_top + 1;
                span_tree[j].to = j + 1;
            }
        }
        priority_length = INT_MAX;
        priority_length++;
        for(j = 0; j < N; ++j){
            if((span_tree[j].length < priority_length) && (visited[j] == 0)){
                priority_length = span_tree[j].length;
                priority_top = j;
            }
        }
    }
}

int main() {
    int j, i, n, N, *visited, check = 0;
    unsigned int **graph;
    edge * span_tree;
    
    if (scanf("%d", &N) == EOF) {
        printf("bad number of lines");
        exit(0);
    }
    if (scanf("%d", &n) == EOF) {
        printf("bad number of lines");
        exit(0);
    }
    if ((N < 0) || (N > 5000)) {
        printf("bad number of vertices");
        exit(0);
    }
    if ((n < 0) || (n > N * (N + 1) / 2)) {
        printf("bad number of edges");
        exit(0);
    }
    if ((n == 0) && (N == 1)){
        exit(0);
    }
    if (n == 0) {
        printf("no spanning tree");
        exit(0);
    }

    graph = (unsigned int **) malloc(N * sizeof(unsigned int *));
    for(i = 0; i < N; ++i){
        graph[i] = (unsigned int *) malloc(N * sizeof(unsigned int));
    }
    for (i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            graph[i][j] = INT_MAX;
            graph[i][j]++;
        }
    }
    dynamic_array_initialize(graph, N, n);

    span_tree = (edge *) malloc(N * sizeof(edge));
    for (i = 0; i < N; ++i){
        span_tree[i] = makeedge(0, 0, INT_MAX);
        span_tree[i].length++;
    }

    visited = (int *) malloc(N * sizeof(int));
    for (i = 0; i < N; ++i){
        visited[i] = 0;
    }

    prim(graph, span_tree, visited, N);
    for(i = 0; i < N; ++i){
        if(visited[i] != 0) check++;
    }
    if(check == N) {
        for (i = 1; i < N; ++i) {
            printf("%d %d\n", span_tree[i].from, span_tree[i].to);
        }
    }else{
        printf("no spanning tree");
    }

    free(visited);
    free(span_tree);
    for(i = 0; i < N; ++i){
        free(graph[i]);
    }
    free(graph);
    return 0;
}
