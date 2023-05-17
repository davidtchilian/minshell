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

void print_node_list(NodeList* list) {
    if (list == NULL) {
        return;
    }
    printf("%s ", list->node->name);
    print_node_list(list->next);
}

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

void add_to_node_list(NodeList** list, Node* node) {
    if (*list == NULL) {
        *list = (NodeList*)malloc(sizeof(NodeList));
        (*list)->node = node;
        (*list)->next = NULL;
        return;
    }else{
        NodeList* current = *list;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = (NodeList*)malloc(sizeof(NodeList));
        current->next->node = node;
        current->next->next = NULL;
    }
}

void delete_file(Node* current_directory, char* name) {
    if (current_directory->children == NULL) {
        return;
    }
    NodeList* current = current_directory->children;
    NodeList* previous = NULL;
    while(current != NULL) {
        if(strcmp(current->node->name, name) == 0) {
            if (previous == NULL) {
                current_directory->children = current->next;
            }else{
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void create_file(Node* current_directory, char* name){
    Node* new_file = createNode(name);
    new_file->parent = current_directory;
    add_to_node_list(&current_directory->children, new_file);    
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
        printf("vide\n");
        return;
    }
    NodeList* current = current_directory->children;
    print_node_list(current);
    printf("\n");
}

int main() {
    printf("\n\n\n");
    Node* root = createNode("Root");
    Node* current_directory = root;
    create_file(current_directory, "file1");
    create_file(current_directory, "file2");

    list_directory(current_directory);
    printf("\n\n\n");
    delete_file(current_directory, "file1");
    list_directory(current_directory);

    
    printf("\n\n\n");
    return 0;
}
