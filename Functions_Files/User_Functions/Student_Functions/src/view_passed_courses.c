#include <stdio.h>
#include <string.h>
#include "View_Passed_Courses.h"

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

#define DB_PATH "../Project/DataBases/Student_DataBase.csv"
void View_Passed_Courses(const char *student_id) {
    FILE *fp = fopen(DB_PATH, "r");
    if (!fp) {
        printf(RED"[Error] Cannot open students database.\n"RESET);
        return;
    }

    char line[512];
    int found = 0;

    // Skip header row
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        // Remove newline
        line[strcspn(line, "\n")] = '\0';

        // Tokenize CSV columns
        char *id        = strtok(line, ",");
        char *password  = strtok(NULL, ",");
        char *name      = strtok(NULL, ",");
        char *passed    = strtok(NULL, ",");
        char *registered= strtok(NULL, ",");
        char *requested = strtok(NULL, ",");

        if (!id || !passed)
            continue; // skip broken line

        if (strcmp(id, student_id) == 0) {
            found = 1;
            printf("\nStudent: %s (%s)\n", name, id);
            printf(CYAN"Passed Courses: "RESET);
            if (strcmp(passed, "None") == 0)
                printf(YELLOW"No passed courses yet.\n"RESET);
            else
                printf("%s\n", passed);
            break;
        }
    }

    if (!found)
        printf(RED"Student record not found.\n"RESET);

    fclose(fp);
}
