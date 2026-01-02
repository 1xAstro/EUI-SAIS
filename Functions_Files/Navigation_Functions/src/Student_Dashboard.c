#include <stdio.h>
#include "../Navigation_Functions/Headers/Student_Dashboard.h"

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

// Helper to clear buffer (duplicate this or include a common utility header)
static void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int Show_Student_Dashboard(char *student_name) {
    int choice;
    printf(MAGENTA"\n========================================\n"RESET);
    printf(CYAN "   STUDENT DASHBOARD: %s\n"RESET, student_name );
    printf(MAGENTA"========================================\n"RESET);
    printf("1. Register for New Courses\n");
    printf("2. View Registered Courses\n");
    printf("3. View Passed Courses\n");
    printf("4. Logout\n");
    printf(MAGENTA"----------------------------------------\n"RESET);
    printf(BLUE "Select an option: " RESET);

    if (scanf("%d", &choice) != 1) {
        printf(RED "Invalid input. Please enter a number.\n" RESET);
        clear_buffer();
        return -1;
    }
    return choice;
}