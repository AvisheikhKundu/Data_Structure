
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    char name[100];
    struct Node *next;
    struct Node *previous;
};

typedef struct Node node;

node* createNode(int data, const char* name) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    newNode->next = NULL;
    newNode->previous = NULL;

    return newNode;
}

node* insertNode(node* head, int data, const char* name) {
    node* newNode = createNode(data, name);
    if (head == NULL) {
        newNode->next = newNode;
        newNode->previous = newNode;
        return newNode;
    }

    newNode->next = head;
    newNode->previous = head->previous;
    head->previous->next = newNode;
    head->previous = newNode;
    return head;
}

void traversal(node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    node* current = head;
    do {
        printf("%d %s\n", current->data, current->name);
        current = current->next;
    } while (current != head);
}

void freeList(node* head) {
    if (head == NULL) {
        return;
    }

    node* current = head;
    do {
        node* temp = current;
        current = current->next;
        free(temp);
    } while (current != head);
}

int main() {
    node* head = NULL;
    head = insertNode(head, 100, "a");
    head = insertNode(head, 200, "b");
    head = insertNode(head, 300, "c");
    head = insertNode(head, 400, "d");
    head = insertNode(head, 500, "d");
    head = insertNode(head, 600, "d");
    head = insertNode(head, 700, "d");
    head = insertNode(head, 800, "d");


    traversal(head);
    freeList(head);

    return 0;
}
