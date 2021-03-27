#include <stdio.h>

/* K & R Stack */
#define MAXVAL 100
static int val[MAXVAL];
static int sp = 0;

void push(int ch)
{
    if (sp < MAXVAL) {
        val[sp++] = ch;
    } else {
        // stack full
    }
}

int pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        return -1;
    }
}

int isEmpty(void) { return sp == 0; }

int isLeftSymbol(int ch);
int getMatcher(int ch);
const char* getOriginalSymbol(int ch);

int main()
{
    char symbols[100];
    char line[1000];
    char result[100] = "YES\n";
    int i, index, ch;
    index = 0;

    // 读所有的要配对的符号
    while (fgets(line, sizeof(line)/sizeof(line[0]), stdin) != NULL) {
        if (line[0] == '.' && line[1] == '\n') {
            break;
        }
        for (i = 0; line[i] != '\0'; i++) {
            ch = line[i];
            if (line[i] == '/' && line[i+1] == '*') {
                symbols[index++] = '<';
                i++;
            } else if (line[i] == '*' && line[i+1] == '/') {
                symbols[index++] = '>';
                i++;
            } else if (ch == '(' || ch == ')' ||
                       ch == '[' || ch == ']' ||
                       ch == '{' || ch == '}')
            {
                symbols[index++] = ch;
            }
        }
    }
    symbols[index] = '\0';
    
    // printf("%s\n", symbols);    /* 输出所有读到的符号 */

    /* 检查符号匹配 */
    for (i = 0; i < index; i++) {
        int ch = symbols[i];
        if (isLeftSymbol(ch)) { /* 是左边的符号，push 到堆栈里面去 */
            push(symbols[i]);
        } else {    /* 是右边的符号 */
            int leftSymbol = pop(); /* 从堆栈取出要匹配的左边的符号 */
            if (leftSymbol != -1) { /* 还有左边的符号 */
                int rightSymbol = getMatcher(leftSymbol);
                if (rightSymbol != ch) {    /* 左边符号想要的右符号是不是现在遇到的右边的符号（ch） */
                    sprintf(result, "NO\n%s-?\n", getOriginalSymbol(leftSymbol));
                    break;
                }
            } else {    /* 当前遇到的符号没有左符号来匹配 */
                sprintf(result, "NO\n?-%s\n", getOriginalSymbol(ch));
                break;
            }
        }
    }

    if (i == index && !isEmpty()) {    /* 匹配完所有的括号后，如果堆栈不为空有多余的左括号/符号 */
        sprintf(result, "NO\n%s-?\n", getOriginalSymbol(pop()));
    }

    printf("%s", result);
    return 0;
}


int isLeftSymbol(int ch)
{
    return ch == '<' || ch == '(' || ch == '[' || ch == '{';
}

int getMatcher(int ch)
{
    static int map[128] = {
        ['<'] = '>', 
        ['>'] = '<',
        ['('] = ')',
        [')'] = '(',
        ['['] = ']',
        [']'] = '[',
        ['{'] = '}',
        ['}'] = '{'
    };

    return ch >= 0 && ch < 128 ? map[ch] : 0;
}

const char* getOriginalSymbol(int ch)
{
    static const char *symbols[128] = {
        ['<'] = "/*",
        ['>'] = "*/",
        ['('] = "(",
        [')'] = ")",
        ['['] = "[",
        [']'] = "]",
        ['{'] = "{",
        ['}'] = "}",
    };

    return ch >= 0 && ch < 128 ? symbols[ch] : "";
}
