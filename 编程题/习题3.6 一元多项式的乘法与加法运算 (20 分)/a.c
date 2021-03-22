#include <stdio.h>
#include <stdlib.h>

typedef struct _item {
    int coe;
    int exp;
    struct _item *next;
} Item;

typedef struct _polynomial {
    Item *head;
    Item *tail;
} Polynomial;

void append_item(Polynomial *p, int coe, int exp)
{
    Item *item = malloc(sizeof(Item));
    item->coe = coe;
    item->exp = exp;
    item->next = NULL;
    // add to linked-list
    if (p->tail) {
        p->tail->next = item;
        p->tail = item;
    } else {
        p->head = p->tail = item;
    }
}

Polynomial read_polynomial(void)
{
    int n, coe, exp;
    scanf("%d", &n);

    Polynomial p = {NULL, NULL};
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coe, &exp);
        if (coe != 0)
            append_item(&p, coe, exp);
        // Item *item = malloc(sizeof(Item));
        // item->coe = coe;
        // item->exp = exp;
        // item->next = NULL;
        // // add to linked-list
        // if (p.tail) {
        //     p.tail->next = item;
        //     p.tail = item;
        // } else {
        //     p.head = p.tail = item;
        // }
    }
    return p;
}

Polynomial add(const Polynomial *poly1, const Polynomial *poly2)
{
    Polynomial p = {NULL, NULL};

    Item *pi1 = poly1 != NULL ? poly1->head : NULL;
    Item *pi2 = poly2 != NULL ? poly2->head : NULL;

    while (pi1 != NULL && pi2 != NULL) {
        if (pi1->exp == pi2->exp) {
            if (pi1->coe + pi2->coe != 0)
                append_item(&p, pi1->coe + pi2->coe, pi2->exp);
            pi1 = pi1->next;
            pi2 = pi2->next;
        } else if (pi1->exp > pi2->exp) {
            append_item(&p, pi1->coe, pi1->exp);
            pi1 = pi1->next;
        } else {
            append_item(&p, pi2->coe, pi2->exp);
            pi2 = pi2->next;
        }
    }

    while (pi1 != NULL) {
        append_item(&p, pi1->coe, pi1->exp);
        pi1 = pi1->next;
    }
    while (pi2 != NULL) {
        append_item(&p, pi2->coe, pi2->exp);
        pi2 = pi2->next;
    }

    if (p.head == NULL) {
        append_item(&p, 0, 0);
    }
    return p;
}

void free_polynomial(const Polynomial *poly)
{
    Item *q = NULL;
    for (Item *pi = poly->head; pi != NULL; pi = q) {
        q = pi->next;
        free(pi);
    }
}

Polynomial multiply(const Polynomial *poly1, const Polynomial *poly2)
{
    Polynomial result = {NULL, NULL};
    Polynomial last_result = {NULL, NULL};
    for (Item *pi = poly1->head; pi != NULL; pi = pi->next) {
        Polynomial temp = {NULL, NULL};
        for (Item *prhs = poly2->head; prhs != NULL; prhs = prhs->next) {
            append_item(&temp, pi->coe * prhs->coe, pi->exp + prhs->exp);
        }
        last_result = result;
        result = add(&last_result, &temp);
        free_polynomial(&temp);
        free_polynomial(&last_result);
    }
    result = add(&result, NULL);
    return result;
}

void print_polynomial(const Polynomial *poly)
{
    for (Item *pi = poly->head; pi != NULL; pi = pi->next) {
        printf("%d %d%s", pi->coe, pi->exp, pi->next != NULL ? " " : "\n");
    }
}

int main()
{
    Polynomial p1 = read_polynomial();
    Polynomial p2 = read_polynomial();

    Polynomial multiply_result = multiply(&p1, &p2);
    Polynomial add_result = add(&p1, &p2);
    print_polynomial(&multiply_result);
    print_polynomial(&add_result);

    free_polynomial(&p1);
    free_polynomial(&p2);
    free_polynomial(&multiply_result);
    free_polynomial(&add_result);
    return 0;
}
