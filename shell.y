%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

extern FILE *yyin;
extern int yylineno;
extern char* yytext;
void yyerror(char* s);
int yylex();
int yyparse();
Node* current_directory;

%}


%union {    
    char* str;
}

%token LS CAT RM TOUCH CP MV MKDIR RMDIR CD PWD TEST COMMENT
%token <str> FILENAME

%token EOL

%start S
%%

S:
    Token                    {  }
    | S Token                {  }
    ;

Token: 
    error EOL                                                   { if (yyin == stdin) { printf("shell> "); } }
    | EOL                                                       { if (yyin == stdin) { printf("shell> "); } }
    | COMMENT                                                   { }
    | LS                                                        { 
        list_directory(current_directory);
    }
    | PWD                                                       {
        if (current_directory == NULL) {
            printf("current directory is null\n");
            exit(1);
        }
        printf("%s\n", get_pwd(current_directory));
    }
    | MKDIR FILENAME                                            { 
        create_file(current_directory, $2);
    }
    | CD FILENAME                                               { 
        change_directory(&current_directory, $2);
    }
    | TEST                                                      {
        printf("test detected !\n");
        // printf("%s\n", stringtest);
    }
    ;
%%

void yyerror(char *s) {
    /* if (yyin != stdin) {
        fprintf(stderr, "\033[1;31m%s\n\033[0m", s);
        exit(1);
    }
    else {
        fprintf(stderr, "\033[1;31m%s\n\033[0m", s);
    } */
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, yytext);

}

int main(int argc, char const *argv[]){
    char* str = malloc(100*sizeof(char));
    current_directory = (Node*) malloc(sizeof(Node));
    strcpy(current_directory->name, "/");
    current_directory->parent = NULL;
    current_directory->children = NULL;


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
