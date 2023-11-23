#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to run a Python script with the provided argument
int runPythonScript(const char* input_string, char* val, size_t val_size) {
    char command[200];
    snprintf(command, sizeof(command), "python slave.py \"%s\"", input_string);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        return -1;
    }

    char capitalized_string[100];  // Used to capture the capitalized string

    // Read the output from Python
    if (fgets(capitalized_string, sizeof(capitalized_string), fp) != NULL) {
        // Remove newline characters if present
        size_t len = strlen(capitalized_string);
        if (len > 0 && (capitalized_string[len - 1] == '\n' || capitalized_string[len - 1] == '\r')) {
            capitalized_string[len - 1] = '\0';
        }

        // Now, capture the value of 'val' from Python
        if (fgets(val, val_size, fp) != NULL) {
            len = strlen(val);
            if (len > 0 && (val[len - 1] == '\n' || val[len - 1] == '\r')) {
                val[len - 1] = '\0';
            }
        } else {
            pclose(fp);
            return -1;
        }
    } else {
        pclose(fp);
        return -1;
    }
    pclose(fp);
    return 0;
}

struct node {
    char url[100];
    struct node* pre;
    struct node* next;
};

struct node* createNode(const char* url) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strncpy(newNode->url, url, sizeof(newNode->url));
    newNode->url[sizeof(newNode->url) - 1] = '\0';
    newNode->next = NULL;
    newNode->pre = NULL;
    return newNode;
}

struct node* insertNode(struct node* current, const char* url) {
    struct node* newNode = createNode(url);

    if (current != NULL) {
        newNode->pre = current;
        current->next = newNode;
    }
    return newNode;
}

void display(struct node* current) {
    if (current == NULL) {
        printf("No web page to display.\n");
    } else {
        printf("Current page: %s\n", current->url);
    }
}

struct node* goBack(struct node* current) {
    if (current == NULL || current->pre == NULL) {
        printf("Cannot go back.\n");
        return current;
    }

    return current->pre;
}

struct node* goForward(struct node* current) {
    if (current == NULL || current->next == NULL) {
        printf("Cannot go forward.\n");
        return current;
    }

    return current->next;
}

void freeList(struct node* head) {
    struct node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct node* head = NULL;
    struct node* current = NULL;

    int choice;
    char url[100];

    do {
        printf("\nMain Menu:\n");
        printf("1. Search the web\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char current_url[100];
        int result;
        char val[100];
        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                if (current == NULL) {
                    head = insertNode(head, url);
                    current = head;
                } else {
                    current = insertNode(current, url);
                }
                result = runPythonScript(url, val, sizeof(val));
                // if (result == -1) {
                //     printf("Error: Python script execution failed for URL: %s\n", url);
                // } else {
                //     int res = strcmp(val, "11");
                //     if (res == 0) {
                //         printf("Python Back.\n");
                //     }

                //     res = strcmp(val, "22");
                //     if (res == 0) {
                //         printf("Python Fwd.\n");
                //     }
                // }
                break;
            case 2:
                current = goBack(current);
                strcpy(current_url, current->url);
                result = runPythonScript(current_url, val, sizeof(val));
                break;
            case 3:
                current = goForward(current);
                strcpy(current_url, current->url);
                result = runPythonScript(current_url, val, sizeof(val));
                break;
            case 4:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    freeList(head);

    return 0;
}