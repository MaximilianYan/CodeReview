#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int min(const int a, const int b) {
    if (a < b) return a;
    return b;
}

struct Edge {
    int pos;
    int delta;
};

int comparator(const void* a, const void* b) {
    if (((const struct Edge*)a)->pos <
        ((const struct Edge*)b)->pos) return -1;
    if (((const struct Edge*)a)->pos >
        ((const struct Edge*)b)->pos) return +1;
    if (((const struct Edge*)a)->delta >
        ((const struct Edge*)b)->delta) return -1;
    if (((const struct Edge*)a)->delta <
        ((const struct Edge*)b)->delta) return +1;
    return 0;
}

int main() {
    int n = 0;
    struct Edge edges[210000] = { {0, 0} };

    if (scanf("%d", &n) != 1) return 2;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", (int*)(void*)(edges + (i << 1) + 0)) != 1) return 2;
        if (scanf("%d", (int*)(void*)(edges + (i << 1) + 1)) != 1) return 2;
        edges[(i << 1) + 0].delta = +1;
        edges[(i << 1) + 1].delta = -1;
    }

    qsort(edges, n << 1, sizeof(struct Edge), comparator);

    int counter = 0;
    int k = 0;
    for (int i = 0; i < n << 1; ++i) {
        if (!counter) {
            if (edges[i].delta < 0) return 3;
            ++k;
        }

        counter += edges[i].delta;
    }

    printf("%d\n", k);

    counter = 0;
    for (int i = 0; i < n << 1; ++i) {
        if (!counter) {
            if (edges[i].delta < 0) return 3;
            ++k;
            printf("%d ", edges[i].pos);
        }

        counter += edges[i].delta;

        if (!counter)
            printf("%d\n", edges[i].pos);
    }

    return 0;
}
