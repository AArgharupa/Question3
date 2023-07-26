#include <stdio.h>
#include <stdlib.h>

// Define a structure for a linked list node
struct ListNode {
    char* data;
    struct ListNode* next;
};

// Function to create a new node
struct ListNode* createNode(const char* str) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = strdup(str);
    newNode->next = NULL;
    return newNode;
}

// Function to add a new node at the end of the list
void addNode(struct ListNode** head, struct ListNode** tail, const char* str) {
    struct ListNode* newNode = createNode(str);

    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

// Function to free the linked list and its nodes
void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_lines>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        printf("Invalid number of lines: %d\n", n);
        return 1;
    }

    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;
    char buffer[1024];

    // Read input line by line and maintain the linked list of last 'n' lines
    while (fgets(buffer, sizeof(buffer), stdin)) {
        addNode(&head, &tail, buffer);
        if (n > 0) {
            // If the list size exceeds 'n', remove the first node
            if (n == 1) {
                free(head->data);
                free(head);
                head = tail = NULL;
            } else {
                struct ListNode* temp = head;
                head = head->next;
                free(temp->data);
                free(temp);
            }
            n--;
        }
    }

    // Print the last 'n' lines in reverse order
    while (tail != NULL) {
        printf("%s", tail->data);
        tail = tail->next;
    }

    // Free memory used by the linked list
    freeList(head);

    return 0;
}
