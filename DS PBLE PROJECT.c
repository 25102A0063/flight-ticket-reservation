#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ---------------- USER ARRAY ----------------
typedef struct {
    char username[50];
    char password[50];
} User;

User users[100];
int userCount = 0;

// ---------------- FLIGHT ARRAY ----------------
typedef struct {
    int flightID;
    char source[50];
    char destination[50];
    int totalSeats;
} Flight;

Flight flights[50] = {
    {1, "Mumbai", "Delhi", 5},
    {2, "Mumbai", "Bangalore", 4},
    {3, "Mumbai", "Chennai", 1}
};

int flightCount = 3;

// ---------------- DOUBLY LINKED LIST ----------------
typedef struct Node {
    int ticketID;
    int flightID;
    char username[50];  
    char name[50];
    char source[50];
    char destination[50];
    char date[20];
    char status[20];     
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;
int ticketCounter = 1;
char currentUser[50];

// ---------------- GET SEATS PER FLIGHT ----------------
void toLowerCase(char str[]) {
    int i;
    for (i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

int getTotalSeats(char source[], char destination[]) {
	int i;
    for (i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].source, source) == 0 &&
            strcmp(flights[i].destination, destination) == 0)
            return flights[i].totalSeats;
    }
    return -1;
}

// ---------------- CREATE NODE ----------------
Node* createNode(char username[], char name[], char source[], char destination[], char date[], int flightID) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->ticketID = ticketCounter++;
    newNode->flightID = flightID;
    strcpy(newNode->username, username);
    strcpy(newNode->name, name);
    strcpy(newNode->source, source);
    strcpy(newNode->destination, destination);
    strcpy(newNode->date, date);

    int totalSeats = getTotalSeats(source, destination);
    int booked = 0;

    Node* temp = head;
    while (temp) {
        if (strcmp(temp->source, source) == 0 &&
            strcmp(temp->destination, destination) == 0 &&
            strcmp(temp->status, "BOOKED") == 0)
        {
            booked++;
        }
        temp = temp->next;
    }

    if (booked < totalSeats)
        strcpy(newNode->status, "BOOKED");
    else
        strcpy(newNode->status, "WAITING");

    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

// ---------------- INSERT NODE ----------------
void insertNode(Node* newNode) {
    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next) temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

// ---------------- VIEW FLIGHTS ----------------
void viewFlights() {
	int i;
    if (flightCount == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    printf("\n--- Available Flights ---\n");

    for (i = 0; i < flightCount; i++) {
        int booked = 0;

        // count booked seats for this flight
        Node* temp = head;
        while (temp) {
            if (temp->flightID == flights[i].flightID &&
                strcmp(temp->status, "BOOKED") == 0)
            {
                booked++;
            }
            temp = temp->next;
        }

        printf("Flight ID: %d | %s -> %s | Available Seats: %d/%d\n",
               flights[i].flightID,
               flights[i].source,
               flights[i].destination,
               flights[i].totalSeats - booked,
               flights[i].totalSeats);
    }
}

// ---------------- BOOK FIRST TICKET ----------------
void bookFirstTicket() {
    char name[50], source[50], destination[50], date[20];
    int fid, found = 0, i;

    printf("\nEnter Name: ");
    scanf("%s", name);

    // SHOW flights first
    viewFlights();

    printf("Select Flight ID from above: ");
    scanf("%d", &fid);

    // validate + fetch flight
    for (i = 0; i < flightCount; i++) {
        if (flights[i].flightID == fid) {
            strcpy(source, flights[i].source);
            strcpy(destination, flights[i].destination);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Invalid Flight ID!\n");
        return;
    }

    printf("Enter Date: ");
    scanf("%s", date);

    Node* newNode = createNode(currentUser, name, source, destination, date, fid);
    insertNode(newNode);

    printf("\nWelcome! Your first booking is successful!\n");
    printf("Your Ticket ID: %d\n", newNode->ticketID);
}

// ---------------- HELP MENU ----------------
void helpMenu() {
    printf("\n--- Help Section ---\n");
    printf("1. To book a ticket: Go to booking option\n");
    printf("2. To cancel: Use Ticket ID\n");
    printf("3. Ticket ID is important for tracking\n");
}

// ---------------- USER FUNCTIONS ----------------
int userExists(char username[]) {
    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0)
            return 1;
    }
    return 0;
}

int validateUser(char username[], char password[]) {
    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0)
            return 1;
    }
    return 0;
}

// ---------------- OLD CUSTOMER FEATURES ----------------
void bookTicket() {
    char name[50], source[50], destination[50], date[20];
    int fid, found = 0, i;

    printf("\nEnter Name: ");
    scanf("%s", name);

    // SHOW flights first
    viewFlights();

    printf("Select Flight ID from above: ");
    scanf("%d", &fid);

    // validate + fetch flight
    for (i = 0; i < flightCount; i++) {
        if (flights[i].flightID == fid) {
            strcpy(source, flights[i].source);
            strcpy(destination, flights[i].destination);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Invalid Flight ID!\n");
        return;
    }

    printf("Enter Date: ");
    scanf("%s", date);

    Node* newNode = createNode(currentUser, name, source, destination, date, fid);
    insertNode(newNode);

    printf("\nTicket Booked Successfully!\n");
    printf("Ticket ID: %d | Status: %s\n", newNode->ticketID, newNode->status);
}

void cancelTicket() {
    int id;
    printf("\nEnter Ticket ID to cancel: ");
    scanf("%d", &id);

    Node* temp = head;
    while (temp) {
        if (temp->ticketID == id && strcmp(temp->username, currentUser) == 0) {
            strcpy(temp->status, "CANCELLED");
            printf("Ticket cancelled successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Ticket not found!\n");
}

void viewMyBookings() {
    Node* temp = head;

    printf("\n--- My Bookings ---\n");
    while (temp) {
        if (strcmp(temp->username, currentUser) == 0) {
            printf("ID: %d | %s -> %s | Date: %s | Status: %s\n",
                   temp->ticketID,
                   temp->source,
                   temp->destination,
                   temp->date,
                   temp->status);
        }
        temp = temp->next;
    }
}

void searchTicket() {
    int id;
    printf("\nEnter Ticket ID: ");
    scanf("%d", &id);

    Node* temp = head;
    while (temp) {
        if (temp->ticketID == id) {
            printf("Found: %s -> %s | Date: %s | Status: %s\n",
                   temp->source, temp->destination,
                   temp->date, temp->status);
            return;
        }
        temp = temp->next;
    }
    printf("Not found!\n");
}

void checkSeatAvailability() {
    char source[50], destination[50];

    viewFlights();

    printf("\nEnter Source: ");
    scanf("%s", source);
    printf("Enter Destination: ");
    scanf("%s", destination);

    int totalSeats = getTotalSeats(source, destination);
    int booked = 0, waiting = 0;

    Node* temp = head;

    while (temp) {
        if (strcmp(temp->source, source) == 0 &&
            strcmp(temp->destination, destination) == 0)
        {
            if (strcmp(temp->status, "BOOKED") == 0) booked++;
            if (strcmp(temp->status, "WAITING") == 0) waiting++;
        }
        temp = temp->next;
    }

    printf("\n--- Seat Status (%s -> %s) ---\n", source, destination);
    printf("Total Seats: %d\n", totalSeats);
    printf("Available Seats: %d\n", totalSeats - booked);
    printf("Waiting List: %d\n", waiting);
}

void viewWaitingList() {
    char source[50], destination[50];

    viewFlights();

    printf("\nEnter Source: ");
    scanf("%s", source);
    printf("Enter Destination: ");
    scanf("%s", destination);

    Node* temp = head;
    int found = 0;

    printf("\n--- Waiting List (%s -> %s) ---\n", source, destination);

    while (temp) {
        if (strcmp(temp->source, source) == 0 &&
            strcmp(temp->destination, destination) == 0 &&
            strcmp(temp->status, "WAITING") == 0)
        {
            printf("ID:%d | %s\n", temp->ticketID, temp->name);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf("No waiting passengers.\n");
}

void updateBooking() {
    int id;
    printf("\nEnter Ticket ID to update: ");
    scanf("%d", &id);

    Node* temp = head;

    while (temp) {
        if (temp->ticketID == id && strcmp(temp->username, currentUser) == 0) {
            printf("Enter new destination: ");
            scanf("%s", temp->destination);
            printf("Enter new date: ");
            scanf("%s", temp->date);
            printf("Booking updated!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Ticket not found!\n");
}

void viewBookingHistory() {
    Node* temp = head;

    printf("\n--- Booking History ---\n");

    while (temp) {
        if (strcmp(temp->username, currentUser) == 0) {
            printf("ID:%d | %s->%s | %s | %s\n",
                   temp->ticketID,
                   temp->source,
                   temp->destination,
                   temp->date,
                   temp->status);
        }
        temp = temp->next;
    }
}

// ---------------- OLD CUSTOMER MENU ----------------
void oldCustomerMenu() {
    int choice;
    do {
        printf("\n--- Old Customer Menu ---\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. View My Bookings\n");
        printf("4. Search Ticket\n");
        printf("5. Help\n");
        printf("6. Check Seat Availability\n");
        printf("7. Update Booking\n");
        printf("8. View Booking History\n");
        printf("9. Waiting List\n");
        printf("10. Logout\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: cancelTicket(); break;
            case 3: viewMyBookings(); break;
            case 4: searchTicket(); break;
            case 5: helpMenu(); break;
            case 6: checkSeatAvailability(); break;
            case 7: updateBooking(); break;
            case 8: viewBookingHistory(); break;
            case 9: viewWaitingList(); break;
        }

    } while (choice != 10);
}

// ---------------- NEW CUSTOMER MENU ----------------
void newCustomerMenu() {
    int choice;

    do {
        printf("\n--- New Customer Menu ---\n");
        printf("1. Book Your First Ticket\n");
        printf("2. View Available Flights\n");
        printf("3. Help\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookFirstTicket(); break;
            case 2: viewFlights(); break;
            case 3: helpMenu(); break;
            case 4: printf("Returning...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 4);
}

// ---------------- SIGNUP ----------------
void signup() {
    char username[50], password[50], confirm[50];

    printf("\nCreate Username: ");
    scanf("%s", username);

    if (userExists(username)) {
        printf("Username already exists!\n");
        return;
    }

    printf("Create Password: ");
    scanf("%s", password);
    printf("Confirm Password: ");
    scanf("%s", confirm);

    if (strcmp(password, confirm) == 0) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].password, password);
        userCount++;

        strcpy(currentUser, username);

        printf("\nAccount Created Successfully!\n");
        newCustomerMenu();
    } else {
        printf("\nPasswords do not match!\n");
    }
}

// ---------------- LOGIN ----------------
void login() {
    char username[50], password[50];

    printf("\nEnter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    if (validateUser(username, password)) {
        strcpy(currentUser, username);
        printf("\nLogin Successful!\n");
        oldCustomerMenu();
    } else {
        printf("\nWrong credentials!\n");
    }
}

// ---------------- CUSTOMER MENU ----------------
void customerMenu() {
    int choice;

    do {
        printf("\n--- Customer Menu ---\n");
        printf("1. Sign Up\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1: signup(); break;
            case 2: login(); break;
            case 3: printf("Returning...\n"); break;
        }

    } while (choice != 3);
}

// ---------------- ADMIN FUNCTIONS ----------------

void viewAllBookings() {
    Node* temp = head;

    printf("\n--- All Bookings (Forward) ---\n");
    while (temp) {
        printf("ID:%d | %s | %s->%s | %s | %s\n",
               temp->ticketID,
               temp->name,
               temp->source,
               temp->destination,
               temp->date,
               temp->status);
        if (temp->next == NULL) break;
        temp = temp->next;
    }

    printf("\n--- Reverse Order ---\n");
    while (temp) {
        printf("ID:%d | %s | %s->%s | %s | %s\n",
               temp->ticketID,
               temp->name,
               temp->source,
               temp->destination,
               temp->date,
               temp->status);
        temp = temp->prev;
    }
}

// ---------------- SEARCH BOOKING  ----------------
void searchAnyBooking() {
    int choice;
    Node* temp = head;
    int found = 0;

    printf("\n1. By Ticket ID\n2. By Name\n3. By Destination\n");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("Enter Ticket ID: ");
        scanf("%d", &id);

        while (temp) {
            if (temp->ticketID == id) {
                printf("Found: %s -> %s | %s | %s\n",
                       temp->source, temp->destination,
                       temp->date, temp->status);
                found = 1;
            }
            temp = temp->next;
        }
    }

    else if (choice == 2) {
        char name[50];
        printf("Enter Name: ");
        scanf("%s", name);

        while (temp) {
            if (strcmp(temp->name, name) == 0) {
                printf("ID:%d | %s -> %s\n",
                       temp->ticketID,
                       temp->source,
                       temp->destination);
                found = 1;
            }
            temp = temp->next;
        }
    }

    else if (choice == 3) {
        char dest[50];
        printf("Enter Destination: ");
        scanf("%s", dest);

        while (temp) {
            if (strcmp(temp->destination, dest) == 0) {
                printf("ID:%d | %s\n",
                       temp->ticketID,
                       temp->name);
                found = 1;
            }
            temp = temp->next;
        }
    }

    if (!found)
        printf("No matching records found.\n");
}

// ---------------- ADD FLIGHT  ----------------
void addFlightAdmin() {
    printf("Enter Flight ID: ");
    scanf("%d", &flights[flightCount].flightID);

    printf("Enter Source: ");
    scanf("%s", flights[flightCount].source);

    printf("Enter Destination: ");
    scanf("%s", flights[flightCount].destination);

    printf("Enter Seats: ");
    scanf("%d", &flights[flightCount].totalSeats);

    flightCount++;

    printf("Flight added successfully!\n");
}

// ---------------- REMOVE FLIGHT  ----------------
void removeFlight() {
    int id, i, j;
    printf("Enter Flight ID: ");
    scanf("%d", &id);

    // remove flight
    for (i = 0; i < flightCount; i++) {
        if (flights[i].flightID == id) {
            for (j = i; j < flightCount - 1; j++)
                flights[j] = flights[j + 1];
            flightCount--;
            break;
        }
    }

    // cancel related tickets
    Node* temp = head;
    while (temp) {
        if (temp->flightID == id)
            strcpy(temp->status, "CANCELLED");
        temp = temp->next;
    }

    printf("Flight removed and bookings cancelled.\n");
}
 
// ---------------- Update Booking (Admin override)  ----------------
void adminUpdateBooking() {
    int id;
    printf("Enter Ticket ID: ");
    scanf("%d", &id);

    Node* temp = head;

    while (temp) {
        if (temp->ticketID == id) {

            if (strcmp(temp->status, "CANCELLED") == 0) {
                printf("Cannot update cancelled ticket.\n");
                return;
            }

            printf("Enter new destination: ");
            scanf("%s", temp->destination);

            printf("Enter new date: ");
            scanf("%s", temp->date);

            printf("Updated successfully.\n");
            return;
        }
        temp = temp->next;
    }

    printf("Ticket not found.\n");
}

// ---------------- MANAGE SEATS  ----------------
void manageSeats() {
    int id, seats, i;

    printf("Enter Flight ID: ");
    scanf("%d", &id);

    for (i = 0; i < flightCount; i++) {
        if (flights[i].flightID == id) {

            printf("Current Seats: %d\n", flights[i].totalSeats);

            printf("Enter new seat capacity: ");
            scanf("%d", &seats);

            flights[i].totalSeats = seats;

            printf("Seats updated successfully!\n");
            return;
        }
    }

    printf("Flight not found!\n");
}
// ---------------- View Waiting List  ----------------
void adminWaitingList() {
    Node* temp = head;

    printf("\n--- WAITING LIST ---\n");

    while (temp) {
        if (strcmp(temp->status, "WAITING") == 0) {
            printf("ID:%d | %s | %s->%s\n",
                   temp->ticketID,
                   temp->name,
                   temp->source,
                   temp->destination);
        }
        temp = temp->next;
    }
}

// ---------------- REPORTS ----------------
void generateReports() {
    Node* temp = head;

    int total = 0, cancelled = 0, booked = 0;

    while (temp) {
        total++;

        if (strcmp(temp->status, "CANCELLED") == 0)
            cancelled++;

        if (strcmp(temp->status, "BOOKED") == 0)
            booked++;

        temp = temp->next;
    }

    printf("\nTotal Bookings: %d\n", total);
    printf("Cancelled Tickets: %d\n", cancelled);

    if (total > 0)
        printf("Occupancy Rate: %.2f%%\n", (booked * 100.0) / total);
}

// ---------------- ADMIN MENU ----------------
void adminMenu() {
    int choice;

    do {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. View All Bookings\n");
        printf("2. Search Booking\n");
        printf("3. Add Flight\n");
        printf("4. Remove Flight\n");
        printf("5. Update Booking\n");
        printf("6. Manage Seats\n");
        printf("7. View Waiting List\n");
        printf("8. Reports\n");
        printf("9. Logout\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1: viewAllBookings(); break;
            case 2: searchAnyBooking(); break;
            case 3: addFlightAdmin(); break;
            case 4: removeFlight(); break;
            case 5: adminUpdateBooking(); break;
            case 6: manageSeats(); break;
            case 7: adminWaitingList(); break;
            case 8: generateReports(); break;
        }

    } while (choice != 9);
}

// ---------------- MAIN ----------------
int main() {
    int choice;

    do {
        printf("\n===== FLIGHT RESERVATION SYSTEM =====\n");
        printf("1. Admin\n2. Customer\n3. Exit\n");

        scanf("%d", &choice);

        if (choice == 1) {
		    char pass[20];
		    printf("Enter Admin Password: ");
		    scanf("%s", pass);
		
		    if (strcmp(pass, "admin123") == 0)
		        adminMenu();
		    else
		        printf("Wrong password!\n");
			}
        else if (choice == 2) {
            customerMenu();
        }

    } while (choice != 3);

    return 0;
}
