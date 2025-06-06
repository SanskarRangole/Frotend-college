#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for Date, Guest, Room, and Stack

struct Date {
    int day;
    int month;
    int year;
};

struct Guest {
    int roomNumber;
    char name[50];
    struct Date checkInDate;
    struct Date checkOutDate;
    struct Guest* next;
};

struct Room {
    int roomNumber;
    char type[20];
    float price;
    int isOccupied;
};

struct Stack {
    struct Guest* top;
};

// Function to push a guest onto the stack
void push(struct Stack* stack, struct Guest* guest) {
    guest->next = stack->top;
    stack->top = guest;
}

// Function to pop a guest from the stack
struct Guest* pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty. No reservation to remove.\n");
        return NULL;
    }
    struct Guest* guest = stack->top;
    stack->top = stack->top->next;
    return guest;
}

// Function to insert a guest into the linked list in a sorted manner
void insertSorted(struct Guest** head, struct Guest* newGuest) {
    struct Guest* current;
    if (*head == NULL || (*head)->roomNumber >= newGuest->roomNumber) {
        newGuest->next = *head;
        *head = newGuest;
    } else {
        current = *head;
        while (current->next != NULL && current->next->roomNumber < newGuest->roomNumber) {
            current = current->next;
        }
        newGuest->next = current->next;
        current->next = newGuest;
    }
}

// Function to display all guests in the linked list

void displayGuests(struct Guest* head) {
    printf("Guests:\n");
    struct Guest* current = head;
    
    if (current == NULL) {
        printf("No guests.\n");
    } else {
        while (current != NULL) {
            printf("Name: %s\n", current->name);
            printf("Room Number: %d\n", current->roomNumber);
            printf("Check-in Date: %02d/%02d/%04d\n", current->checkInDate.day, current->checkInDate.month, current->checkInDate.year);
            printf("Check-out Date: %02d/%02d/%04d\n", current->checkOutDate.day, current->checkOutDate.month, current->checkOutDate.year);
            printf("\n");
            current = current->next;
        }
    }
}







// Function to check if a room is available
int isRoomAvailable(struct Room rooms[], int roomNumber, int totalRooms) {
    for (int i = 0; i < totalRooms; i++) {
        if (rooms[i].roomNumber == roomNumber && rooms[i].isOccupied == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to reserve a room
void reserveRoom(struct Room rooms[], int roomNumber, int totalRooms, struct Guest** head, struct Stack* reservationStack) {
    for (int i = 0; i < totalRooms; i++) {
        if (rooms[i].roomNumber == roomNumber && rooms[i].isOccupied == 0) {
            rooms[i].isOccupied = 1;

            struct Guest* newGuest = (struct Guest*)malloc(sizeof(struct Guest));
            newGuest->roomNumber = roomNumber;
            printf("Enter guest name: ");
            scanf("%s", newGuest->name);

            printf("Enter check-in date (day month year): ");
            scanf("%d %d %d", &newGuest->checkInDate.day, &newGuest->checkInDate.month, &newGuest->checkInDate.year);

            printf("Enter check-out date (day month year): ");
            scanf("%d %d %d", &newGuest->checkOutDate.day, &newGuest->checkOutDate.month, &newGuest->checkOutDate.year);

            newGuest->next = NULL;

            insertSorted(head, newGuest);
            push(reservationStack, newGuest);

            printf("Room reserved successfully!\n");
            return;
        }
    }
    printf("Room not available for reservation.\n");
}

// Function to search for a guest by room number
void searchGuest(struct Guest* head, int roomNumber) {
    struct Guest* current = head;
    int guestFound = 0;
    while (current != NULL) {
        if (current->roomNumber == roomNumber) {
            printf("Name: %s\n", current->name);
            printf("Room Number: %d\n", current->roomNumber);
            printf("Check-in Date: %02d/%02d/%04d\n", current->checkInDate.day, current->checkInDate.month, current->checkInDate.year);
            printf("Check-out Date: %02d/%02d/%04d\n", current->checkOutDate.day, current->checkOutDate.month, current->checkOutDate.year);
            guestFound = 1;
        }
        current = current->next;
    }
    if (!guestFound) {
        printf("No guest found in room %d.\n", roomNumber);
    }
}

// Function to check-out a guest
void checkOutGuest(struct Room rooms[], int roomNumber, int totalRooms, struct Guest** head) {
    struct Guest* current = *head;
    struct Guest* prev = NULL;
    while (current != NULL) {
        if (current->roomNumber == roomNumber) {
            for (int i = 0; i < totalRooms; i++) {
                if (rooms[i].roomNumber == roomNumber) {
                    rooms[i].isOccupied = 0;
                    break;
                }
            }
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Guest checked out successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("No guest found in room %d.\n", roomNumber);
}

int main() {
    struct Room rooms[5];
    struct Guest* guestList = NULL;
    struct Stack reservationStack;
    reservationStack.top = NULL;
    int totalRooms = 5;
    int guestsDisplayed = 0; // Flag to track whether guests have been displayed

    // Initialize rooms
    for (int i = 0; i < totalRooms; i++) {
        rooms[i].roomNumber = i + 1;
        strcpy(rooms[i].type, "Standard");
        rooms[i].price = 100.0;
        rooms[i].isOccupied = 0;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Reserve a room\n");
        printf("2. Display guest details (sorted by room number)\n");
        printf("3. Search for a guest\n");
        printf("4. Check-out a guest\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int roomNumber;
                printf("Enter room number for reservation: ");
                scanf("%d", &roomNumber);

                if (roomNumber < 1 || roomNumber > totalRooms) {
                    printf("Invalid room number.\n");
                } else {
                    reserveRoom(rooms, roomNumber, totalRooms, &guestList, &reservationStack);
                }
                break;
            }
       case 2: {
                // Display guests when option 2 is selected
                displayGuests(guestList);
                break;
       }
            case 3: {
                int roomNumber;
                printf("Enter room number to search for a guest: ");
                scanf("%d", &roomNumber);
                searchGuest(guestList, roomNumber);
                break;
            }
            case 4: {
                int roomNumber;
                printf("Enter room number to check out a guest: ");
                scanf("%d", &roomNumber);
                checkOutGuest(rooms, roomNumber, totalRooms, &guestList);
                break;
            }
            case 5:
                printf("Exiting the system.\n");
                exit(0);
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
            guestsDisplayed = 0;
    }

    return 0;
}
