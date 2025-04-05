// Implementation: Lexer (Lex) for Whitespace Removal 
 
%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[ \t\n]+      { printf(" "); } // Replace any sequence of whitespace with a single space
.             { putchar(yytext[0]); } // Copy all other characters as is
%%

int main() {
    char input_file[100], output_file[100];

    // Asking for input file name
    printf("Enter the input file name: ");
    fgets(input_file, sizeof(input_file), stdin);
    input_file[strcspn(input_file, "\n")] = '\0';  // Remove newline character

    // Open the input file
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        perror("Error opening input file");
        exit(1);
    }

    // Asking for output file name
    printf("Enter the output file name: ");
    fgets(output_file, sizeof(output_file), stdin);
    output_file[strcspn(output_file, "\n")] = '\0';  // Remove newline character

    // Open the output file
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        perror("Error opening output file");
        exit(1);
    }

    // Redirect input and output
    stdin = input;
    stdout = output;

    // Start lexical analysis
    yylex();

    // Close the files
    fclose(input);
    fclose(output);

    // Print success message to console (this will be printed to stdout)
    printf("\nFile has been copied successfully, with whitespace replaced.\n");

    return 0;
}

