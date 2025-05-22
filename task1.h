#pragma once

#define MAX_SIZE 100

typedef struct {
    char* data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);
void push(Stack* s, char* item);
char* pop(Stack* s);
int isOperator(char c);
char* postfixToPrefix(const char* postfix, int* errorPos);
