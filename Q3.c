#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a line of input
typedef struct Line {
    char* text;
    struct Line* next;
} Line;

// Function to create a new line node
Line* createLine(const char* text) {
    Line* newLine = (Line*)malloc(sizeof(Line));
    newLine->text = strdup(text);
    newLine->next = NULL;
    return newLine;
}

// Function to add a new line to the end of the linked list
void addLine(Line** head, const char* text, int n) {
    Line* newLine = createLine(text);

    if (*head == NULL) {
        *head = newLine;
        return;
    }

    if (n == 1) {
        Line* temp = *head;
        *head = newLine;
        newLine->next = temp;
        return;
    }

    Line* current = *head;
    int count = 1;
    while (current->next != NULL && count < n - 1) {
        current = current->next;
        count++;
    }

    Line* temp = current->next;
    current->next = newLine;
    newLine->next = temp;
}

// Function to free the memory used by the linked list
void freeLines(Line* head) {
    while (head != NULL) {
        Line* temp = head;
        head = head->next;
        free(temp->text);
        free(temp);
    }
}

// Function to print the last n lines from the linked list
void printLastNLines(Line* head) {
    if (head == NULL) {
        printf("No lines to display.\n");
        return;
    }

    Line* current = head;
    while (current != NULL) {
        printf("%s", current->text);
        current = current->next;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Invalid value of n: %d\n", n);
        return 1;
    }

    Line* head = NULL;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        addLine(&head, buffer, n);
    }

    printLastNLines(head);

    // Free the allocated memory
    freeLines(head);

    return 0;
}
