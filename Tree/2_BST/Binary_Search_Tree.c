#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} node;

node* createnode(int value) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;

}
//left -root-right
void inorder(node *root){
        if (root==0){
        return;
    }
    
    inorder(root->left);
    printf("%d\t",root->data);
    inorder(root->right);
}
int isBST(node *root){
    static node *prev=NULL;
    if (root!=NULL){
        if (!isBST(root->left)){
            return 0;
        }
        if (prev!=NULL && root->data<=prev->data){
            return 0;
        }
        prev=root;
        return isBST(root->right);
    }
    else 
    return 1;
}

int main(){
    node *p=createnode(5);
    node *p1=createnode(3);
    node *p2=createnode(6);
    node *p3=createnode(1);
    node *p4=createnode(4);

    p->left=p1;
    p->right=p2;
    p1->left=p3;
    p1->right=p4;

    inorder(p);
    printf("\n%d",isBST(p));
    return 0;
}
