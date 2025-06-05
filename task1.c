#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "task1.h"

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack* s, char* item) {
    if (isFull(s)) {
        fprintf(stderr, "Ошибка: стек переполнен\n");
        exit(EXIT_FAILURE);
    }
    s->data[++s->top] = item;
}

char* pop(Stack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Ошибка: стек пуст\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

char* postfixToPrefix(const char* postfix, int* errorPos) {
    Stack s;
    initStack(&s);
    int len = strlen(postfix);
    char* operand1, * operand2, * temp;
    char* result = NULL;

    for (int i = 0; i < len; i++) {
        char c = postfix[i];

        if (isspace(c)) {
            continue;
        }

        if (isalnum(c)) {
            char* operand = malloc(2 * sizeof(char));
            operand[0] = c;
            operand[1] = '\0';
            push(&s, operand);
        }
        
        else if (isOperator(c)) {
            if (s.top < 1) {
                *errorPos = i;
                return NULL;
            }
            operand2 = pop(&s);
            operand1 = pop(&s);

            int newLen = strlen(operand1) + strlen(operand2) + 2;
            temp = malloc(newLen * sizeof(char));
            temp[0] = c;
            temp[1] = '\0';
            strcat(temp, operand1);
            strcat(temp, operand2);

            push(&s, temp);

            free(operand1);
            free(operand2);
        }
        else {
            *errorPos = i;
            return NULL;
        }
    }

    if (s.top != 0) {
        *errorPos = len;
        return NULL;
    }

    result = pop(&s);
    return result;
}

int StackUse() {
    int errorPos = -1;
    char* postfix = NULL;
    printf("Введите строку в постфиксной форме: ");
    InsertStr(&postfix);
    char* prefix = postfixToPrefix(postfix, &errorPos);

    if (prefix != NULL) {
        printf("\nСтрока в префиксной форме: %s\n", prefix);
        free(prefix);
    }
    else {
        printf("Ошибка в позиции %d\n", errorPos);
    }

    return 0;
}