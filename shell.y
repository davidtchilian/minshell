%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

extern FILE *yyin;
void yyerror(char*);
int yylex();
int yyparse();
int lineno = 1;
int usingfile = 0;
Node* current_directory;


%}


%union {    
    char* str;
}

%token LS CAT RM TOUCH CP MV MKDIR RMDIR CD PWD
%token <str> FILENAME
%token <str> COMMENT
%token EOL

%start S
%%

S:
    Token                    {  }
    | S Token                {  }
    ;

Token: 
    error EOL                                                   { lineno++; if (yyin == stdin) { printf("shell> "); } }
    | EOL                                                       { lineno++; if (yyin == stdin) { printf("shell> "); } }
    | COMMENT                                                   { }
    | LS                                                        { 
        list_directory(current_directory);
    }
    | PWD                                                       {
        printf("pwd detected !\n");
        if (current_directory == NULL) {
            printf("current directory is null\n");
            exit(1);
        }
        if (current_directory->parent == NULL) {
            printf("parent is null in pwd call\n");
        }
        printf("really not null ?\n");
        printf("%s\n", get_pwd(current_directory));
    }
    | MKDIR FILENAME                                            { 
        create_file(current_directory, $2);
    }
    | CD FILENAME                                               { 
        change_directory(&current_directory, $2);
    }
    ;
%%

void yyerror(char *s) {
    if (yyin != stdin) {
        fprintf(stderr, "\033[1;31m%s\n\033[0m", s);
        exit(1);
    }
    else {
        fprintf(stderr, "\033[1;31m%s\n\033[0m", s);
    }
}

int main(int argc, char const *argv[]){
    char* str = malloc(100*sizeof(char));
    Node current_directory;
    strcpy(current_directory.name, "/");
    current_directory.parent = NULL;
    current_directory.children = NULL;
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Could not open %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    }else{
        yyin = stdin;
        printf("shell> ");
    }
    
    yyparse();
    return 0;
}
