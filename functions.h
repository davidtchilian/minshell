#ifndef FIGURE_H
#define FIGURE_H

// typedef enum filetype folder or file
typedef enum filetype {
    FIL,
    DIR
} filetype;

typedef struct Node Node;
typedef struct NodeList NodeList;

typedef struct Node {
    char name[100];
    struct Node* parent;
    NodeList* children;
    filetype type;
} Node;

typedef struct NodeList {
    Node* node;
    struct NodeList* next;
} NodeList;





void print_node_list(NodeList* list);
Node* create_node(const char* name, filetype type);
void create_file(Node* current_directory, char* name, filetype type);
void add_to_node_list(NodeList** list, Node* node);
void delete_file(Node* current_directory, char* name);
void delete_directory(Node* current_directory, char* name);
char* fullPath(Node* node, char* path);
char* get_pwd(Node* current_directory);
void list_directory(Node* current_directory);
void change_directory(Node** current_directory, char* name);
void ps1(Node* current_directory, int using_stdin, int using_ps1);









#endif