#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void push(int v);
int pop(void);
int isEmpty(void);
int peek(void);

// 运算符优先级
int oprank(int op)
{
    static int pre[] = {
        ['*'] = 1,
        ['/'] = 1,
        ['+'] = 2,
        ['-'] = 2,
        ['('] = 3
    };
    return pre[op];
}


// 格式：当 push +-*/ 的时候输出一个空格，输出运算符的时候输出一个空格
int main(int argc, char const *argv[])
{
    int i;
    char s[21];
    scanf("%s", s);

    for (i = 0; s[i] != '\0'; i++) {
        // operand
        if (!isdigit(s[i]) && ((s[i] == '+' || s[i] == '-') && (i == 0 || s[i-1] == '(')) || s[i] == '.') {  /* 数字前面的正负号, . */
            // print sign
            if (s[i] == '-') {
                printf("-");
            } else if (s[i] == '.') {
                printf(".");
            }
        } else if (isdigit(s[i])) {
            // print digit
            printf("%c", s[i]);
        } else {
            
            int op;
            // operator

            switch (s[i]) {
            case '(':
                push(s[i]);
                break;
            case ')':
                while ((op = pop()) != '(') {
                    printf(" %c", op);
                }
                break;
            default:
                if (isEmpty()) {
                    push(s[i]);
                    printf(" ");
                } else {
                    while (!isEmpty() && oprank(peek()) <= oprank(s[i])) {
                        printf(" %c", pop());
                    }
                    push(s[i]);
                    printf(" ");
                }
            }
        }
    }
    while (!isEmpty())
    {
        printf(" %c", pop());
    }
    
    return 0;
}

#define MAXVAL 100
static int val[MAXVAL];
static int sp = 0;

void push(int v)
{
    if (sp < MAXVAL) {
        val[sp++] = v;
    } else {
        printf("stack is full\n");
    }
}

int pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("stack is empty\n");
        return 0;
    }
}

int isEmpty(void)
{
    return sp == 0;
}

int peek(void)
{
    return val[sp-1];
}