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
    printf("%c", Stack[Top--]);
}

int isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9');
}

void infix_to_postfix(const char* Expr) {
    for (int i = 0; Expr[i]; i++) {
        char ch = Expr[i];
        if (isOperand(ch)) printf("%c", ch);
        else if (ch == '(') push(ch);
        else if (ch == ')') {
            while (Top >= 0 && Stack[Top] != '(') pop();
            if (Top >= 0) Top--; // remove '('
        } else {
            while (Top >= 0 && Stack[Top] != '(' &&
                  ((ch == '+' || ch == '-') ||
                   (ch == '*' || ch == '/') && (Stack[Top] == '*' || Stack[Top] == '/' || Stack[Top] == '^') ||
                   (ch == '^' && Stack[Top] == '^')))
                pop();
            push(ch);
        }
    }
    while (Top >= 0) pop();
}

int main() {
    const char* infixExpr = "A-B/(C*D+E)";
    printf("Infix Expression: %s\n", infixExpr);
    printf("Postfix Expression: ");
    infix_to_postfix(infixExpr);
    printf("\n");
    return 0;
}
