#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdlib.h>
#include <stdbool.h>

struct DequeNode {
    void *ptr;
    struct DequeNode *succ, *prec;
};

typedef struct Deque {
	unsigned count;
	struct DequeNode *top, *bottom;
} Deque;

Deque *createDeque(void);

Deque *deleteDeque(Deque *);

void *front(Deque *);

void *back(Deque *);

Deque *pushFront(Deque *, void *);

Deque *pushBack(Deque *, void *);

void *popFront(Deque *);

void *popBack(Deque *);

bool isEmpty(Deque *);

unsigned nodeCount(Deque *);

#endif

