#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);

int main()
{
    int i, n;
    int *arr = NULL;
    
    scanf("%d", &n);

    arr = malloc(sizeof(int) * n);
    if (arr == NULL) {
        fprintf(stderr, "malloc error!\n");
        exit(-1);
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), cmp);

    for (i = 0; i < n; i++) {
        printf("%d%s", arr[i], i + 1 == n ? "\n" : " ");
    }
    
    return 0;
}

int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
