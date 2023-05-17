%{
  #include "shell.tab.h"
  #include <stdlib.h>
%}


%option noyywrap
%%

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
ln { return LN; }

[a-zA-Z0-9_\-\.]+ { yylval.str = strdup(yytext); return FILENAME; }
"\n" { return EOL; }

. { /* On ignore */ }