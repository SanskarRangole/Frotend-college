#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Guest {
    int roomNumber;
    char name[50];
};

struct Stack {
    struct Guest data[100];
    int top;
};

void push(struct Stack* stack, struct Guest guest) {
    if (stack->top < 100) {
        stack->data[stack->top] = guest;
        stack->top++;
    } else {
        printf("Stack is full. Cannot push more guests.\n");
    }
}

struct Guest pop(struct Stack* stack) {
    struct Guest emptyGuest;
    if (stack->top > 0) {
        stack->top--;
        return stack->data[stack->top];
    } else {
        printf("Stack is empty. No more guests to pop.\n");
        return emptyGuest;
    }
}

void bubbleSort(struct Guest guests[], int numGuests) {
    int swapped;
    struct Guest temp;
    do {
        swapped = 0;
        for (int i = 0; i < numGuests - 1; i++) {
            if (guests[i].roomNumber > guests[i + 1].roomNumber) {
                temp = guests[i];
                guests[i] = guests[i + 1];
                guests[i + 1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

int searchGuest(struct Guest guests[], int numGuests, int roomNumber) {
    for (int i = 0; i < numGuests; i++) {
        if (guests[i].roomNumber == roomNumber) {
            return i; // Guest found at index i.
        }
    }
    return -1; // Guest not found.
}

void displayGuests(struct Guest guests[], int numGuests) {
    printf("Guest List:\n");
    for (int i = 0; i < numGuests; i++) {
        printf("Room Number: %d, Name: %s\n", guests[i].roomNumber, guests[i].name);
    }
}

int main() {
    struct Guest guests[100];
    int numGuests = 0;
    struct Stack guestStack;
    guestStack.top = 0;

    while (1) {
        int choice;
        printf("1. Add Guest\n2. Remove Guest\n3. Search Guest\n4. Sort Guests\n5. Display Guests\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add a guest to the guests array.
                struct Guest newGuest;
                printf("Enter room number: ");
                scanf("%d", &newGuest.roomNumber);
                printf("Enter guest name: ");
                scanf("%s", newGuest.name);
                guests[numGuests] = newGuest;
                numGuests++;
                break;

            case 2:
                // Remove a guest from the stack and update the guests array.
                if (guestStack.top > 0) {
                    struct Guest removedGuest = pop(&guestStack);
                    int index = searchGuest(guests, numGuests, removedGuest.roomNumber);
                    if (index != -1) {
                        for (int i = index; i < numGuests - 1; i++) {
                            guests[i] = guests[i + 1];
                        }
                        numGuests--;
                    }
                }
                break;

            case 3:
                // Search for a guest by room number and display their information.
                int roomNumber;
                printf("Enter room number to search: ");
                scanf("%d", &roomNumber);
                int guestIndex = searchGuest(guests, numGuests, roomNumber);
                if (guestIndex != -1) {
                    printf("Guest found - Room Number: %d, Name: %s\n", guests[guestIndex].roomNumber, guests[guestIndex].name);
                } else {
                    printf("Guest not found.\n");
                }
                break;

            case 4:
                // Sort the guests array.
                bubbleSort(guests, numGuests);
                printf("Guests sorted.\n");
                break;

            case 5:
                // Display all guests.
                displayGuests(guests, numGuests);
                break;

            case 6:
                exit(0); // Exit the program.
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}