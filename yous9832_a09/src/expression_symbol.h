/*
--------------------------------------------------
Project: a9q2
File:    expression_symbol.h
Author:  Antoine Youssef, 169069832, yous9832@mylaurier.ca
Version: 2025-03-15
--------------------------------------------------
*/

#ifndef EXPRESSION_SYMBOL_H
#define EXPRESSION_SYMBOL_H

#include "common_queue_stack.h"
#include "hash.h"

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr);

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr);

int evaluate_postfix(QUEUE queue);

DATA evaluate_statement(HASHTABLE *ht, char* statement);

#endif
