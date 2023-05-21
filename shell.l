%{
  #include "shell.tab.h"
  #include <stdlib.h>
  #include <stdio.h>
%}


%option noyywrap
%%

"\n" { return EOL; }
^#[^\n]* { return COMMENT; }

ls { return LS; }
cat { return CAT; }
rm { return RM; }
touch { return TOUCH; }
cp { return CP; }
mv { return MV; }
mkdir { return MKDIR; }
rmdir { return RMDIR; }
cd { return CD; }
pwd { return PWD; }
test { return TEST; }
exit { return EXIT; }
echo { return ECHO_COMMAND; }
set { return SET; }
PS1 { return PS1; }

[a-zA-Z0-9_\-\.]+ { yylval.str = strdup(yytext); return FILENAME; }
\".*\"|\'.*\' { yylval.str = strdup(yytext); return TEXT; }

. { /* On ignore */ }
