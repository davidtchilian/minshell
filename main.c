#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct NodeList NodeList;

typedef struct Node {
    char name[100];
    struct Node* parent;
    NodeList* children;
} Node;

typedef struct NodeList {
    Node* node;
    struct NodeList* next;
} NodeList;

Node* createNode(const char* name) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->parent = NULL;
    node->children = NULL;
    return node;
}

Node* findFile(Node* node, char* name) {
    if(node->children == NULL) {
        return NULL;
    }
    NodeList* current = node->children;
    while(current != NULL) {
        if(strcmp(current->node->name, name) == 0) {
            return current->node;
        }
        current = current->next;
    }
    return NULL;
}

// Delete a file node with the given name under the specified directory

// Rename a file node with the given name under the specified directory

// Change directory to the specified directory among nodelist

void add_to_node_list(NodeList* list, Node* node) {
    printf("Adding %s to nodelist\n", node->name);
    if (list->node == NULL) {
        printf("liste nulle\n");
        list->node = node;
        list->next = NULL;
    } 
    // if (list->next == NULL) {
    //     list->next = (NodeList*)malloc(sizeof(NodeList));
    //     list->next->node = node;
    //     list->next->next = NULL;
    // } else {
    //     // add_to_node_list(list->next, node);
    // }
}

// Create file
void create_file(Node* current_directory, char* name){
    Node* new_file = createNode(name);
    new_file->parent = current_directory;
    printf("1Adding %s to %s\n", new_file->name, current_directory->name);
    add_to_node_list(current_directory->children, new_file);    
}

char* fullPath(Node* node, char* path) {
    if (node->parent == NULL) {
        return path;
    }
    char* temp = (char*)malloc(sizeof(char) * 300);
    
    strcat(temp, "/");
    strcat(temp, node->name);
    strcat(temp, path);
    strcpy(path, temp);

    free(temp);

    return fullPath(node->parent, path);
}

void list_directory(Node* current_directory) {
    if (current_directory->children == NULL) {
        printf("\n");
        return;
    }
    NodeList* current = current_directory->children;
    while (current != NULL) {
        printf("%s ", current->node->name);
        current = current->next;
    }
    printf("\n");
}

int main() {
    printf("\n\n\n");
    Node* root = createNode("Root");
    Node* current_directory = root;
    create_file(current_directory, "file1");
    // create_file(current_directory, "file2");

    // list_directory(current_directory);


    
    printf("\n\n\n");
    return 0;
}
