#include <stdio.h>
#include "../Navigation_Functions/Headers/Admin_Dashboard.h"

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

static void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int Show_Admin_Dashboard(char *admin_name) {
    int choice;
    printf(MAGENTA"\n========================================\n"RESET);
    printf(CYAN"   ADMIN DASHBOARD: %s\n"RESET, admin_name);
    printf(MAGENTA"========================================\n"RESET);
    printf("1. Process Pending Requests\n");
    printf("2. Manually Add Passed Course\n");
    printf("3. Adding new students\n");
    printf("4. Logout\n");
    printf(MAGENTA"----------------------------------------\n"RESET);
    printf(BLUE"Select an option: "RESET);

    if (scanf("%d", &choice) != 1) {
        printf(RED"Invalid input. Please enter a number.\n"RESET);
        clear_buffer();
        return -1;
    }
    return choice;
}