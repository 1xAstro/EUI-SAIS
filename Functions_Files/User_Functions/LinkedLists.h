#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Supports both Linked Lists (next) and Binary Trees (left/right)
typedef struct Node {
    char code[16];
    char prereq1[16];
    char prereq2[16];
    char title[128];

    struct Node *next;  // For Linked List usage
    struct Node *left;  // For Binary Tree usage
    struct Node *right; // For Binary Tree usage
} Node;

// Function Prototypes
void Insert_Course_Tree(Node **root, char *c, char *p1, char *p2, char *t);
void Load_Courses_Tree(Node **root); // Builds the Tree
void freeTree(Node *root);

#endif