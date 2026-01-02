#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Headers/Admin_Courses.h"

// Defining color codes for terminal output
#define RED   "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BLUE   "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define RESET "\033[0m"

#define DB_PATH "DataBases/Student_DataBase.csv"
void get_csv_field_admin(char *line, int index, char *output_buffer);

void Add_New_Student(void)
{
    FILE *fp;
    char line[2024];

    // Variables to track the last ID found
    int last_year = -1;
    int last_number = 0;

    /* --- STEP 1: SCAN DATABASE FOR LAST ID --- */
    fp = fopen(DB_PATH,"r");
    if (fp){
        while(fgets(line, sizeof(line), fp)){
            char temp[50];
            int y, n;

            // Using your external helper function
            get_csv_field_admin(line, 0, temp);

            // Parse for format "YY-101NNN"
            // %d handles the number regardless of zeros (e.g. reads 005 as 5)
            if (sscanf(temp, "%d-101%d", &y, &n) == 2){
                last_year = y;
                last_number = n;
            }
        }
        fclose(fp);
    }

    /* --- STEP 2: CALCULATE NEW ID --- */
    char new_id[50];
    int new_year_prefix;
    int new_number_seq;

    // Get current system year
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int current_system_year = (tm->tm_year + 1900) % 100;

    if (last_year == -1) {
        new_year_prefix = current_system_year;
        new_number_seq = 1;
    }
    else if (current_system_year > last_year) {
        new_year_prefix = current_system_year;
        new_number_seq = 1;
    }
    else {
        new_year_prefix = last_year;
        new_number_seq = last_number + 1;
    }

    // FORMAT THE NEW ID: YY-101NNN
    // %03d forces it to be 3 digits (e.g., 1 becomes 001)
    sprintf(new_id, "%d-101%03d", new_year_prefix, new_number_seq);

    printf(CYAN"Auto-Generated Student ID: %s\n"RESET, new_id);

    /* --- STEP 3: DUPLICATE CHECK --- */
    int exists = 0;
    fp = fopen(DB_PATH, "r");
    if (fp) {
        while (fgets(line, sizeof(line), fp)){
            char temp[50];
            get_csv_field_admin(line, 0, temp);
            if (strcmp(temp, new_id) == 0){
                exists = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (exists){
        printf(RED"Error: Generated ID %s conflicts with existing data.\n"RESET, new_id);
        return;
    }

    /* --- STEP 4: GET USER INPUT --- */
    char name[100], password[50];
    int c;

    // Flush the buffer to catch the previous 'Enter' key
    while ((c = getchar()) != '\n' && c != EOF);

    printf(BLUE"Enter Student Name: "RESET);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf(BLUE"Enter Password: "RESET);
    scanf("%49s", password);

    // Clear buffer again after password
    while ((c = getchar()) != '\n' && c != EOF);

    /* --- STEP 5: SAVE TO FILE --- */
    fp = fopen(DB_PATH, "a+");
    if (!fp){
        perror("fopen");
        return;
    }

    fseek(fp, 0, SEEK_END);
    
    fprintf(fp, "%s,%s,%s,None,None,None\n", new_id, password, name);
    fclose(fp);

    printf(GREEN"\nSuccess! Student %s added with ID %s.\n"RESET, name, new_id);
}