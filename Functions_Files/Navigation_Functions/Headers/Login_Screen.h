//
// Created by ACER on 12/12/2025.
//

#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H
int Show_Login_Menu();
int Show_Student_Login(char *id_buffer, char *pass_buffer);
int Show_Admin_Login(char *email_buffer, char *pass_buffer);
void Perform_Logout(char *user_name);
#endif //LOGIN_SCREEN_H
