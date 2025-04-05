// Implementation: Lexer (Lex) for Complex Rule Matching 
 
%{
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0;
%}

d [0-9]

%%

({d})*00 {
    c1++;
    printf("%s rule A\n", yytext);
}

({d})*222({d})* {
    c2++;
    printf("%s rule B\n", yytext);
}

(1(0)*(11|01)(01*01|00*10(0)*(11|1))*0)(1|10(0)*(11|01)(01*01|00*10(0)*(11|1))*10)* {
    c4++;
    printf("%s rule D\n", yytext);
}

({d})*1{d}{9} {
    c5++;
    printf("%s rule E\n", yytext);
}

{d}{4} {
    int sum = 0, i;
    for (i = 0; i < 4; i++) {
        sum = sum + yytext[i] - 48;
    }
    if (sum == 9) {
        c6++;
        printf("%s rule F\n", yytext);
    } else {
        sum = 1;
        for (i = 0; i < 3; i++) {
            if (yytext[i] > yytext[i + 1]) {
                sum = 0;
                break;
            }
        }
        if (sum == 1) {
            c7++;
            printf("%s rule G\n", yytext);
        } else {
            printf("%s doesn't match any rule\n", yytext);
        }
    }
}

({d})* {
    int i, c = 0;
    if (yyleng < 5) {
        printf("%s doesn't match any rule\n", yytext);
    } else {
        for (i = 0; i < 5; i++) {
            if (yytext[i] == '5') {
                c++;
            }
        }
        if (c >= 2) {
            for (; i < yyleng; i++) {
                if (yytext[i - 5] == '5') {
                    c--;
                }
                if (yytext[i] == '5') {
                    c++;
                }
                if (c < 2) {
                    printf("%s doesn't match any rule\n", yytext);
                    break;
                }
            }
            if (yyleng == i) {
                printf("%s rule C\n", yytext);
                c3++;
            }
        } else {
            printf("%s doesn't match any rule\n", yytext);
        }
    }
}

%%

int main() {
    printf("Enter text\n");
    yylex();
    printf("Total number of tokens matching rules are:\n");
    printf("Rule A: %d\n", c1);
    printf("Rule B: %d\n", c2);
    printf("Rule C: %d\n", c3);
    printf("Rule D: %d\n", c4);
    printf("Rule E: %d\n", c5);
    printf("Rule F: %d\n", c6);
    printf("Rule G: %d\n", c7);
    return 0;
}

