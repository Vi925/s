%{
#include <stdio.h>
#include <ctype.h>
%}

%option noyywrap

%%
[a-zA-Z]+ {
    char first_letter = yytext[0];
    if (isalpha(first_letter)) {
        if (first_letter == 'a' || first_letter == 'e' || first_letter == 'i' || first_letter == 'o' || first_letter == 'u' ||
            first_letter == 'A' || first_letter == 'E' || first_letter == 'I' || first_letter == 'O' || first_letter == 'U') {
            printf("%say ", yytext);
        } else {
            printf("%s%cay ", yytext + 1, first_letter);
        }
    }
}
[^a-zA-Z]+ {
    printf("%s", yytext);
}
%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}

