#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int start, end;
    int this_start, this_end;
    int *arr = NULL;
    start = end = 0;
    this_start = this_end = 0;

    scanf("%d", &n);

    arr = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i-1]) {
            this_end++;
        } else {
            this_end = this_start = i;
        }
        if (end - start < this_end - this_start)
            start = this_start, end = this_end;
    }

    for (int i = start; i <= end; i++) {
        printf("%d%s", arr[i], i == end ? "\n" : " ");
    }

    free(arr);
    return 0;
}
