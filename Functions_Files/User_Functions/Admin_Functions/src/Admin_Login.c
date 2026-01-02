#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/Admin.h"

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

#define MAX_LINE_LENGTH 1024
#define CSV_ADMIN "./DataBases/Admin_DataBase.csv"

// --- Helper Function: Add Node to List ---
void add_admin_node(User **head, char *Email, char *Password , char *Name) {
    User *newUser = (User*)malloc(sizeof(User));
    if (!newUser) {
        printf(RED"Memory allocation failed.\n"RESET);
        return;
    }
    strcpy(newUser->ID, Email);
    strcpy(newUser->Password, Password);
    strcpy(newUser->Name, Name);
    newUser->next = *head;
    *head = newUser;
}

// --- Function 1: Load Data (Hidden logic) ---
User* load_admin_from_csv() {
    User *head = NULL;
    char line[MAX_LINE_LENGTH];

    FILE *file = fopen(CSV_ADMIN, "r");
    if (file == NULL) {
        printf(RED"Error: Could not open %s\n"RESET, CSV_ADMIN);
        return NULL;
    }

    // Skip Header
    fgets(line, sizeof(line), file);

    // Read File
    while (fgets(line, sizeof(line), file)) {
        char *Email = strtok(line, ",");
        char *Password = strtok(NULL, ",");
        char *Name = strtok(NULL, ",");
        if (Email != NULL && Password != NULL && Name != NULL) {
            // Clean newline characters from password
            Password[strcspn(Password, "\r\n")] = 0;
            add_admin_node(&head, Email, Password,Name);
        }
    }

    fclose(file);
    return head;
}

// --- Function 2: The Main Login Check ---
// Returns 1 if successful, 0 if failed
int perform_admin_login(char *Email, char *Password, char *Name) {
    // 1. Load the database just for this check
    // (In a larger app, you might load this once in main, but this is safe for now)
    User *head = load_admin_from_csv();
    User *current = head;
    int success = 0;

    // 2. Traverse the list
    while (current != NULL) {
        if (strcmp(Email, current->ID) == 0 &&
            strcmp(Password, current->Password) == 0) {
            success = 1;
            strcpy(Name, current->Name); // Return the Name on successful login
            break;
        }
        current = current->next;
    }

    // 3. Clean up memory immediately after check
    free_admin_list(head);

    return success;
}

// --- Function 3: Cleanup ---
void free_admin_list(User *head) {
    User *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}