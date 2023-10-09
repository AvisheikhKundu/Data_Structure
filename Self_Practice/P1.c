//Question: Suppose, you are in a marriage ceremony to take food from the booth. Now, write a function in c using link list as a guest. Assume, you have a token where a serial number and name and groom side/bride side are given. Do it for 50 guests.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a guest
struct Guest {
    int serialNumber;
    char name[50];
    char side[10];
    struct Guest* next;
};

// Function to create a new guest node
struct Guest* createGuest(int serialNumber, char name[], char side[]) {
    struct Guest* newGuest = (struct Guest*)malloc(sizeof(struct Guest));
    newGuest->serialNumber = serialNumber;
    strcpy(newGuest->name, name);
    strcpy(newGuest->side, side);
    newGuest->next = NULL;
    return newGuest;
}

// Function to insert a guest into the linked list
void insertGuest(struct Guest** head, int serialNumber, char name[], char side[]) {
    struct Guest* newGuest = createGuest(serialNumber, name, side);
    newGuest->next = *head;
    *head = newGuest;
}

// Function to display the list of guests
void displayGuests(struct Guest* head) {
    printf("Guest List:\n");
    while (head != NULL) {
        printf("Serial Number: %d, Name: %s, Side: %s\n", head->serialNumber, head->name, head->side);
        head = head->next;
    }
}

int main() {
    struct Guest* guestList = NULL;
    int i;
    char side[10];
    // Assume guests are added to the list with serial numbers, names, and sides.
    for (i = 1; i <= 50; ++i) {
        if (i % 2 == 0) {
            strcpy(side, "Bride");
        } else {
            strcpy(side, "Groom");
        }
        // Guest names are assumed to be "Guest1", "Guest2", ..., "Guest50"
        char guestName[50];
        sprintf(guestName, "Guest%d", i);
        insertGuest(&guestList, i, guestName, side);
    }

    // Display the list of guests
    displayGuests(guestList);

    // Free allocated memory
    struct Guest* temp;
    while (guestList != NULL) {
        temp = guestList;
        guestList = guestList->next;
        free(temp);
    }

    return 0;
}
