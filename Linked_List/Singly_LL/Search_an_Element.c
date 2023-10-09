/**
 * C program to search an element by key in Singly Linked List.
 */
#include <stdio.h>
#include <stdlib.h>

/* Node structure */
struct node
{
    int data;          // Data
    struct node *next; // Address
} * head;


/* Function declaration */
void createList(int n);
void displayList();
int  search(int key);


int main()
{
    int n, keyToSearch, index;

    // Input node count to create
    printf("Enter number of node to create: ");
    scanf("%d", &n);

    createList(n);

    // Display list
    printf("\nData in list: \n");
    displayList();

    // Input element to search from user.
    printf("\nEnter element to search: ");
    scanf("%d", &keyToSearch);

    // Call function to search first element by key
    index = search(keyToSearch);
    
    // Element found in the list
    if (index >= 0)
        printf("%d found in the list at position %d\n", keyToSearch, index + 1);
    else
        printf("%d not found in the list.\n", keyToSearch);
    

    return 0;
}

/**
 * Create a list of n nodes
 */
void createList(int n)
{
    struct node *newNode, *temp;
    int data, i;

    head = malloc(sizeof(struct node));

    /*
     * Unable to allocate memory, hence exit from app.
     */
    if (head == NULL)
    {
        printf("Unable to allocate memory. Exiting from app.");
        exit(0);
    }
    

    /* Input head node data from user */
    printf("Enter data of node 1: ");
    scanf("%d", &data);

    head->data = data; // Link data field with data
    head->next = NULL; // Link address field to NULL

    temp = head;

    /*
     * Create n nodes and add to the list
     */
    for (i = 2; i <= n; i++)
    {
        newNode = malloc(sizeof(struct node));

        /* If memory is not allocated for newNode */
        if (newNode == NULL)
        {
            printf("Unable to allocate memory. Exiting from app.");
            exit(0);
        }

        printf("Enter data of node %d: ", i);
        scanf("%d", &data);

        newNode->data = data; // Link data field of newNode
        newNode->next = NULL; // The newNode should point to nothing

        temp->next = newNode; // Link previous node i.e. temp to the newNode
        temp = temp->next;
    }
    
}


/**
 * Display entire list
 */
void displayList()
{
    struct node *temp;

    /*
     * If the list is empty i.e. head = NULL,
     * dont perform any action and return.
     */
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    
    temp = head;
    while (temp != NULL)
    {
        printf("%d, ", temp->data);
        temp = temp->next;  // Move to next node
    }
    printf("\n");
}


/**
 * Search an element with given key in linked list.
 * It return a positive integer specifying index of the element 
 * on success, otherwise returns -1.
 */
int search(int key)
{
    int index;
    struct node *curNode;

    index = 0;
    curNode = head;

    // Iterate till last element until key is not found
    while (curNode != NULL && curNode->data != key)
    {
        index++;
        curNode = curNode->next;
    }


    return (curNode != NULL) ? index : -1;
}