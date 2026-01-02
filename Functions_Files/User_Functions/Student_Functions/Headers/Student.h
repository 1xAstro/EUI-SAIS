#ifndef STUDENT_H
#define STUDENT_H
#include "../User_Functions/User_Struct.h"

// 2. Add other student commands
void view_student_dashboard(char *username);


// Core Login Functions
User* load_students_from_csv();
int perform_student_login(char *ID, char *Password, char *Name);
void free_student_list(User *head);

#endif
