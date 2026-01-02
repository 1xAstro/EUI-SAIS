#include <stdio.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// --- USER & DATA STRUCTURE HEADERS ---
#include "Functions_Files/User_Functions/LinkedLists.h" // Contains Node struct & Tree Loader
#include "Functions_Files/User_Functions/Admin_Functions/Headers/Admin.h"
#include "Functions_Files/User_Functions/Student_Functions/Headers/Student.h"
#include "Functions_Files/User_Functions/Student_Functions/Headers/Student_Courses.h" // Contains Student_Request_Session
#include "Functions_Files/User_Functions/Student_Functions/Headers/view_passed_courses.h"
#include "Functions_Files/User_Functions/Student_Functions/Headers/view_registered_courses.h"
#include "Functions_Files/User_Functions/Admin_Functions/Headers/Admin_Courses.h"

// --- NAVIGATION & DASHBOARD HEADERS ---
#include "Functions_Files/Navigation_Functions/Headers/Login_Screen.h"
#include "Functions_Files/Navigation_Functions/Headers/Admin_Dashboard.h"
#include "Functions_Files/Navigation_Functions/Headers/Student_Dashboard.h"
#include "Functions_Files/Navigation_Functions/Headers/Press_Key_Back.h"

// Defining color codes for terminal output
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define CYAN    "\033[0;36m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET   "\033[0m"

int main() {
    // --- CONSOLE SETUP (For Colors) ---
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // --- INITIALIZE DATA STRUCTURE ---
    Node *course_head = NULL;

    // This ensures Student_Request_Session receives the correct structure.
    Load_Courses_Tree(&course_head);

    int main_choice, sub_choice;
    char id[150] = {0};
    char password[50] = {0};
    char name[100] = {0};

    while (1) {
        // 1. MAIN MENU
        main_choice = Show_Login_Menu();
        if (main_choice == -1) continue;

        if (main_choice == 1) {
            // --- STUDENT FLOW ---
            if (Show_Student_Login(id, password)) {
                ClearScreen();
                if (perform_student_login(id, password, name)) {

                    // STUDENT SESSION LOOP
                    while(1) {
                        ClearScreen();
                        sub_choice = Show_Student_Dashboard(name);

                        if (sub_choice == 1) {
                            ClearScreen();
                            // Pass the Tree Root (course_head) to the request session
                            Student_Request_Session(id, course_head);
                            Press_Key_Back();
                        }
                        else if (sub_choice == 2) {
                            ClearScreen();
                            View_Registered_Courses(id);
                            Press_Key_Back();
                        }
                        else if (sub_choice == 3) {
                            ClearScreen();
                            View_Passed_Courses(id);
                            Press_Key_Back();
                        }
                        else if (sub_choice == 4) {
                            ClearScreen();
                            Perform_Logout(name);
                            Press_Key_Back();
                            break; // Break inner loop -> Back to Main Menu
                        }
                        else if (sub_choice != -1) {
                            printf(RED"Invalid option.\n"RESET);
                            Press_Key_Back();
                        }
                    }
                } else {
                    printf(RED"\n[Error]: Login failed.\n"RESET);
                    Press_Key_Back();
                }
            }
        }
        else if (main_choice == 2) {
            // --- ADMIN FLOW ---
            ClearScreen();
            if (Show_Admin_Login(id, password)) {
                ClearScreen();
                if (perform_admin_login(id, password, name)) {

                    // ADMIN SESSION LOOP
                    while(1) {
                        sub_choice = Show_Admin_Dashboard(name);

                        if (sub_choice == 1) {
                            ClearScreen();
                            Admin_Admit_Requests();
                            Press_Key_Back();
                        }
                        else if (sub_choice == 2) {
                            ClearScreen();
                            Admin_Add_Passed_Courses_Manual();
                            Press_Key_Back();
                        }
                        else if (sub_choice == 3) {
                            ClearScreen();
                            Add_New_Student();
                            Press_Key_Back();
                        }
                        else if (sub_choice == 4) {
                            ClearScreen();
                            Perform_Logout(name);
                            Press_Key_Back();
                            break; // Break inner loop -> Back to Main Menu
                        }
                        else if (sub_choice != -1) {
                            printf(RED"Invalid option.\n"RESET);
                            Press_Key_Back();
                        }
                    }
                } else {
                    printf(RED"\n[Error]: Login failed.\n"RESET);
                    Press_Key_Back();
                }
            }
        }
        else if (main_choice == 3) {
            printf(CYAN"Exiting... Goodbye!\n"RESET);
            break;
        }

        // Secure Cleanup of sensitive strings
        memset(password, 0, sizeof(password));
        memset(id, 0, sizeof(id));
        memset(name, 0, sizeof(name));
    }

    // CLEANUP: Free the Binary Tree memory
    freeTree(course_head);
    return 0;
}