#include "../Headers/Press_Key_Back.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

void ClearScreen() {
#ifdef _WIN32
    system("cls");   // Windows command
#else
    system("clear"); // Mac/Linux command
#endif

}

void Press_Key_Back() {
    printf(MAGENTA "\n========================================\n" RESET);
    printf(YELLOW "Enter 0 to go back..." RESET);

    // Wait until the user types '0'
    while (getchar() != '0');

     while (getchar() != '\n');
    // Clear the console screen
    ClearScreen();
}

