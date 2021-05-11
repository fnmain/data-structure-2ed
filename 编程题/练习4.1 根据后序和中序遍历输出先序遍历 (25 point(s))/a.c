#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int value;
    struct tnode *left;
    struct tnode *right;
};

struct list {
    int *v;
    int size;
};

struct tnode* talloc(void) { return (struct tnode*)malloc(sizeof(struct tnode)); }

struct tnode* tree(int postorder[], int start, int end, int inorder[], int x, int y)
{
    int pos;   /* position of root in Inorder */
    struct tnode *root = NULL;

    if (start <= end) {
        root = talloc();
        root->value = postorder[end];
        for (pos  = x; pos <= y; pos++) {
            if (inorder[pos] == root->value) {
                break;
            }
        }
        int num_rtree = y - pos;
        int num_ltree = pos - x;
        root->left = tree(postorder, start, start + num_ltree - 1, inorder, x, pos - 1);
        root->right = tree(postorder, end - num_rtree, end - 1, inorder, pos + 1, y);
    }

    return root;
}

void traversal(struct tnode *root, struct list *plist)
{
    if (root) {
        plist->v[plist->size++] = root->value;
        traversal(root->left, plist);
        traversal(root->right, plist);
    }
}

void read(int v[], int n)
{
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

int main()
{
    int i, n;

    scanf("%d", &n);
    int postorder[n];
    int inorder[n];

    read(postorder, n);
    read(inorder, n);

    struct tnode *root = tree(postorder, 0, n-1, inorder, 0, n-1);
    struct list preorder = {(int*)malloc(sizeof(int)*n), 0};
    
    traversal(root, &preorder);

    printf("Preorder: ");
    for (i = 0; i < preorder.size; i++) {
        printf("%d%s", preorder.v[i], i + 1 == preorder.size ? "\n" : " ");
    }

    return 0;
}