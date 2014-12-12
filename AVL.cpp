#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <queue>

using namespace std;


struct node
{
    int data;
    int height;
    node * left;
    node * right;
};


inline int max(int a, int b)
{
    return a>b?a:b;
}

int High(node * root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

void LeftRonate(node * & root)
{
    node * temp = root;
    root = root -> left;

    temp -> left = root -> right;
    root -> right = temp;

    temp -> height = max(High(temp -> left), High(temp -> right)) + 1;
    root -> height = max(High(root -> left), temp -> height) + 1;
}
void RightRonate(node * & root)
{
    node * temp = root;
    root = root -> right;

    temp -> right = root -> left;
    root -> left = temp;

    temp -> height = max(High(temp -> left), High(temp -> right)) + 1;
    root -> height = max(High(root -> right), temp -> height) + 1;
}
void LeftRightRonate(node * & root)
{
    /*
    node * temp = root;
    root = root -> left;

    temp -> left = root -> left;
    root -> left = temp;

    temp -> height = max(High(temp -> left), High(temp -> right)) + 1;
    root -> height = max(High(root -> right), temp -> height) + 1;
    */
    RightRonate(root -> left);
    LeftRonate(root);
}
void RightLeftRonate(node * & root)
{
    /*
    node * temp = root;
    root = root -> right;

    temp -> right = root -> right;
    root -> right = temp;

    temp -> height = max(High(temp -> left), High(temp -> right)) + 1;
    root -> height = max(High(root -> left), temp -> height) + 1;
    */
    LeftRonate(root -> right);
    RightRonate(root);
}

void InsertNode(node * & root, int data)
{
    if (root == NULL)
    {
        root = (node *)malloc(sizeof(node));
        root -> data = data;
        root -> left = NULL;
        root -> right = NULL;
    }
    else if (data > root -> data) 
    {
        InsertNode(root -> right, data);
        if (High(root -> right) - High(root -> left) == 2)
        {
            if (High(root -> right -> left) > High(root -> right -> right))
                RightLeftRonate(root);
            else 
                RightRonate(root);
        }
    }
    else if (data < root -> data)
    {
        InsertNode(root -> left, data);
        if (High(root -> left) - High(root -> right) == 2)
        {
            if (High(root -> left -> right) > High(root -> left -> left))
                LeftRightRonate(root);
            else
                LeftRonate(root);
        }
    }
    root -> height = max(High(root -> left),High(root -> right)) + 1;
}

void inorder(node * root)
{
    if (root == NULL)
        return ;
    inorder(root -> left);
    printf("%d(%d)\t", root -> data, root -> height);
    inorder(root -> right);
}
void quprint(node * root)
{
    queue<node*> q;
    q.push(root);
    while(!q.empty())
    {
        node * cur = q.front();
        q.pop();

        printf("%d(%d)\t", cur -> data, cur -> height);

        if (cur -> left != NULL)
            q.push(cur -> left);
        if (cur -> right != NULL)
            q.push(cur -> right);
    }
}

void DeleteAVLNode(node * & root, int data)
{
    if (root == NULL)
        return;
    
    if (data < root -> data)
    {
        DeleteAVLNode(root -> left, data);
        if (High(root -> right) - High(root -> left) == 2)
        {
            if (High(root -> right -> left) > High(root -> right -> right))
                RightLeftRonate(root);
            else
                RightRonate(root);
        }
    }
    else if (data > root -> data)
    {
        DeleteAVLNode(root -> right, data);
        if (High(root -> left) - High(root -> right) == 2)
        {
            if (High(root -> left -> right) - High(root -> left -> left))
                LeftRightRonate(root);
            else
                LeftRonate(root);
        }
    }
    else
    {
        if (root -> left && root -> right)
        {
            node * temp = root -> right;
            while(temp -> left != NULL)
                temp = temp -> left;
            root -> data = temp -> data;
            DeleteAVLNode(root -> right, temp -> data);
            if (High(root -> left) - High(root -> right) == 2)
            {
                if (High(root -> left -> right) - High(root -> left -> left))
                    LeftRightRonate(root);
                else
                    LeftRonate(root);
            }
        }
        else
        {
            node * temp = root;
            if (root -> left == NULL)
                root = root -> right;
            else if (root -> right == NULL)
                root = root -> left;
            free(temp);
        }
    }
    if (root == NULL)
        return ;
    root -> height = max(High(root -> right), High(root -> left)) + 1;
}
int main()
{
    node * root = NULL;
    int x;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    //    InsertNode(root, rand()%100);
    {
        scanf("%d", &x);
        InsertNode(root, x);
    }

    //inorder(root);
    quprint(root);
    printf("\n\n");
    scanf("%d", &x);
    DeleteAVLNode(root, x);
    quprint(root);
}
