#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>




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
    printf("path: %s\n", path);
    if (node->parent == NULL) {
        printf("debug\n");
        if (strcmp(path, "") == 0) {
            printf("root\n");
            return "/";
        }
        return path;
    }
    printf("debug2\n");
    char* temp = (char*)malloc(sizeof(char) * 300);
    
    strcat(temp, "/");
    strcat(temp, node->name);
    strcat(temp, path);
    strcpy(path, temp);

    free(temp);

    return fullPath(node->parent, path);
} 

char* get_pwd(Node* current_directory) {
    char* path = malloc(sizeof(char) * 300);
    strcpy(path, "");
    return fullPath(current_directory, path);
}

void list_directory(Node* current_directory) {
    printf(". .. ");
    if (current_directory->children == NULL) {
        printf("\n");
        return;
    }
    NodeList* current = current_directory->children;
    print_node_list(current);
    printf("\n");
}

void change_directory(Node** current_directory, char* name) {
    if (strcmp(name, "..") == 0) {
        if ((*current_directory)->parent == NULL) {
            return;
        }
        *current_directory = (*current_directory)->parent;
        return;
    }
    NodeList* current = (*current_directory)->children;
    while(current != NULL) {
        if (strcmp(current->node->name, name) == 0) {
            *current_directory = current->node;
            return;
        }
        current = current->next;
    }
}