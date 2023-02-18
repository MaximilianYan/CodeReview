#include <stdio.h>
#include <stdlib.h>

int comparatorDelta(const void* a, const void* b);
int comparatorInt(const void* a, const void* b);

#define END0      \
    free(xs);      \
    free(deltas);   \
    free(deltaOrds); \
    return 0;

// 6 2
// 1 2 3 9 8 7
// 1 2 3 7 8 9
//  1 1 4 1 1


int* xs = 0;
int* deltas = 0;
int* deltaOrds = 0;

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 2;

    xs = calloc(n, sizeof(int));
    deltas = calloc(n - 1, sizeof(int));
    deltaOrds = calloc(n - 1, sizeof(int));
    if (!(xs && deltas && deltaOrds)) return 1;


    for (int i = 0; i < n; ++i) {
        if (scanf("%d", xs + i) != 1) return 2;
    }

    qsort(xs, n, sizeof(int), comparatorInt);

    for (int i = 1; i < n; ++i) {
        deltas[i - 1] = xs[i] - xs[i - 1];
        deltaOrds[i] = i - 1;
    }

    if (k >= n) {
        printf("0\n");

        END0;
    }

    int ans = -2;

    for (int i = 0; i < n - k; ++i) {
        qsort(deltaOrds, n, sizeof(int), comparatorDelta);
        if (deltaOrds[i] > 0)
            deltas[deltaOrds[i] - 1] += deltas[deltaOrds[i]];
        if (deltaOrds[i] < n - 1)
            deltas[deltaOrds[i] + 1] += deltas[deltaOrds[i]];
        ans = deltas[deltaOrds[i]];
        deltas[deltaOrds[i]] = -1;
    }

    printf("%d\n", ans);

    END0;
}

int comparatorDelta(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (deltas[arg1] < deltas[arg2]) return -1;
    if (deltas[arg1] > deltas[arg2]) return 1;
    return 0;

    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

int comparatorInt(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;

    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}
