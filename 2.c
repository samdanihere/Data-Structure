#include <stdio.h>
#define SIZE 100

char Stack[SIZE];
int Top = -1;

void push(char ch) {
    if (Top + 1 >= SIZE) {
        printf("\nStack overflow!");
        return;
    }
    Stack[++Top] = ch;
}

void pop() {
    if (Top < 0) {
        printf("\nStack underflow!");
        return;
    }
    if (Stack[Top] != '(') printf("%c", Stack[Top]);
    Top--;
}

int isOperand(char ch) {
    return (ch >= '0' && ch <= '9') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= 'a' && ch <= 'z');
}

void infix_to_postfix(const char* E) {
    for (int i = 0; E[i]; i++) {
        char c = E[i];
        if (isOperand(c)) printf("%c", c);
        else if (c == '(') push(c);
        else if (c == ')') {
            while (Top >= 0 && Stack[Top] != '(') pop();
            if (Top >= 0) Top--;
        } else {
            while (Top >= 0 && Stack[Top] != '(' &&
                  ((c == '+' || c == '-') ||
                   (c == '*' || c == '/') && (Stack[Top] == '*' || Stack[Top] == '/' || Stack[Top] == '^') ||
                   (c == '^' && Stack[Top] == '^')))
                pop();
            push(c);
        }
    }
    while (Top >= 0) pop();
}

int main() {
    const char* infixExpr = "((A+B)-C*(D/E))";
    printf("Infix Expression: %s\n", infixExpr);
    printf("Postfix Expression: ");
    infix_to_postfix(infixExpr);
    printf("\n");
    return 0;
}
