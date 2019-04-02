#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void readin(FILE **in, FILE **out, int *N, int *n, int *S, int *F, long **graph){
    int i, j, b, e;
    long l;
    *in = fopen("in.txt", "r");
    *out = fopen("out.txt", "w");
    if (fscanf(*in, "%d", N) == EOF) {
        fprintf(*out, "bad number of lines");
        exit(0);
    }
    if (fscanf(*in, "%d %d", S, F) == EOF) {
        fprintf(*out, "bad number of lines");
        exit(0);
    }
    if (fscanf(*in, "%d", n) == EOF) {
        fprintf(*out, "bad number of lines");
        exit(0);
    }
    if ((*N < 0) || (*N > 5000)) {
        fprintf(*out, "bad number of vertices");
        exit(0);
    }
    if ((*S < 1) || (*S > *N) || (*F < 1) || (*F > *N)) {
        fprintf(*out, "bad vertex");
        exit(0);
    }
    if ((*n < 0) || (*n > *N * (*N + 1) / 2)) {
        fprintf(*out, "bad number of edges");
        exit(0);
    }
    if ((*S < 1) || (*S > *N) || (*F < 1) || (*F > *N)) {
        fprintf(*out, "bad vertex");
        exit(0);
    }
    *graph = (long *) malloc(*N * *N * sizeof(long));
    for (i = 0; i < *N; ++i){
        for (j = 0; j < *N; ++j){
            *(*graph + i * *N +j) = 0;
        }
    }
    for (i = 0; i < *n; i++) {
        if (fscanf(*in, "%d%d%li", &b, &e, &l) != EOF) {
            if ((b < 1) || (b > *N) || (e < 1) || (e > *N)) {
                fprintf(*out, "bad vertex");
                free(graph);
                exit(0);
            }
            if ((l > INT_MAX) || (l < 0)) {
                fprintf(*out, "bad length");
                free(graph);
                exit(0);
            }
            *(*graph + (b - 1) * *N +(e - 1)) = l;
            *(*graph + (e - 1) * *N +(b - 1)) = l;
        } else {
            fprintf(*out, "bad number of lines");
            free(graph);
            exit(0);
        }
    }
}

void printd(FILE *out, long long *d, int N){
    for (int i = 0; i < N; ++i) {
        if (d[i] != LONG_LONG_MAX) {
            if (d[i] <= INT_MAX) {
                fprintf(out, "%lli ", d[i]);
            } else {
                if (d[i] > INT_MAX) {
                    fprintf(out, "INT_MAX+ ");
                }
            }
        } else {
            fprintf(out, "oo ");
        }
    }
    fprintf(out, "\n");
}

void findd(int N, const long *graph, long long *d, short *visited){
    int i, minindex;
    long long temp, minl;
    do {
        minindex = INT_MAX;
        minl = LONG_LONG_MAX;
        for (i = 0; i < N; ++i){
            if ((visited[i] == 1) && (d[i] < minl)){
                minl = d[i];
                minindex = i;
            }
        }
        if (minindex != INT_MAX){
            for (i = 0; i < N; ++i){
                if (*(graph + minindex * N + i) > 0){
                    temp = minl + *(graph + minindex * N + i);
                    if (temp < d[i]){
                        d[i] = temp;
                    }
                }
            }
            visited[minindex] = 0;
        }
    } while (minindex < INT_MAX);
}

void recovery_path(FILE *out, int *path, int F, int N, const long long *d, const long *graph){
    int i, end = F - 1, k = 1, check = 0;
    long long weight = d[end], temp;
    while (weight > 0){
        for (i = 0; i < N; ++i){
            if (*(graph + end * N + i) != 0){
                temp = weight - *(graph + end * N + i);
                if (temp == d[i]){
                    weight = temp;
                    end = i;
                    path[k] = i + 1;
                    k++;
                }
            }
        }
    }
    for(i = 0; i < N; i++){
        if ((d[i] >= INT_MAX) && (d[i] != LONG_LONG_MAX)) {
            check++;
        }
    }
    if ((check > 2) && (d[F - 1] > INT_MAX)){
        fprintf(out, "overflow");
    } else {
        for (i = 0; i < k; ++i){
            fprintf(out, "%d ", path[i]);
        }
    }
}

int main() {
    FILE *in, *out;
    int i, n, N, S, F, *path;
    long long *d;
    long *graph;
    short *visited;

    readin(&in, &out, &N, &n, &S, &F, &graph);

    visited = (short *) malloc(N * sizeof(short));
    for (i = 0; i < N; ++i){
        visited[i] = 1;
    }

    path = (int *) malloc(N * sizeof(int));
    path[0] = F;

    d = (long long *) malloc(N * sizeof(long long));
    for (i = 0; i < N; ++i){
        d[i] = LONG_LONG_MAX;
    }
    d[S - 1] = 0;

    findd(N, graph, d, visited);
    printd(out, d, N);
    if (F != S) {
        if (d[F - 1] != LONG_LONG_MAX) {
            recovery_path(out, path, F, N, d, graph);
        } else {
            fprintf(out, "no path");
        }
    } else {
        fprintf(out, "%d", path[0]);
    }

    free(visited);
    free(d);
    free(graph);
    free(path);
    fclose(in);
    fclose(out);
    return 0;
}
