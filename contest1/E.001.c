#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum {
    C_BR, // ()
    R_BR, // []
    Y_BR, // {}
};

char* input = 0;
char* pos = 0;
int* stack = 0;
int head = 0;

bool check() {

    if (scanf("%s", input) != 1) exit(2);

    while (*pos) {
        switch (*pos) {
#define CASEOPEN(BR, NAME)  \
    case BR:                 \
        stack[head++] = NAME; \
        break;

            CASEOPEN('(', C_BR);
            CASEOPEN('[', R_BR);
            CASEOPEN('{', Y_BR);
#undef CASEOPEN

#define CASECLOSE(BR, NAME)                   \
    case BR:                                   \
        if (!head) return false;                \
        if (stack[--head] != NAME) return false; \
        break;

            CASECLOSE(')', C_BR);
            CASECLOSE(']', R_BR);
            CASECLOSE('}', Y_BR);
#undef CASECLOSE

        default:
            exit(1);
        }

        ++pos;
    }

    return !head;
}

int main() {
    input = calloc(1000000, sizeof(char));
    pos = input;
    stack = calloc(1000000, sizeof(int));
    head = 0;

    if (check()) {
        printf("YES");
    } else {
        printf("NO");
    }

    free(input);
    free(stack);

    return 0;
}
