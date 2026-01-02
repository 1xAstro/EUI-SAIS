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

// --- CONFIGURATION: RELATIVE PATHS ---
#define DB_PATH "../Project/DataBases/Student_DataBase.csv"
#define TEMP_PATH "../Project/DataBases/temp_db.csv"
#define BACKUP_PATH "../Project/DataBases/Student_DataBase_Old.csv"

// We include the same Safe CSV parser here to ensure Admin reads correctly too
void get_csv_field_admin(char *line, int index, char *output_buffer) {
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

void Admin_Admit_Requests() {
    FILE *file = fopen(DB_PATH, "r");
    FILE *temp = fopen(TEMP_PATH, "w");

    if (!file || !temp) {
        printf(RED"Error: Could not open database at %s\n"RESET, DB_PATH);
        if (file) fclose(file);
        return;
    }

    char line[MAX_LINE];
    printf(CYAN"\n--- Processing Pending Requests ---\n"RESET);

    while (fgets(line, MAX_LINE, file)) {
        char original_line[MAX_LINE];
        strcpy(original_line, line);

        char id[150], pass[50], name[100], passed[512], reg[512], req[512];

        // Use Safe Parser
        get_csv_field_admin(line, 0, id);
        get_csv_field_admin(line, 1, pass);
        get_csv_field_admin(line, 2, name);
        get_csv_field_admin(line, 3, passed);
        get_csv_field_admin(line, 4, reg);
        get_csv_field_admin(line, 5, req);

        // Header Check
        if (strcmp(id, "ID") == 0) {
            fprintf(temp, "%s", original_line);
            continue;
        }

        if (strlen(passed) == 0) strcpy(passed, "None");
        if (strlen(reg) == 0) strcpy(reg, "None");
        if (strlen(req) == 0) strcpy(req, "None");

        // LOGIC: Is there a request?
        if (strcmp(req, "None") != 0 && strlen(req) > 0) {

            printf(YELLOW"\nStudent: %s (ID: %s)\n", name, id);
            printf("Wants to Register: [%s]\n"RESET, req);
            printf(BLUE"Admit this student? (y/n): "RESET);

            char choice;
            while(getchar() != '\n' && !feof(stdin));
            scanf("%c", &choice);

            if (choice == 'y' || choice == 'Y') {
                // APPROVE: Move Req (Col F) to Reg (Col E)
                if (strcmp(reg, "None") == 0) {
                    fprintf(temp, "%s,%s,%s,%s,%s,None\n", id, pass, name, passed, req);
                } else {
                    // CHANGE IS HERE: Used '-' instead of ';'
                    fprintf(temp, "%s,%s,%s,%s,%s-%s,None\n", id, pass, name, passed, reg, req);
                }
                printf(GREEN"  -> Student Admitted.\n"RESET);
            } else {
                // DENY: Clear Req (Col F)
                fprintf(temp, "%s,%s,%s,%s,%s,None\n", id, pass, name, passed, reg);
                printf(RED"  -> Request Denied.\n"RESET);
            }
        } else {
            fprintf(temp, "%s", original_line);
        }
    }

    fclose(file);
    fclose(temp);

    remove(BACKUP_PATH);
    rename(DB_PATH, BACKUP_PATH);
    rename(TEMP_PATH, DB_PATH);
    remove(BACKUP_PATH);
}