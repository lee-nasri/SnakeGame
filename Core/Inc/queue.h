/*
 * queue.h
 *
 *  Created on: May 14, 2020
 *      Author: Nasmeen
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity);

int isFull(struct Queue* queue);

int isEmpty(struct Queue* queue);

void enqueue(struct Queue* queue, int item);

int dequeue(struct Queue* queue);

int front(struct Queue* queue);

int rear(struct Queue* queue);





#endif /* INC_QUEUE_H_ */
