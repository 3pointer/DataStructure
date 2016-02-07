#include<bits/stdc++.h>

using namespace std;

#define RED 0
#define BLACK 1

class bst{
private:

    struct node{
        int val;
        bool color;
        node * Left, * Right, * parent;

        node (int x){
            color = RED;
            Left = NULL;
            Right = NULL;
            parent = NULL;
            val = x;
        }

        node * grandparent(){
            if (parent == NULL){
                return NULL;
            }
            return parent -> parent;
        }

        node * uncle(){
            if (grandparent() == NULL){
                return NULL;
            }
            if (parent == grandparent() -> Right){
                return grandparent() -> Left;
            } else {
                return grandparent() -> Right;
            }
        }
        node * sibling(){
            if (parent -> Left == this){
                return parent -> Right;
            } else {
                return parent -> Left;
            }
        }
    };

    node * root, *NIL;

    void rotate_right(node * p){
        node *gp = p -> grandparent();
        node *fa = p -> parent;
        node *y = p -> Right;

        fa -> Left = y;
        if (y != NIL){
            y -> parent = fa;
        }
        p -> Right = fa;
        fa -> parent = p;

        if (root == fa){
            root = p;
        }
        p -> parent = gp;
        if (gp != NULL){
            if (gp -> Left == fa){
                gp -> Left = p;
            } else {
                gp -> Right = p;
            }

        }
    }

    void rotate_left(node *p){
        node *gp = p -> grandparent();
        node *fa = p -> parent;
        node *y = p -> Left;

        fa -> Right = y;
        if (y != NIL){
            y -> parent = fa;
        }
        p -> Left = fa;
        fa -> parent = p;

        if (root == fa){
            root = p;
        }
        p -> parent = gp;
        if (gp != NULL){
            if (gp -> Left == fa){
                gp -> Left = p;
            } else {
                gp -> Right = p;
            }
        }

    }

    void inorder(node *p) {
        if (p == NIL){
            return;
        }
        inorder(p -> Left);
        cout << p -> val << endl;
        inorder(p -> Right);
    }

    string outputColor(bool color){
        return color ? "BLACK" : "RED";
    }

    node * getSmallestChild(node *p){
        if (p -> Left == NIL){
            return p;
        }
        return getSmallestChild(p -> Left);
    }

    void insert(node *p, int data){
        if (p -> val >= data){
            if (p -> Left != NIL){
                insert(p -> Left, data);
            } else {
                node * tmp = new node(data);
                tmp -> parent = p;
                tmp -> Left = tmp -> Right = NIL;
                p -> Left = tmp;
                insert_case(tmp);
            }
        } else {
            if (p -> Right != NIL){
                insert(p -> Right, data);
            } else {
                node * tmp = new node(data);
                tmp -> parent = p;
                tmp -> Left = tmp -> Right = NIL;
                p -> Right = tmp;
                insert_case(tmp);
            }
        }
    }

    void insert_case(node *p){
        if (p -> parent == NULL){           // 第一种情况 root 的情况 这里不可能发生
            root = p;
            p -> color = BLACK;
            return;
        }

        if (p -> parent -> color == RED){
            if (p -> uncle() -> color == RED){
                p -> parent -> color = p -> uncle() -> color = BLACK;
                p -> grandparent() -> color = RED;
                insert_case(p -> grandparent());
            } else {
                if (p -> parent -> Right == p && p -> grandparent() -> Left == p -> parent){
                    rotate_left(p);
                    rotate_right(p);
                    p -> color = BLACK;
                    p -> Left = p -> Right = RED;
                } else if (p -> parent -> Left == p && p -> grandparent() -> Right == p -> parent){
                    rotate_right(p);
                    rotate_left(p);
                    p -> color = BLACK;
                    p -> Left -> color = p -> Right -> color = RED;
                } else if (p -> parent -> Left == p && p -> grandparent() -> Left == p -> parent){
                    p -> parent -> color = BLACK;
                    p -> grandparent() -> color = RED;
                    rotate_right(p -> parent);
                } else if (p -> parent -> Right == p && p -> grandparent() -> Right == p -> parent){
                    p -> parent -> color = BLACK;
                    p -> grandparent() -> color = RED;
                    rotate_left(p -> parent);
                }
            }
        }
    }

    void DeleteTree(node *p){
        if (p == NULL){
            return ;
        }
        DeleteTree(p -> Left);
        DeleteTree(p -> Right);
        delete p;
    }

public:
    bst(){
        NIL = new node(0);
        NIL -> color = BLACK;
        root = NULL;
    }

    void insert(int x){
        if (root == NULL){
            root = new node(x);
            root -> color = BLACK;
            root -> Left = root -> Right = NIL;
        } else {
            insert(root, x);
        }
    }
};

int main(){
    return 0;
}

