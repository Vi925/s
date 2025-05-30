// Implementation: Parser (Yacc) for Arithmetic Calculator 
 
%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token NUMBER
%token EOL  // Token for end of line

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:
    | input line
    ;

line:
    expr EOL { printf("Result: %d\n", $1); }
    ;

expr:
    NUMBER           { $$ = $1; }
    | expr '+' expr  { $$ = $1 + $3; }
    | expr '-' expr  { $$ = $1 - $3; }
    | expr '*' expr  { $$ = $1 * $3; }
    | expr '/' expr  { $$ = $1 / $3; }
    | '(' expr ')'   { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter an expression: ");
    return yyparse();
}

