#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int key;
    int height;
    struct node* left;
    struct node* right;
}node;

int height(node* p)
{
        return p?p->height:0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl>hr?hl:hr) + 1;
}

node* rotateright(node* p)
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q)
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p)
{
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

node* makenode(int k)
{
    node *node1 = (node *) malloc(sizeof(node));
    node1->left = 0;
    node1->right = 0;
    node1->height = 1;
    node1->key = k;
    return node1;
}

node* insert(node* p, int k)
{
    if( !p ) return makenode(k);
    if( k<p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
}

void freeNode(node *root)
{
    if (root == NULL) {
        return;
    }
    freeNode(root->left);
    freeNode(root->right);
    free(root);
}

int main() {
    int n, i, k;
    node *root;
    root=NULL;
    scanf("%d", &n);
    if (n==0) printf("%d", 0 );
    else {
        for (i = 0; i < n; i++) {
            scanf("%d", &k);
            root=insert(root, k);
        }
        printf("%d", height(root));
    }
    freeNode(root);
    return 0;
}
