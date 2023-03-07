#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int min(const int a, const int b) {
    if (a < b) return a;
    return b;
}

int main() {
    int n = 0;
    int as[110000] = { 0 };
    int ls[110000] = { 0 };
    int rs[110000] = { 0 };
    if (scanf("%d", &n) != 1) return 2;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", as + i) != 1) return 2;
    }
    int q = 0;
    if (scanf("%d", &q) != 1) return 2;

    ls[0] = as[0];
    for (int i = 1; i < n; ++i) {
        ls[i] = min(ls[i - 1], as[i]);
    }
    rs[n - 1] = as[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        rs[i] = min(rs[i + 1], as[i]);
    }

    int l = 0, r = 0;
    while (q--) {
        if (scanf("%d %d", &l, &r) != 2) return 2;
        printf("%d\n", min(ls[l - 1], rs[r - 1]));
    }

    return 0;
}
