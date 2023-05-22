#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
    int pos; // edge position
    int dir; // edge direction (+1/-1)
};

struct Matr {
    int l;
    int r;

    int multiplier; // counter of coinciding matrs
};

struct MatrCounter {
    struct Matr* matr;

    int counterOpened;
};

int matrCompr(const void* aptr, const void* bptr);
int matrEndingCompr(const void* aptr, const void* bptr);
bool doMatrsCoinces(const struct Matr* a, const struct Matr* b);

void scanMatrs(int n, struct Matr* matrs) {
    for (int i = 0; i < n; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);

        matrs[i].l = l;
        matrs[i].r = r;
        matrs[i].multiplier = 1;
    }
}

int deleteCoincidences(int n, struct Matr* matrs) {
    int newN = n;
    int prevUniqI = 0;
    for (int i = 1; i < n; ++i) {
        if (doMatrsCoinces(&matrs[prevUniqI], &matrs[i])) {
            matrs[prevUniqI].multiplier++;
            matrs[i].multiplier = 0;

            newN--;
        } else {
            prevUniqI = i;
        }
    }

    return newN;
}

int countNested(int n, struct Matr* matrs, struct Matr* matrsEndings) {
    struct MatrCounter* matrsCounts = calloc(n, sizeof(struct MatrCounter));
    for (int i = 0; i < n; ++i) {
        matrsCounts[i].matr = &matrs[i];
        matrsCounts[i].counterOpened = 0;
    }

    int counterOpened = 0;
    int ans = 0;

    int i = 0;
    int iEnd = 0;
    while (true) {
        if (i < n && matrsCounts[i].matr->l < matrsEndings[iEnd].r) {
            matrsCounts[i].counterOpened = counterOpened;

            counterOpened++;

            ++i;
        } else {
            counterOpened--;

            for (int index = 0; index < i; ++index) {
                // matrsCounts[index].counterOpened--;
            }

            ans += matrsCounts[iEnd].counterOpened;

            ++iEnd;
            if (iEnd == n) break;
        }
    }


    free(matrsCounts);
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);

    struct Matr* matrs = calloc(n, sizeof(struct Matr));

    scanMatrs(n, matrs);
    qsort(matrs, n, sizeof(struct Matr), matrCompr);

    n = deleteCoincidences(n, matrs);
    qsort(matrs, n, sizeof(struct Matr), matrCompr);

    struct Matr* matrsEndings = calloc(n, sizeof(struct Matr));
    for (int i = 0; i < n; ++i)
        matrsEndings[i] = matrs[i];
    qsort(matrsEndings, n, sizeof(struct Matr), matrEndingCompr);

    int ans = countNested(n, matrs, matrsEndings);
    printf("%d", ans);

    free(matrs);
    free(matrsEndings);
    return 0;
}


int matrCompr(const void* aptr, const void* bptr) {
    const struct Matr* a = (const struct Matr*)aptr;
    const struct Matr* b = (const struct Matr*)bptr;

    if (a->multiplier == 0)
        if (b->multiplier == 0)
            return 0;
        else // b > 0
            return +1;
    else     // a > 0
        if (b->multiplier == 0)
            return -1;

    if (a->l < b->l) return -1;
    if (a->l > b->l) return +1;

    if (a->r > b->r) return -1;
    if (a->r < b->r) return +1;

    return 0;
}

int matrEndingCompr(const void* aptr, const void* bptr) {
    const struct Matr* a = (const struct Matr*)aptr;
    const struct Matr* b = (const struct Matr*)bptr;

    if (a->r < b->r) return -1;
    if (a->r > b->r) return +1;

    if (a->l > b->l) return -1;
    if (a->l < b->l) return +1;

    return 0;
}

bool doMatrsCoinces(const struct Matr* a, const struct Matr* b) {
    if (a->l != b->l) return false;
    if (a->r != b->r) return false;
    return true;
}
