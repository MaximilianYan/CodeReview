#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int min(const int a, const int b) {
    if (a < b) return a;
    return b;
}

bool BinarySearch(const int* begin, const int* end, int target) {
    size_t delta = ((end - begin) ) >> 1;
    if (delta == 0)
        return *begin == target;

    const int* mid = begin + delta;

    if (*mid > target) {
        return BinarySearch(begin, mid, target);
    } else {
        return BinarySearch(mid, end, target);
    }

    return false;
}

int main() {
    int n = 0, q = 0;
    int arr[110000] = { 0 };
    int i = 0, j = 0, t = 0;

    if (scanf("%d", &n) != 1) return 2;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", arr + i) != 1) return 2;
    }
    if (scanf("%d", &q) != 1) return 2;

    while (q--) {
        if (scanf("%d %d %d", &i, &j, &t) != 3) return 2;

        if (BinarySearch(arr + i, arr + j, t)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
