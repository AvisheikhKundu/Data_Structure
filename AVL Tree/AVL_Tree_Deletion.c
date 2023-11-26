#include <stdio.h>
#include <stdlib.h>
struct Node {
   int data;
   struct Node *leftChild;
   struct Node *rightChild;
   int height;
};
int max(int a, int b);
int height(struct Node *N){
   if (N == NULL)
      return 0;
   return N->height;
}
int max(int a, int b){
   return (a > b) ? a : b;
}
struct Node *newNode(int data){
   struct Node *node = (struct Node *) malloc(sizeof(struct Node));
   node->data = data;
   node->leftChild = NULL;
   node->rightChild = NULL;
   node->height = 1;
   return (node);
}
struct Node *rightRotate(struct Node *y){
   struct Node *x = y->leftChild;
   struct Node *T2 = x->rightChild;
   x->rightChild = y;
   y->leftChild = T2;
   y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
   x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
   return x;
}
struct Node *leftRotate(struct Node *x){
   struct Node *y = x->rightChild;
   struct Node *T2 = y->leftChild;
   y->leftChild = x;
   x->rightChild = T2;
   x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
   y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
   return y;
}
int getBalance(struct Node *N){
   if (N == NULL)
      return 0;
   return height(N->leftChild) - height(N->rightChild);
}
struct Node *insertNode(struct Node *node, int data){
   if (node == NULL)
      return (newNode(data));
   if (data < node->data)
      node->leftChild = insertNode(node->leftChild, data);
   else if (data > node->data)
      node->rightChild = insertNode(node->rightChild, data);
   else
      return node;
   node->height = 1 + max(height(node->leftChild),
                     height(node->rightChild));
   int balance = getBalance(node);
   if (balance > 1 && data < node->leftChild->data)
      return rightRotate(node);
   if (balance < -1 && data > node->rightChild->data)
      return leftRotate(node);
   if (balance > 1 && data > node->leftChild->data) {
      node->leftChild = leftRotate(node->leftChild);
      return rightRotate(node);
   }
   if (balance < -1 && data < node->rightChild->data) {
      node->rightChild = rightRotate(node->rightChild);
      return leftRotate(node);
   }
   return node;
}
struct Node *minValueNode(struct Node *node){
   struct Node *current = node;
   while (current->leftChild != NULL)
      current = current->leftChild;
   return current;
}
struct Node *deleteNode(struct Node *root, int data){
   if (root == NULL)
      return root;
   if (data < root->data)
      root->leftChild = deleteNode(root->leftChild, data);
   else if (data > root->data)
      root->rightChild = deleteNode(root->rightChild, data);
   else {
      if ((root->leftChild == NULL) || (root->rightChild == NULL)) {
         struct Node *temp = root->leftChild ? root->leftChild : root->rightChild;
         if (temp == NULL) {
            temp = root;
            root = NULL;
         } else
            *root = *temp;
         free(temp);
      } else {
         struct Node *temp = minValueNode(root->rightChild);
         root->data = temp->data;
         root->rightChild = deleteNode(root->rightChild, temp->data);
      }
   }
   if (root == NULL)
      return root;
   root->height = 1 + max(height(root->leftChild),
                     height(root->rightChild));
   int balance = getBalance(root);
   if (balance > 1 && getBalance(root->leftChild) >= 0)
      return rightRotate(root);
   if (balance > 1 && getBalance(root->leftChild) < 0) {
      root->leftChild = leftRotate(root->leftChild);
      return rightRotate(root);
   }
   if (balance < -1 && getBalance(root->rightChild) <= 0)
      return leftRotate(root);
   if (balance < -1 && getBalance(root->rightChild) > 0) {
      root->rightChild = rightRotate(root->rightChild);
      return leftRotate(root);
   }
   return root;
}

// Print the tree
void printTree(struct Node *root){
   if (root != NULL) {
      printTree(root->leftChild);
      printf("%d ", root->data);
      printTree(root->rightChild);
   }
}
int main(){
   struct Node *root = NULL;
   root = insertNode(root, 22);
   root = insertNode(root, 14);
   root = insertNode(root, 72);
   root = insertNode(root, 44);
   root = insertNode(root, 25);
   root = insertNode(root, 63);
   root = insertNode(root, 98);
   printf("AVL Tree: ");
   printTree(root);
   root = deleteNode(root, 25);
   printf("\nAfter deletion: ");
   printTree(root);
   return 0;
}