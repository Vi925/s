%{
#include "y.tab.h"  // Includes definitions from the YACC output
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; } // Match numbers
[+\-*/()]       { return yytext[0]; }                    // Match operators and parentheses
[ \t]           ;                                        // Ignore whitespace
.               { printf("Invalid character: %s\n", yytext); } // Handle invalid input
\n              { return EOL; }                          // Signal end of input line
%%

