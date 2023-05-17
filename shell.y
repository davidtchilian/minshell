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




%}


%union {    
    char* str;
}

%token LS CAT RM TOUCH CP MV MKDIR RMDIR CD PWD LN
%token <str> FILENAME
%token <str> COMMENT
%token EOL

%start S
%%

S:
    Token                    { }
    | S Token                { }
    ;

Token: 
    error EOL                                                   { }
    | EOL                                                       { lineno++; printf("shell> "); }
    | COMMENT                                                   { }
    | LS                                                        { printf("ls detected !\n"); }

    ;
%%

void yyerror(char *s) {
    fprintf(stderr, "\033[1;31mLine: %d : %s\n\033[0m", lineno, s);
    exit(1);
}



int main(int argc, char const *argv[]){
    char* str = malloc(100*sizeof(char));
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Could not open %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    }
    printf("shell> ");
    yyparse();
}
