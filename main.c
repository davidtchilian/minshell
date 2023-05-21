#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Rename a file node with the given name under the specified directory

int main() {
    printf("\n\n\n");
    Node* root = create_node("Root", DIR);
    Node* current_directory = root;
    create_file(current_directory, "file1", FIL);
    create_file(current_directory, "folder2", DIR);

    list_directory(current_directory);
    delete_file(current_directory, "file1");
    list_directory(current_directory);

    change_directory(&current_directory, "folder2");
    create_file(current_directory, "file3", FIL);
    create_file(current_directory, "file4", DIR);



    printf("\n\n\n");
    return 0;
}
