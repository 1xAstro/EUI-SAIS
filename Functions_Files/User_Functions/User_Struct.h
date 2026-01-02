#ifndef USERSTRUCT_H
#define USERSTRUCT_H

typedef struct User {
    char ID[150];
    char Password[50];
    char Name[100];
    struct User* next;
    // Add any other common fields here
} User;

#endif