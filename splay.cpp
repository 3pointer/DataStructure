#include <stdio.h>
#include <stdlib.h>
#define NUM 50

int size;

struct tree_node
{
    int item;
    struct tree_node * left;
    struct tree_node * right;
};

tree_node * splay(int i, tree_node * t)
{
    tree_node N, *l, *r, *y;

    if (t == NULL)
    return t;

    N.left = N.right = NULL;
    l = r = &N;

    for (;;)
    {
        if (i < t->item)
        {
            if (t->left == NULL)
            break;
            if (i < t->left->item)
            {
                y = t->left;
                t->left = y->right;
                t = y;
                if (t->left == NULL)
                break;
            }
            r->left = t;
            r = t;
            t = t->left;
        }
        else if (i > t->item)
        {
            if (t->right == NULL)
            break;
            if (i > t->right->item)
            {
                y = t->right;
                t->right = y->left;
                y->left = t;
                t = y;
                if (t->right == NULL)
                break;
            }
            l->right = t;
            l = t;
            t = t->right;
        }
        else
        break;
    }
    l->right = t->left;
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;
return t;
}

tree_node * ST_insert(int i, tree_node * t)
{
    tree_node * node;
    node = (tree_node*)malloc(sizeof(tree_node));
    node->item = i;
    if (t == NULL)
    {
        node->left = node->right = NULL;
        size = 1;
        return node;
    }
    t = splay(i, t);
    if (i < t->item)
    {
        node->left = t->left;
        node->right = t;
        t->left = NULL;
        size++;
        return node;
    }
    else if (i > t->item)
    {
        node->right = t->right;
        node->left = t;
        t->right = NULL;
        size++;
        return node;
    }
    else
    {
        free(node);
        return t;
    }
}
tree_node * ST_delete(int i, tree_node * t)
{
    tree_node * x;
    if (t == NULL)
    return NULL;
    t = splay(i, t);
    if (i == t->item)
    {
        if (t->left == NULL)
        {
            x = t->right;
        }
        else
        {
            x = splay(i, t->left);
            x->right = t->right;
        }
        size--;
        free(t);
        return x;
    }
    return t;
}
void ST_inorder(tree_node * node)
{
    if (node ==  NULL)
    return;
    ST_inorder(node->left);
    printf("%d ", node->item);
    ST_inorder(node->right);
}
int main()
{
    tree_node * root;
    int i;
    root = NULL;
    size = 0;
    for (int i = 0; i < NUM; i++)
    root = ST_insert(rand()%NUM, root);
    ST_inorder(root);
    for (int i = 0; i < NUM; i++)
    root = ST_delete(i, root);
    printf("\nsize=%d\n", size);
    return 0;
}
