// Write a program to design Lexical Analyzer in C Language 
// (to recognize any five keywords, identifiers, numbers, operators and punctuations).

// Sample Input:
// Enter number of lines: 3
// int int nti iiit;
// float hi 23.5
// 1a 2b e3;

// Sample output:
// Keywords: 3 (int int float)
// Operators: 0
// Constants: 1 (23.5)
// Punctuations: 2 (; ;)
// Identifiers: 3 (nti iiit hi)
// Tokens: 9

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_LENGTH 100

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
const int numKeywords = 32;
const char operators[] = "+-*/%=<>&|!^";
const char punctuations[] = ",;(){}[]";

int isKey(const char *word) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOp(char ch) {
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int isPun(char ch) {
    for (int i = 0; i < strlen(punctuations); i++) {
        if (ch == punctuations[i]) {
            return 1;
        }
    }
    return 0;
}

int isNumber(const char *word) {
    int dotCount = 0;
    for (int i = 0; word[i]; i++) {
        if (word[i] == '.') {
            dotCount++;
            if (dotCount > 1) return 0;
        } else if (!isdigit(word[i])) {
            return 0;
        }
    }
    return 1;
}

int isId(const char *word) {
    if (isdigit(word[0]) || word[0] == '\0') return 0;
    for (int i = 0; word[i]; i++) {
        if (!isalnum(word[i]) && word[i] != '_') return 0;
    }
    return 1;
}

void processToken(const char *token, char processedTokens[MAX_TOKENS][MAX_LENGTH], int *tokenCount) {
    char buffer[MAX_LENGTH];
    int bufferId = 0;
    for (int i = 0; token[i]; i++) {
        if (isPun(token[i])) {
            if (bufferId > 0) {
                buffer[bufferId] = '\0';
                strcpy(processedTokens[(*tokenCount)++], buffer);
                bufferId = 0;
            }
            char punct[2] = {token[i], '\0'};
            strcpy(processedTokens[(*tokenCount)++], punct);
        } else {
            buffer[bufferId++] = token[i];
        }
    }
    if (bufferId > 0) {
        buffer[bufferId] = '\0';
        strcpy(processedTokens[(*tokenCount)++], buffer);
    }
}

int main() {
    int numLines;
    printf("Enter number of lines: ");
    scanf("%d", &numLines);
    getchar(); // Clear newline character from input buffer

    char line[MAX_LENGTH];
    char tokens[MAX_TOKENS][MAX_LENGTH];
    int tokenCount = 0;

    printf("Enter code:\n");
    for (int i = 0; i < numLines; i++) {
        fgets(line, MAX_LENGTH, stdin);
        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            processToken(token, tokens, &tokenCount);
            token = strtok(NULL, " \t\n");
        }
    }

    int keyCnt = 0, opCntt = 0, conCnt = 0, punCnt = 0, idCnt = 0;
    char keyFnd[MAX_TOKENS][MAX_LENGTH], idFnd[MAX_TOKENS][MAX_LENGTH], conFnd[MAX_TOKENS][MAX_LENGTH];
    char punFnd[MAX_TOKENS];

    for (int i = 0; i < tokenCount; i++) {
        if (isKey(tokens[i])) {
            strcpy(keyFnd[keyCnt++], tokens[i]);
        } else if (isNumber(tokens[i])) {
            strcpy(conFnd[conCnt++], tokens[i]);
        } else if (isId(tokens[i])) {
            strcpy(idFnd[idCnt++], tokens[i]);
        } else if (strlen(tokens[i]) == 1 && isPun(tokens[i][0])) {
            punFnd[punCnt++] = tokens[i][0];
        }
    }

    printf("Keywords: %d (", keyCnt);
    for (int i = 0; i < keyCnt; i++) {
        printf("%s%s", keyFnd[i], (i + 1 < keyCnt) ? " " : "");
    }
    printf(")\n");

    printf("Operators: %d\n", opCntt);

    printf("Constants: %d (", conCnt);
    for (int i = 0; i < conCnt; i++) {
        printf("%s%s", conFnd[i], (i + 1 < conCnt) ? " " : "");
    }
    printf(")\n");

    printf("Punctuations: %d (", punCnt);
    for (int i = 0; i < punCnt; i++) {
        printf("%c%s", punFnd[i], (i + 1 < punCnt) ? " " : "");
    }
    printf(")\n");

    printf("Identifiers: %d (", idCnt);
    for (int i = 0; i < idCnt; i++) {
        printf("%s%s", idFnd[i], (i + 1 < idCnt) ? " " : "");
    }
    printf(")\n");

    printf("Tokens: %d\n", keyCnt + opCntt + conCnt + punCnt + idCnt);

    return 0;
}