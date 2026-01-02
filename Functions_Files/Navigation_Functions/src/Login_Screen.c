// File: Navigation_Functions/src/Login_Screen.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/Login_Screen.h" // Go up from src, then into Headers

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

void clear_input_buffer_nav() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int Show_Login_Menu() {
    int choice;
    printf(MAGENTA"========================================\n"RESET);
    printf(CYAN "      University Registration System      \n"RESET);
    printf(MAGENTA"========================================\n"RESET);
    printf("1. Login as Student\n");
    printf("2. Login as Admin\n");
    printf("3. Quit Program\n");
    printf(MAGENTA"----------------------------------------\n"RESET);
    printf(BLUE"Select an option: "RESET);

    if (scanf("%d", &choice) != 1) {
        printf(RED"Invalid input. Please enter a number.\n"RESET);
        clear_input_buffer_nav();
        return -1; // Return error code
    }
    return choice;
}

int Show_Student_Login(char *id_buffer, char *pass_buffer) {
    printf(MAGENTA"\n========================================\n"RESET);
    printf(CYAN"           STUDENT LOGIN               \n"RESET);
    printf(MAGENTA"========================================\n"RESET);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf(BLUE"Enter Student ID: "RESET);
    if (fgets(id_buffer, 50, stdin) == NULL) return 0;
    id_buffer[strcspn(id_buffer, "\n")] = 0; // Remove Enter key

    printf(BLUE"Enter Password:   "RESET);
    if (fgets(pass_buffer, 300, stdin) == NULL) return 0;
    pass_buffer[strcspn(pass_buffer, "\n")] = 0; // Remove Enter key

    printf(MAGENTA"----------------------------------------\n"RESET);
    return 1; // Success
}

int Show_Admin_Login(char *email_buffer, char *pass_buffer) {
    printf(MAGENTA"\n========================================\n"RESET);
    printf(CYAN"            ADMIN LOGIN                \n"RESET);
    printf(MAGENTA"========================================\n"RESET);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf(BLUE"Enter Email:      "RESET);
    if (fgets(email_buffer, 300, stdin) == NULL) return 0;
    email_buffer[strcspn(email_buffer, "\n")] = 0; // Remove Enter key
    printf(BLUE"Enter Password:   "RESET);
    if (fgets(pass_buffer, 50, stdin) == NULL) return 0;
    pass_buffer[strcspn(pass_buffer, "\n")] = 0; // Remove Enter key

    printf(MAGENTA"----------------------------------------\n"RESET);
    return 1; // Success
    }
    void Perform_Logout(char *user_name) {
        printf(RED"\n[System]: User '%s' logged out.\n" RESET, user_name);
}