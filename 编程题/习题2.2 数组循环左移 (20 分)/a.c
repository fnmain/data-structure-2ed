#include <stdio.h>

void shift_one_bit(int arr[], int len)
{
    int i;
    int temp = arr[0];
    for (i = 1; i < len; i++) {
        arr[i-1] = arr[i];
    }
    arr[len-1] = temp;
}

int main()
{
    int n, m;
    int i;

    scanf("%d %d", &n, &m);
    int arr[n];

    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // shift
    for (i = 0; i < m % n; i++) {
        shift_one_bit(arr, n);
    }

    for (i = 0; i < n; i++) {
        printf("%d%s", arr[i], i + 1 == n ? "\n" : " ");
    }

    return 0;
}
