#include <stdio.h>
#include "../Headers/Admin.h"

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

void view_admin_dashboard(char *username) {
    printf(CYAN"Welcome to the dashboard, %s!\n"RESET, username);
}

