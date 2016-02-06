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

        node (){
            color = RED;
            Left = NULL;
            Right = NULL;
            parent = NULL;
            val = 0;
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
        if (y != NULL){
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
        if (y != NULL){
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
};

int main(){
    return 0;
}

