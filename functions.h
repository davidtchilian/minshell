#ifndef FIGURE_H
#define FIGURE_H

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





void print_node_list(NodeList* list);
Node* createNode(const char* name);
void add_to_node_list(NodeList** list, Node* node);
void delete_file(Node* current_directory, char* name);
void create_file(Node* current_directory, char* name);
char* fullPath(Node* node, char* path);
char* get_pwd(Node* current_directory);
void list_directory(Node* current_directory);
void change_directory(Node** current_directory, char* name);









#endif