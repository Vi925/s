// Implementation: Recursive Descent Parser (C Implementation) 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char input[100];  // Input string
int pos = 0;      // Position to traverse input

// Function prototypes
void E();
void EPrime();
void T();
void TPrime();
void F();

void error() {
    printf("String is not accepted\n");
    exit(0);
}

// Match function to check if the current input symbol matches expected
void match(char expected) {
    if (input[pos] == expected) {
        pos++;  // Move to next character
    } else {
        error();
    }
}

// Production: E -> TE'
void E() {
    T();
    EPrime();
}

// Production: E' -> +TE' | ε
void EPrime() {
    if (input[pos] == '+') {
        match('+');
        T();
        EPrime();
    }
    // Else, epsilon (do nothing)
}

// Production: T -> FT'
void T() {
    F();
    TPrime();
}

// Production: T' -> *FT' | ε
void TPrime() {
    if (input[pos] == '*') {
        match('*');
        F();
        TPrime();
    }
    // Else, epsilon (do nothing)
}

// Production: F -> (E) | ID
void F() {
    if (input[pos] == '(') {  // Case: (E)
        match('(');
        E();
        match(')');
    } else if (isalpha(input[pos])) {  // Case: ID (single character variable)
        match(input[pos]);
    } else {
        error();
    }
}

int main() {
    printf("Recursive descent parsing for the following grammar:\n");
    printf("E  -> TE'\nE' -> +TE'/@\nT  -> FT'\nT' -> *FT'/@\nF  -> (E)/ID\n");

    printf("Enter the string to be checked: ");
    scanf("%s", input);

    pos = 0;
    E();  // Start parsing

    // If the entire string is consumed, it's valid
    if (input[pos] == '\0') {
        printf("String is accepted\n");
    } else {
        printf("String is not accepted\n");
    }

    return 0;
}