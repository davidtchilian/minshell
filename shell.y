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
int using_ps1 = 0;

%}


%union {    
    char* str;
}

%token LS CAT RM TOUCH CP MV MKDIR RMDIR CD PWD TEST COMMENT EXIT ECHO_COMMAND TEXT SET PS1
%token <str> FILENAME

%token EOL

%start S
%%

S:
    Token                    {  }
    | S Token                {  }
    ;

Token: 
    error EOL                                                   { ps1(current_directory, yyin == stdin, using_ps1); }
    | EOL                                                       { ps1(current_directory, yyin == stdin, using_ps1); }
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
        create_file(current_directory, $2, DIR);
    }
    | CD FILENAME                                               { 
        change_directory(&current_directory, $2);
    }
    | TOUCH FILENAME                                            { 
        create_file(current_directory, $2, FIL);
    }
    | RM FILENAME                                               { 
        delete_file(current_directory, $2);
    }
    | RMDIR FILENAME                                            { 
        delete_directory(current_directory, $2);
    }
    | SET SET_OPTION                                            { }
    ;

SET_OPTION:
    | PS1                                                       { 
        using_ps1 = !using_ps1;
    }
    ;
%%

void yyerror(char *s) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, yytext);
}

int main(int argc, char const *argv[]){
    char* str = malloc(100*sizeof(char));
    current_directory = create_node("root", DIR);

    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Could not open %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    }else{
        yyin = stdin;
        printf("minshell> ");
    }
    
    yyparse();
    return 0;
}
