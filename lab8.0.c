#include <stdio.h>
#include <stdlib.h>

int get_par(int v, int *par) {
    if (v == par[v]) return v;
    return par[v] = get_par(par[v], par);
}

void make_union(int a, int b, int *par) {
    a = get_par(a, par);
    b = get_par(b, par);
    if (a != b) par[a] = b;
}

typedef struct edge{
   int from;
   int to;
   int length;
}edge;

edge makeedge(int from, int to, int length){
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

void dynamic_array_initialize(edge *A, int N, int n){
    int b, e, l;
    for (int i = 0; i < n; i++){
        if (scanf("%d%d%d", &b, &e, &l) != EOF) {
            check_vertex(b, N);
            check_vertex(e, N);
            if (l < 0){
                printf("bad length");
                exit(0);
            }
            A[i] = makeedge(b, e, l);
        } else {
            printf("bad number of lines");
            exit(0);
        }
    }
}

void QSort (edge *A, int l, int r){
    int i = l, j = r, x = A[(l+r)/2].length;
    edge t;
    do{
        while(A[i].length < x) i++;
        while(A[j].length > x) j--;
        if(i <= j) {
            t = A[i];
            A[i] = A[j];
            A[j] = t;
            i++;
            j--;
        }
    }while(i < j);
    if (i < r) QSort(A, i, r);
    if (j > l) QSort (A, l, j);
}

void kruskal(int *par, edge *graph,  int n, int N, int *frame){
    int k = 0;
    for(int i = 0; i < n; i++){
        if (get_par(((graph[i].from) - 1), par) != get_par(((graph[i].to) - 1), par)){
            make_union((graph[i].from) - 1, (graph[i].to) - 1, par);
            frame[k] = i;
            k++;
            frame[N-1]++;
        }
    }
}

int main() {
    int i, N, n, *par, *frame;
    edge *graph;

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

    par = (int *) malloc(N * sizeof(int));
    for (i = 0; i < N; i++) {
        par[i] = i;
    }

    frame = (int *) malloc(N * sizeof(int));
    for (i = 0; i < N; i++) {
        frame[i] = 0;
    }
    frame[N-1] = 0;

    graph = (edge *) malloc(n * sizeof(edge));
    dynamic_array_initialize(graph, N, n);
    QSort(graph, 0, n - 1);

    kruskal(par, graph, n, N, frame);
    if (frame[N-1] == N-1) {
        for (i = 0; i < N - 1; i++) {
            printf("%d %d\n", graph[frame[i]].from, graph[frame[i]].to);
        }
    } else {
        printf("no spanning tree");
        exit(0);
    }

    free(par);
    free(frame);
    free(graph);

    return 0;
}
