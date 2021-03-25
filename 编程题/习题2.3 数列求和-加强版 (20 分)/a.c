#include <stdio.h>

int main()
{
    // S = A + AA + ... + AA..A(N个A)
    int S, N, A, T, i, j, carry;
    i = 0;

    scanf("%d %d", &A, &N);
    int numbers[N + 1];
    if (N != 0) {
        carry = 0;
        for (i = 0; i < N; i++) {
            numbers[i] = ((N-i) * A + carry) % 10;
            carry = ((N-i) * A + carry) / 10;
        }

        if (carry > 0) {
            numbers[i++] = carry;
        }
    } else {
        numbers[i++] = 0;
    }


    for (j = i - 1; j >= 0; j--) {
        printf("%d", numbers[j]);
    }
    printf("\n");

    return 0;
}
