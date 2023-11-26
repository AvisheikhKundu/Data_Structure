#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};
typedef struct Node node;
node *createNode(){
    int data;
    node *newnode;
    newnode=(node*)malloc(sizeof(node));
    printf("Enter data (-1 for no node)\n");
    scanf("%d",&data);
    if (data==-1){
        return 0;
    }
    newnode->data=data;
    printf("Enter left child of %d\n",data);
    newnode->left=createNode();
    printf("Enter right child of %d\n",data);
    newnode->right=createNode();
    return newnode;

}
//preorder treversal.
// root-left-right.
void preorder(node *root){
    if (root==0){
        return;
    }
    printf("%d\t",root->data);
    preorder(root->left);
    preorder(root->right);

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
//left right root.
void postorder(node *root){
        if (root==0){
        return;
    }
    
    postorder(root->left);
    
    postorder(root->right);
    printf("%d\t",root->data);
}
int main(){
    node *root;
    root=0;
    root=createNode();
    printf("Traversed preorder\n");
    preorder(root);
    printf("\nTreversed interorder\n");
    inorder(root);
    printf("\nTreversed postorder\n");
    postorder(root);


    return 0;
}