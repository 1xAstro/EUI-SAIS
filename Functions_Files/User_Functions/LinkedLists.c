#include "LinkedLists.h"

// CHECK THIS PATH AGAIN:
#define COURSES_DB "../Project/DataBases/courses.txt"
#define MAX_LINE 2048

#define RED   "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

Node* Recursive_Insert(Node *root, char *c, char *p1, char *p2, char *t) {
    // 1. Base Case: Found an empty spot, create the node
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf(RED"Error: Out of memory!\n"RESET);
            return NULL;
        }
        strcpy(newNode->code, c);
        strcpy(newNode->prereq1, p1);
        strcpy(newNode->prereq2, p2);
        strcpy(newNode->title, t);

        newNode->left = NULL;
        newNode->right = NULL;
        newNode->next = NULL;
        return newNode;
    }

    // 2. Sorting Logic (Avoids Infinite Loops)
    int cmp = strcmp(c, root->code);

    if (cmp < 0) {
        // Go Left
        root->left = Recursive_Insert(root->left, c, p1, p2, t);
    }
    else if (cmp > 0) {
        // Go Right
        root->right = Recursive_Insert(root->right, c, p1, p2, t);
    }
    // else: cmp == 0 (Duplicate course code), do nothing/return root

    return root;
}

void Insert_Course_Tree(Node **root, char *c, char *p1, char *p2, char *t) {
    if (root == NULL) return; // Safety check
    *root = Recursive_Insert(*root, c, p1, p2, t);
}

void Load_Courses_Tree(Node **root) {
    FILE *file = fopen(COURSES_DB, "r");

    if (!file) {
        // Try alternate path just in case
        file = fopen("DataBases/courses.txt", "r");
    }

    if (!file) {
        printf(RED"[System] Error: Could not open courses file.\n"RESET);
        return;
    }

    char line[MAX_LINE];
    char code[16], p1[16], p2[16], name[128];

    while (fgets(line, MAX_LINE, file)) {
        // Ensure we strictly get 4 items to avoid reading garbage
        if (sscanf(line, "%s %s %s %[^\n]", code, p1, p2, name) == 4) {
            Insert_Course_Tree(root, code, p1, p2, name);
        }
    }

    fclose(file);
    printf(GREEN"[System] Tree built successfully.\n"RESET);
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}