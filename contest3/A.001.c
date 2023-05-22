#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN (50000)

#define MULT (257)

void findPattern(unsigned char* s, unsigned char* p) {
    unsigned int hashArr[STRLEN] = { 0 };
    unsigned int* hash = hashArr + 1;

    int index = 0;

    int patternHash = 0;
    int patternOffset = 0;
    unsigned int patternMultiplier = 1;


    bool hasPatternEnd = false;

    for (; s[index]; ++index) {

        // Add symbol to string hash
        hash[index] = hash[index - 1] * MULT;
        hash[index] += s[index];

        if (!hasPatternEnd) {
            if (p[index]) {
                // Add symbol to pattern

                patternMultiplier *= MULT;

                patternHash *= MULT;
                patternHash += p[index];

                continue;

            } else {
                // Finish pattern

                hasPatternEnd = true;

                index -= 1;
                patternOffset = index;
            }
        }

        if (hash[index] - hash[index - patternOffset - 1] * patternMultiplier == patternHash) {
            // chack false hash match

            bool correct = true;

            for (int i = 0; i <= patternOffset; ++i) {
                if (p[i] != s[index - patternOffset + i]) correct = false;
            }

            if (correct) {
                printf("%d\n", index - patternOffset);
            }
        }
    }
}

int main() {
    unsigned char s[STRLEN] = { 0 };
    unsigned char p[STRLEN] = { 0 };

    scanf("%s %s", s, p);

    findPattern(s, p);

    return 0;
}
