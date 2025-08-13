#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 100

char Stack[SIZE];
int Top = -1;

void push(char ch);
char pop();
void infix_to_postfix(char *Expr);
int precedence(char op);

int main() {
    char Expr[SIZE];

    printf("Program to convert infix expression into postfix expression:\n");
    printf("Enter your expression (end with '#'): ");

    fgets(Expr, SIZE, stdin); // Safer input method

    printf("Infix Expression: %s", Expr);
    printf("Postfix Expression: ");
    infix_to_postfix(Expr);

    return 0;
}

void push(char ch) {
    if (Top >= SIZE - 1) {
        printf("\nStack overflow");
        exit(1);
    }
    Stack[++Top] = ch;
}

char pop() {
    if (Top < 0) {
        printf("\nStack underflow");
        exit(1);
    }
    return Stack[Top--];
}

int precedence(char op) {
    switch (op) {
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        case '(': return 1;
        case '#': return 0; // Sentinel has lowest precedence
        default: return 0;
    }
}

void infix_to_postfix(char *Expr) {
    int i = 0;
    push('#'); // Sentinel at bottom of stack

    while (Expr[i] != '\0' && Expr[i] != '\n') {
        if (isalnum(Expr[i])) {
            printf("%c", Expr[i++]); // Operand → output
        }
        else if (Expr[i] == '(') {
            push(Expr[i++]);
        }
        else if (Expr[i] == ')') {
            while (Stack[Top] != '(') {
                printf("%c", pop());
            }
            pop(); // Remove '('
            i++;
        }
        else { // Operator
            while (precedence(Stack[Top]) >= precedence(Expr[i])) {
                printf("%c", pop());
            }
            push(Expr[i++]);
        }
    }

    while (Stack[Top] != '#') { // Pop remaining operators
        printf("%c", pop());
    }
    printf("\n");
}
