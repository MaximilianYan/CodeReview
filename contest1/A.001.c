#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum {
    BYE = 0,
    PUSH,
    POP,
    BACK,
    SIZE,
    CLEAR,
};

int scanCom(int* com) {
    char buffer[256] = { 0 };
    if (scanf("%s", buffer) != 1) {
        return 2;
    }

    if (
        buffer[0] == 'p' &&
        buffer[1] == 'u') {
        *com = PUSH;
    } else if (
        buffer[0] == 'p' &&
        buffer[1] == 'o') {
        *com = POP;
    } else if (
        buffer[0] == 'b') {
        *com = BACK;
    } else if (
        buffer[0] == 's') {
        *com = SIZE;
    } else if (
        buffer[0] == 'c') {
        *com = CLEAR;
    } else if (
        buffer[0] == 'e') {
        *com = BYE;
    }

    return 0;
}

int main() {
    int data[10000] = { 0 };
    int head = 0;
    int com = 1;

    while (com) {
        if (scanCom(&com)) return 2;

        switch (com) {
        case BYE:
            printf("bye\n");
            break;
        case PUSH:
            if (scanf("%d", data + head++) != 1) return 2;
            printf("ok\n");
            break;
        case POP:
        case BACK:
            if (!head) {
                printf("error\n");
                break;
            }

            printf("%d\n", data[--head]);
            head += (com == BACK);
            break;
        case SIZE:
            printf("%d\n", head);
            break;
        case CLEAR:
            head = 0;
            printf("ok\n");
            break;
        }
    }

    return 0;
}
