#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MOD (1e7 + 4321)
#define STRLEN (50000)

#define MULT (257)

int main() {
    unsigned char s[STRLEN] = { 0 };
    unsigned char p[STRLEN] = { 0 };

    scanf("%s %s", s, p);

    unsigned int hashArr[STRLEN] = { 0 };
    unsigned int* hash = hashArr + 1;

    int patHash = 0;
    int index = 0;
    unsigned int multiplier = 1;
    for (; p[index]; ++index) {
        if (!s[index]) return 0;

        multiplier *= MULT;

        patHash *= MULT;
        patHash += p[index];

        if (index)
            hash[index] = hash[index - 1] * MULT;
        hash[index] += s[index];
        // printf("'%d'\n", hash[index]);
    }

    index--;
    int patOff = index;
    // printf("\"%d\"\n", patOff);


    for (; s[index]; ++index) {
        hash[index] = hash[index - 1] * MULT;
        hash[index] += s[index];
        // printf("'%d'\n", hash[index]);

        // printf("index %d", index);
        // printf("%d %d\n", hash[index] - hash[index - patOff - 1] * multiplier, patHash);

        if (hash[index] - hash[index - patOff - 1] * multiplier == patHash) {
            bool correct = true;
            // printf("cor");
            // printf("%d %d", index, patOff);
            for (int i = 0; i <= patOff; ++i) {
                if (p[i] != s[index - patOff + i]) correct = false;
            }
            if (correct) {
                printf("%d\n", index - patOff);
            }
        }
    }

    // printf("hash: ");
    // for (int i = 0; s[i]; ++i) {
        // printf("%d ", hash[i]);
    // }
    // printf("\ndelta: ");
    // for (int i = patOff; s[i]; ++i) {
        // printf("%d ", hash[i] - hash[i - patOff - 1] * MULT);
    // }

    return 0;
}
