#include "Student_Courses.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- COLOR DEFINITIONS ---
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define CYAN    "\033[0;36m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"

#define MAX_LINE 2048

// --- DATABASE PATHS ---
// NOTE: These paths are relative to where your .exe is RUNNING.
#define DB_PATH "../Project/DataBases/Student_DataBase.csv"
#define TEMP_PATH "../Project/DataBases/temp_db.csv"
#define BACKUP_PATH "../Project/DataBases/Student_DataBase_Old.csv"

// --- HELPER: SAFE CSV PARSER ---
// Extracts a specific column from a CSV line
void get_csv_field(char *line, int index, char *output_buffer) {
    int col = 0;
    char *start = line;
    char *end = line;

    strcpy(output_buffer, "");

    while (*start != '\0') {
        end = strpbrk(start, ",\n");

        if (col == index) {
            if (end == NULL) {
                strcpy(output_buffer, start);
            } else {
                int len = end - start;
                strncpy(output_buffer, start, len);
                output_buffer[len] = '\0';
            }
            // Clean up newlines/returns
            char *newline = strchr(output_buffer, '\n');
            if (newline) *newline = '\0';
            char *cr = strchr(output_buffer, '\r');
            if (cr) *cr = '\0';
            return;
        }

        if (end == NULL) break;
        start = end + 1;
        col++;
    }
    strcpy(output_buffer, "None");
}

// --- HELPER: GET PASSED COURSES ---
// Reads the database to find what the student has already finished
void Helper_Get_Passed(char *student_id, char *buffer) {
    FILE *file = fopen(DB_PATH, "r");

    if (!file) {
        printf(RED"ERROR: Could not open Student DataBase at: %s\n"RESET, DB_PATH);
        strcpy(buffer, "NOT_FOUND");
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file)) {
        char current_id[150];
        get_csv_field(line, 0, current_id); // Column 0 is ID

        if (strcmp(current_id, student_id) == 0) {
            get_csv_field(line, 3, buffer); // Column 3 is Passed Courses
            if (strlen(buffer) == 0) strcpy(buffer, "None");
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf(RED"Error: Student ID not found in database.\n"RESET);
    strcpy(buffer, "NOT_FOUND");
}

// --- REQUIRED: TRAVERSE TREE TO SHOW ELIGIBILITY ---
// Recursively visits nodes (Left -> Root -> Right) to print available courses
void Display_Eligible_Courses(Node *root, char *passed_courses) {
    if (root == NULL) return;

    // 1. Traverse Left Subtree
    Display_Eligible_Courses(root->left, passed_courses);

    // 2. Check Logic for Current Node
    int eligible = 1;

    // Check Prereq 1 (Skip if "None" or "-1")
    if (strcmp(root->prereq1, "-1") != 0 && strcmp(root->prereq1, "None") != 0) {
        // If prereq is NOT in passed_courses, you are not eligible
        if (strstr(passed_courses, root->prereq1) == NULL) eligible = 0;
    }

    // Check Prereq 2
    if (strcmp(root->prereq2, "-1") != 0 && strcmp(root->prereq2, "None") != 0) {
        if (strstr(passed_courses, root->prereq2) == NULL) eligible = 0;
    }

    // Check if already passed (Don't show courses you already finished)
    if (strstr(passed_courses, root->code) != NULL) eligible = 0;

    if (eligible) {
        printf(GREEN"  [Available] %-10s (Prereqs: %s, %s)\n"RESET, root->code, root->prereq1, root->prereq2);
    }

    // 3. Traverse Right Subtree
    Display_Eligible_Courses(root->right, passed_courses);
}

// --- REQUIRED: RECURSIVE VALIDATOR ---
// Searches the tree for target_code. If found, validates prerequisites.
// Returns: 1 (Valid), 0 (Invalid), -1 (Code Not Found)
int Recursive_Prereq_Validator(Node *root, char *target_code, char *passed_courses) {
    // Base Case: End of branch
    if (root == NULL) return -1;

    // 1. Search Left
    int res = Recursive_Prereq_Validator(root->left, target_code, passed_courses);
    if (res != -1) return res; // Found in left branch

    // 2. Check Current Node (Root)
    if (strcmp(root->code, target_code) == 0) {

        // Validate Prereq 1
        if (strcmp(root->prereq1, "-1") != 0 && strcmp(root->prereq1, "None") != 0) {
            if (strstr(passed_courses, root->prereq1) == NULL) {
                printf(RED"  [Fail] %s: Missing Prerequisite %s\n"RESET, root->code, root->prereq1);
                return 0; // Invalid
            }
        }

        // Validate Prereq 2
        if (strcmp(root->prereq2, "-1") != 0 && strcmp(root->prereq2, "None") != 0) {
            if (strstr(passed_courses, root->prereq2) == NULL) {
                printf(RED"  [Fail] %s: Missing Prerequisite %s\n"RESET, root->code, root->prereq2);
                return 0; // Invalid
            }
        }

        return 1; // Valid and Safe
    }

    // 3. Search Right
    return Recursive_Prereq_Validator(root->right, target_code, passed_courses);
}

// --- FILE UPDATE LOGIC ---
void Internal_Save_Request(char *target_id, char *course_code, Node *course_head, char *passed_courses) {

    // 1. Validate using the Tree Validator
    int check_result = Recursive_Prereq_Validator(course_head, course_code, passed_courses);

    if (check_result == -1) {
        printf(RED"Error: Course %s does not exist in the curriculum.\n"RESET, course_code);
        return;
    }
    if (check_result == 0) {
        // Error message was already printed inside the validator
        return;
    }

    // 2. Open Files for Update
    FILE *file = fopen(DB_PATH, "r");
    FILE *temp = fopen(TEMP_PATH, "w");

    if (!file || !temp) {
        printf(RED"Error: Could not open database files for writing.\n"RESET);
        if (file) fclose(file);
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file)) {
        char original_line[MAX_LINE];
        strcpy(original_line, line);

        char id[150], pass[50], name[100], passed[512], reg[512], req[512];

        get_csv_field(line, 0, id);
        get_csv_field(line, 1, pass);
        get_csv_field(line, 2, name);
        get_csv_field(line, 3, passed);
        get_csv_field(line, 4, reg);
        get_csv_field(line, 5, req);

        // Normalize data
        if (strlen(passed) == 0) strcpy(passed, "None");
        if (strlen(reg) == 0) strcpy(reg, "None");
        if (strlen(req) == 0) strcpy(req, "None");

        if (strcmp(id, target_id) == 0) {
            // Check if already requested or registered
            if (strstr(req, course_code) != NULL || strstr(reg, course_code) != NULL) {
                printf(YELLOW"  [Info] %s already requested or registered.\n"RESET, course_code);
                fprintf(temp, "%s", original_line); // Write original line
            } else {
                // Append the new request
                if (strcmp(req, "None") == 0) {
                    fprintf(temp, "%s,%s,%s,%s,%s,%s\n", id, pass, name, passed, reg, course_code);
                } else {
                    fprintf(temp, "%s,%s,%s,%s,%s,%s-%s\n", id, pass, name, passed, reg, req, course_code);
                }
                printf(GREEN"  [Success] Request sent for %s.\n"RESET, course_code);
            }
        } else {
            fprintf(temp, "%s", original_line); // Write other students' lines unchanged
        }
    }
    fclose(file);
    fclose(temp);

    // Swap files
    remove(BACKUP_PATH);
    rename(DB_PATH, BACKUP_PATH);
    rename(TEMP_PATH, DB_PATH);
    remove(BACKUP_PATH);
}

// --- RECURSIVE INPUT LOOP ---
void Recursive_Register_Loop(int current, int total, char *student_id, Node *course_head, char *passed_courses) {
    if (current > total) return;

    char code[50];
    printf(BLUE"Enter Code for Course %d: "RESET, current);
    scanf("%s", code);

    // Call save request
    Internal_Save_Request(student_id, code, course_head, passed_courses);

    // Recurse for next input
    Recursive_Register_Loop(current + 1, total, student_id, course_head, passed_courses);
}

// --- MAIN STUDENT REQUEST FUNCTION ---
void Student_Request_Session(char *student_id, Node *course_head) {
    char passed_courses[1024];

    // 1. Get Passed Courses
    Helper_Get_Passed(student_id, passed_courses);

    if (strcmp(passed_courses, "NOT_FOUND") == 0) {
        return; // Error already printed in Helper
    }

    printf(CYAN"\n--- Eligible Courses (Checked via Tree) ---\n"RESET);
    // 2. Display options using Tree Traversal
    Display_Eligible_Courses(course_head, passed_courses);
    printf(CYAN"-------------------------------------------\n"RESET);

    // 3. User Input
    int count;
    printf(BLUE"\nHow many courses do you want to register? "RESET);
    if (scanf("%d", &count) != 1) {
        while(getchar() != '\n'); // Clear buffer
        return;
    }

    if (count <= 0) return;

    printf(CYAN"Please enter the %d course codes:\n"RESET, count);

    // 4. Start Registration Loop
    Recursive_Register_Loop(1, count, student_id, course_head, passed_courses);

    printf(CYAN"\n--- Registration Session Complete ---\n"RESET);
}