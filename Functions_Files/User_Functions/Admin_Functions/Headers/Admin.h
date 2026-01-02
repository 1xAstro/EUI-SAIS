#ifndef ADMIN_H
#define ADMIN_H
#include "../User_Functions/User_Struct.h"

// 2. Add other student commands
void view_admin_dashboard(char *username);

// Core Login Functions
User* load_Admin_from_csv();
int perform_admin_login(char *Email, char *Password, char *Name);
void free_admin_list(User *head);

#endif
