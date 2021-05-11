/**
 * Author: 王调科
 * E-mail: 960485902@qq.com 
 */
#include <stdlib.h>
#include <stdio.h>

struct action {
    int plate;  /* number of plate */
    char from;  /* A */
    char temp;  /* B */
    char dest;  /* C */
};

struct node {
    struct action a;
    struct node *next;
};

static struct node* head = NULL;
static int stack_size = 0;

static void push(struct action a)
{
    struct node* p = malloc(sizeof(struct node));
    p->a = a;
    p->next = head;
    head = p;
    stack_size++;
}

static struct action pop(void)
{
    struct action ret;
    struct node *old = head;
    if (head != NULL) {
        ret = head->a;
        head = head->next;
        stack_size--;
    }
    return ret;
}

static int size() { return stack_size; }

int main()
{
    int n;
    struct action ac;

    scanf("%d", &n);


    ac = (struct action){n, 'a', 'b', 'c'}; 
    
    /* Do a 柱 -> c 柱 */
    push(ac);
    while (ac.plate > 1) {
        ac = (struct action){ac.plate - 1, ac.from, ac.dest, ac.temp};  /* a -> b or a -> c */
        push(ac);
    }

    while (size() > 0) {
        ac = pop();
        printf("%c -> %c\n", ac.from, ac.dest); /* from -> dest */

        if (ac.plate > 1) {
            ac = (struct action){ac.plate - 1, ac.temp, ac.from, ac.dest};  /* Represent b 柱 -> c 柱 */
            /* Do a 柱 -> c 柱 */
            push(ac);
            while (ac.plate > 1) {
                ac = (struct action){ac.plate - 1, ac.from, ac.dest, ac.temp};  /* a -> b or a ->c */
                push(ac);
            }
        }

    }
    return 0;
}
