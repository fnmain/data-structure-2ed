#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y)   ((x) > (y) ? (x) : (y))

struct tnode {
    int number;
    int height;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void) { return (struct tnode*)malloc(sizeof(struct tnode)); }

int height(struct tnode *root)
{
    if (root) {
        return root->height;
    }
    return 0;
}

void tree_update_height(struct tnode *root)
{
    if (root)
        root->height = MAX(height(root->left), height(root->right)) + 1;
}

int get_balance(struct tnode *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

struct tnode *left_rotate(struct tnode *root)
{
    struct tnode *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    tree_update_height(root);
    return temp;
}

struct tnode *right_rotate(struct tnode *root)
{
    struct tnode *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    tree_update_height(root);
    return temp;
}

int balance(struct tnode *node)
{
    int res;
    if ((res = height(node->left) - height(node->right)) > 1 || res < -1) {
        return 0;
    }
    return 1;
}

struct tnode *rebalance(struct tnode *root)
{
    if (height(root->left) - height(root->right) > 1) {
        if (height(root->left->left) > height(root->left->right)) {
            // right rotate
            root = right_rotate(root);
        } else {
            // left right rotate
            root->left = left_rotate(root->left);
            root = right_rotate(root);
        }
    } else {
        if (height(root->right->right) > height(root->right->left)) {
            // left rotate
            root = left_rotate(root);
        } else {
            // right left rotate
            root->right = right_rotate(root->right);
            root = left_rotate(root);
        }
    }
    return root;
}

struct tnode *addtree(struct tnode *root, int val)
{
    int bf;
    if (root == NULL) {
        root = talloc();
        root->number = val;
        root->height = 0;
        root->left = root->right = NULL;
    } else if (root->number < val) {
        root->left = addtree(root->left, val);
    } else if (root->number > val) {
        root->right = addtree(root->right, val);
    }

    /* update tree height */
    root->height = MAX(height(root->left), height(root->right)) + 1;

    if (!balance(root)) {
        // rebalance
        root = rebalance(root);
    }

    return root;
}

int main(int argc, char const *argv[])
{
    int n, x;

    struct tnode *root = NULL;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = addtree(root, x);
    }
    printf("%d\n", root->number);
    return 0;
}
