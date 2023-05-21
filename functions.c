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

Node* create_node(const char* name, filetype type) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->parent = NULL;
    node->children = NULL;
    node->type = type;
    return node;
}

void create_file(Node* current_directory, char* name, filetype type){
    Node* new_file = create_node(name, type);
    new_file->parent = current_directory;
    add_to_node_list(&current_directory->children, new_file);    
}

// Rename a file node with the given name under the specified directory

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
        fprintf(stderr, "Error: cannot delete %s : no such file or directory\n", name);
        return;
    }
    NodeList* current = current_directory->children;
    NodeList* previous = NULL;
    while(current != NULL) {
        if(strcmp(current->node->name, name) == 0) {
            if (current->node->type == DIR) {
                fprintf(stderr, "Error: cannot delete %s : is a directory\n", name);
                return;
            }
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

void delete_directory(Node* current_directory, char* name) {
    if (current_directory->children == NULL) {
        fprintf(stderr, "Error: cannot delete %s : no such file or directory\n", name);
        return;
    }
    NodeList* current = current_directory->children;
    NodeList* previous = NULL;
    while(current != NULL) {
        if(strcmp(current->node->name, name) == 0) {
            if (current->node->type == FIL) {
                fprintf(stderr, "Error: cannot delete %s : is a file\n", name);
                return;
            }
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

char* fullPath(Node* node, char* path) {
    if (node->parent == NULL) {
        if (strcmp(path, "") == 0) {
            return "/";
        }
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
            if (current->node->type == FIL) {
                fprintf(stderr, "Error: cannot cd : %s is a file\n", name);
                return;
            }
            *current_directory = current->node;
            return;
        }
        current = current->next;
    }
    fprintf(stderr, "Error: cannot cd : %s no such file or directory\n", name);
}

void ps1(Node* current_directory, int using_stdin, int using_ps1) {
    if (using_stdin == 1) {
        if (using_ps1 == 1) {
            printf("%s> ", get_pwd(current_directory));
        }else{
            printf("minshell> ");
        }
    }
}