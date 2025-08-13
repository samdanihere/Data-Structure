#include <stdio.h>
#define SIZE 100

char S[SIZE]; int T = -1;

void push(char c) {
    if (T + 1 >= SIZE) { printf("\nStack overflow!"); return; }
    S[++T] = c;
}

void pop() {
    if (T < 0) { printf("\nStack underflow!"); return; }
    if (S[T] != '(') printf("%c", S[T]);
    T--;
}

int isOperand(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void to_postfix(const char* E) {
    for (int i = 0; E[i]; i++) {
        char c = E[i];
        if (isOperand(c)) printf("%c", c);
        else if (c == '(') push(c);
        else if (c == ')') {
            while (T >= 0 && S[T] != '(') pop();
            if (T >= 0) T--;
        } else {
            while (T >= 0 && S[T] != '(' &&
                  ((c == '+' || c == '-') ||
                   (c == '*' || c == '/') && (S[T] == '*' || S[T] == '/' || S[T] == '^') ||
                   (c == '^' && S[T] == '^')))
                pop();
            push(c);
        }
    }
    while (T >= 0) pop();
}

int main() {
    const char* infixExpr = "A*(B*C+D*E)/F";
    printf("Infix Expression: %s\n", infixExpr);
    printf("Postfix Expression: ");
    to_postfix(infixExpr);
    printf("\n");
    return 0;
}
