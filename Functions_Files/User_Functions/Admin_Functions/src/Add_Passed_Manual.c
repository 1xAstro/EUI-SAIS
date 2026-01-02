#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/Admin_Courses.h"

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

#define MAX_LINE 2048
#define DB_PATH "DataBases/Student_DataBase.csv"
#define TEMP_PATH "DataBases/temp_db.csv"

// Re-using parser (ensure this is either in a shared header or local to this file)
void get_csv_field_admin(char *line, int index, char *output_buffer);

void Admin_Add_Passed_Courses_Manual() {
    char target_id[150];
    printf(CYAN"\n--- Manually Add Passed Courses ---\n"RESET);
    printf(BLUE"Enter Student ID: "RESET);
    scanf("%149s", target_id);

    FILE *file = fopen(DB_PATH, "r");
    FILE *temp = fopen(TEMP_PATH, "w");

    // Check if files opened correctly (Path Check)
    if (!file || !temp) {
        printf(RED"Error: Could not access database. Check path: %s\n"RESET, DB_PATH);
        if (file) fclose(file);
        return;
    }

    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, MAX_LINE, file)) {
        char id[150], pass[50], name[100], passed[512], reg[512], req[512];
        char original_line[MAX_LINE];

        strcpy(original_line, line);
        get_csv_field_admin(line, 0, id);

        // If this is the student we want to update
        if (strcmp(id, target_id) == 0) {
            found = 1;
            get_csv_field_admin(line, 1, pass);
            get_csv_field_admin(line, 2, name);
            get_csv_field_admin(line, 3, passed);
            get_csv_field_admin(line, 4, reg);
            get_csv_field_admin(line, 5, req);

            printf(GREEN"Student Found: %s\n"RESET, name);
            int num_to_add;
            printf(BLUE"How many passed courses to add?: "RESET);
            scanf("%d", &num_to_add);

            char new_codes[20][25]; // Array to store inputs for later use
            int actual_added_count = 0;

            // Prepare the 'passed' string (handle "None" case)
            char updated_passed[1024];
            if (strcmp(passed, "None") == 0) strcpy(updated_passed, "");
            else strcpy(updated_passed, passed);

            for (int i = 0; i < num_to_add; i++) {
                char code[25];
                printf(BLUE"Enter Course Code %d: "RESET, i + 1);
                scanf("%24s", code);

                // 1. DUPLICATION CHECK: Don't add if already in 'passed'
                if (strstr(updated_passed, code) != NULL) {
                    printf(YELLOW"  ! %s skipped (already passed).\n"RESET, code);
                    continue;
                }

                // 2. Add to the list of courses we are moving
                strcpy(new_codes[actual_added_count], code);
                actual_added_count++;

                // 3. Append to the 'passed' string
                if (strlen(updated_passed) > 0) strcat(updated_passed, "-");
                strcat(updated_passed, code);
            }

            // 4. REMOVE courses from the 'registered' list
            char updated_reg[512] = "";
            if (strcmp(reg, "None") != 0) {
                char *token = strtok(reg, "-");
                while (token != NULL) {
                    int is_moving = 0;
                    for (int j = 0; j < actual_added_count; j++) {
                        if (strcmp(token, new_codes[j]) == 0) {
                            is_moving = 1;
                            break;
                        }
                    }

                    // If the registered course wasn't just marked as passed, keep it
                    if (!is_moving) {
                        if (strlen(updated_reg) > 0) strcat(updated_reg, "-");
                        strcat(updated_reg, token);
                    }
                    token = strtok(NULL, "-");
                }
            }

            // Final check for empty strings
            if (strlen(updated_passed) == 0) strcpy(updated_passed, "None");
            if (strlen(updated_reg) == 0) strcpy(updated_reg, "None");

            // Write the updated row
            fprintf(temp, "%s,%s,%s,%s,%s,%s\n", id, pass, name, updated_passed, updated_reg, req);
            printf(GREEN"Success: Student record updated.\n"RESET);
        } else {
            // Copy other students as they are
            fprintf(temp, "%s", original_line);
        }
    }

    fclose(file);
    fclose(temp);

    // Swap files only if student was found
    if (found) {
        remove(DB_PATH);
        rename(TEMP_PATH, DB_PATH);
    } else {
        printf(RED"ID '%s' not found.\n"RESET, target_id);
        remove(TEMP_PATH);
    }
}