%{
#include <stdio.h>
%}

%%
[0-9]+\.[0-9]+  { printf("%s is a floating point number\n", yytext); } // Match integers (e.g., 123, 45, etc.)
[0-9]+          { printf("%s is not a floating point number\n", yytext); } // Match invalid input
.               { printf("Invalid input: %s\n", yytext); }
%%

int main() {
    printf("Enter any number: ");
    yylex(); // Start scanning input
    return 0;
}
