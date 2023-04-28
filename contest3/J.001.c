#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int n;
    scanf("%d", &n);

    int* arr = calloc(n, sizeof(int));
    int* summMem = calloc(n + 1, sizeof(int));
    int* summ = summMem + 1;

    // read numbers
    for (int index = 0; index < n; ++index) {
        scanf("%d", &arr[index]);
        if (index % 2) {
            arr[index] = -arr[index];
        }
    }

    // set prefix sums
    for (int index = 0; index < n; ++index) {
        summ[index] = summ[index - 1] + arr[index];
    }

    int m;
    scanf("%d", &m);

    while (m--) {
        int com, l, r;
        scanf("%d %d %d", &com, &l, &r);
        // printf("      -1 0 1 2\n");
        // printf("summs [%d %d %d %d]\n", summ[-1], summ[0], summ[1], summ[2]);

        if (com) {
            // request

            int sumD = summ[r - 1] - summ[l - 2];
            if ((l - 1) % 2)
                sumD = -sumD;

            printf("%d\n", sumD);
        } else {
            // value changing

            int i = l - 1;
            int val = r;
            if (i % 2)
                val = -val;

            int diff = val - arr[i];
            arr[i] += diff;

            // update prefix sums
            for (int index = i; index < n; ++index) {
                summ[index] += diff;
            }
        }
    }


    free(arr);
    free(summMem);
    return 0;
}
