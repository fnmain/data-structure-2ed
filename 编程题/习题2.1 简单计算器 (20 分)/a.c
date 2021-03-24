#include <stdio.h>

int read_int(void)
{
    int ret;
    scanf("%d", &ret);
    return ret;
}

int main()
{
    int result;
    int ret;
    scanf("%d", &result);
    while ( 1 ) {
        char op = getchar();
        switch (op)
        {
        case '+':
            ret = read_int();
            result = result + ret;
            break;
        case '-':
            ret = read_int();
            result = result - ret;
            break;
        case '*':
            ret = read_int();
            result = result * ret;
            break;
        case '/':
            ret = read_int();
            if (ret == 0) {
                printf("ERROR\n");
                return 0;
            }
            result = result / ret;
            break;
        case '=':
            printf("%d\n", result);
            return 0;
        default:
            printf("ERROR\n");
            return 0;
            break;
        }
    }
    return 0;
}
