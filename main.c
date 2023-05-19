#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Delete a file node with the given name under the specified directory

// Rename a file node with the given name under the specified directory

// Change directory to the specified directory among nodelist

// Differentiate between file and directory

int main() {
    printf("\n\n\n");
    Node* root = createNode("Root");
    Node* current_directory = root;
    create_file(current_directory, "file1");
    create_file(current_directory, "file2");

    list_directory(current_directory);
    printf("\n\n");
    delete_file(current_directory, "file1");
    list_directory(current_directory);

    change_directory(&current_directory, "file2");
    printf("pwd: %s\n", get_pwd(current_directory));

    printf("\n\n\n");
    return 0;
}
