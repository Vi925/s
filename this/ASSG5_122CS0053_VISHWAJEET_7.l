// Implementation: Lexer (Lex) for Basic Arithmetic Parser 
 
%{
#include "y.tab.h"
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       { /* Ignore whitespace */ }
\n          { return 0; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"("         { return '('; }
")"         { return ')'; }

%%

int yywrap() {
    return 1;
}
