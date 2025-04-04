%{
#include <stdio.h>
#include <string.h>

int keywords = 0, identifiers = 0, constants = 0, operators = 0, punctuations = 0, total_tokens = 0;


char *keyword_list[] = {"int", "float", "char", "double", "return"};
int is_keyword(const char *word) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(word, keyword_list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
%}

%%

[a-zA-Z_][a-zA-Z0-9_]* {
    if (is_keyword(yytext)) {
        keywords++;
    } else {
        identifiers++;
    }
    total_tokens++;
}

[0-9]+ {
    constants++;
    total_tokens++;
}


[+\-*/=<>] {
    operators++;
    total_tokens++;
}

[;,.()] {
    punctuations++;
    total_tokens++;
}

[ \t] { /* Do nothing */ }

\n { return 0; }


. { printf("Invalid token: %s\n", yytext); }

%%

int main() {
    printf("Enter a statement: ");
    yylex();


    printf("Number of Keywords: %d\n", keywords);
    printf("Number of Constants: %d\n", constants);
    printf("Number of Identifiers: %d\n", identifiers);
    printf("Number of Operators: %d\n", operators);
    printf("Number of Punctuations: %d\n", punctuations);
    printf("Total Number of Tokens are: %d\n", total_tokens);

    return 0;
}

