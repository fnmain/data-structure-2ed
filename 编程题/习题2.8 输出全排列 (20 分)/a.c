#include <stdio.h>
// 123
// 132
// 213
// 231
#define N 20
static int stack[N];
static int sp = 0;

void push(int x)
{
    stack[sp++] = x;
}

int pop(void)
{
    return stack[--sp];
}

void dfs(int n, int depth)
{
    static int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
    static int printed[sizeof(numbers)/sizeof(int)] = {0};

    if (depth + 1 > n) {
        for (int i = 0; i < sp; i++) {
            printf("%d", stack[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!printed[numbers[i]]) {
            printed[numbers[i]] = 1;
            push(numbers[i]);
            dfs(n, depth + 1);
            pop();
            printed[numbers[i]] = 0;
        }
    }
}

int main()
{
    int n;

    scanf("%d", &n);
    dfs(n, 0);
    return 0;
}
