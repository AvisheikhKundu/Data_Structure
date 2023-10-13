/*
 * C program to swap two nodes in a linked list.
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
int  count(struct node *list);
int  swap(struct node *list, int pos1, int pos2);


int main()
{
    int n, pos1, pos2;

    // Input node count to create
    printf("Enter number of node to create: ");
    scanf("%d", &n);

    createList(n);

    // Display list
    printf("\n\nData in list before swapping: \n");
    displayList();

    printf("\nEnter first node position to swap: ");
    scanf("%d", &pos1);
    printf("\nEnter second node position to swap: ");
    scanf("%d", &pos2);

    if (swap(head, pos1, pos2) == 1)
    {
        printf("\nData swapped successfully.\n");
        printf("Data in list after swapping %d node with %d: \n", pos1, pos2);
        displayList();
    }
    else 
    {
        printf("Invalid position, please enter position greater than 0 and less than nodes in list.\n");
    }

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
        printf("%d, ", temp->data);     // Print data of current node
        temp = temp->next;              // Move to next node
    }
    printf("\n");
}


/**
 * Counts total number of nodes in a linked list.
 * @param *list Pointer to head node of linked list.
 * @returns Total count of nodes in list.
 */
int count(struct node *list)
{
    int nodes = 0;

    while (list != NULL) 
    {
        nodes++;
        list = list->next;
    }

    return nodes;
}


/**
 * Function to swap two nodes of a linked list

 * @param *list Pointer to head node of the list
 * @param pos1 Position of first node to swap
 * @param pos2 Position of second node to swap
 * @returns 1 on success, -1 on failure if swap 
 * positions are invalid.
 */
int swap(struct node *list, int pos1, int pos2)
{
    struct node *node1, *node2, *prev1, *prev2, *temp;
    int i;

    // Get the far position among both
    const int maxPos = (pos1 > pos2) ? pos1 : pos2;

    // Get total nodes in the list
    const int totalNodes = count(list);

    // Validate swap positions
    if ((pos1 <= 0 || pos1 > totalNodes) || (pos2 <= 0 || pos2 > totalNodes))
    {
        return -1;
    }
    
    // If both positions are same then no swapping required
    if (pos1 == pos2)
    {
        return 1;
    }

    // Identify both nodes to swap
    i = 1;
    temp  = list;
    prev1 = NULL;
    prev2 = NULL;

    // Find nodes to swap
    while (temp != NULL && (i <= maxPos))
    {
        if (i == pos1 - 1)
            prev1 = temp;
        if (i == pos1)
            node1 = temp;

        if (i == pos2 - 1)
            prev2 = temp;
        if (i == pos2)
            node2 = temp;

        temp = temp->next;
        i++;
    }

    // If both nodes to swap are found.
    if (node1 != NULL && node2 != NULL)
    {
        // Link previous of node1 with node2
        if (prev1 != NULL)
            prev1->next = node2;

        // Link previous of node2 with node1
        if (prev2 != NULL)
            prev2->next = node1;

        // Swap node1 and node2 by swapping their 
        // next node links
        temp        = node1->next;
        node1->next = node2->next;
        node2->next = temp;

        // Make sure to swap head node when swapping
        // first element.
        if (prev1 == NULL)
            head = node2;
        else if (prev2 == NULL)
            head = node1;
    }

    return 1;
}