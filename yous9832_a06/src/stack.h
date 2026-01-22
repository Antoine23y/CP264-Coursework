/*
--------------------------------------------------
Project: a6q2
File:    stack.h
Author:  Antoine Youssef, 169069832, yous9832@mylaurier.ca
Version: 2025-01-16
--------------------------------------------------
*/

#ifndef STACK_H
#define STACK_H
#include "common.h"

typedef struct stack {
  int length;
  NODE *top;
} STACK;

void push(STACK *sp, NODE *np);
NODE *pop(STACK *sp);
void clean_stack(STACK *sp);

#endif
