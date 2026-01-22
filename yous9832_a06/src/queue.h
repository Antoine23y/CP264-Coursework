/*
--------------------------------------------------
Project: a6q1
File:    queue.h
Author:  Antoine Youssef, 169069832, yous9832@mylaurier.ca
Version: 2025-01-16
--------------------------------------------------
*/

#ifndef QUEUE_H
#define QUEUE_H
#include "common.h"

typedef struct queue {
  int length;
  NODE *front;
  NODE *rear;
} QUEUE;

void enqueue(QUEUE *qp, NODE *np);
NODE *dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

#endif
