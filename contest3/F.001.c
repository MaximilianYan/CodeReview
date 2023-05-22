#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = calloc(n, sizeof(int));
    for (int index = 0; index < n; ++index) {
        scanf("%d", &arr[index]);
    }

    


    free(arr);
    return 0;
}
