#include "deque.h"

Deque *createDeque(void) {
	Deque *D = (Deque *) malloc(sizeof(Deque));
	if (D) D->top = D->bottom = NULL;
	return D;
}

Deque *deleteDeque(Deque *D) {
	struct DequeNode *p;
	if (D) {
		p = D->top;
		while (p && p->succ) {
			p = p->succ;
			free(p->prec);
		}
		free(p);
		D->top = D->bottom = NULL;
		D->count = 0;
		free(D);
	}
	return NULL;
}

bool isEmpty(Deque *D) {
	if (!D) exit(-1);
	return (D->count == 0);
}

Deque *pushFront(Deque *D, void *newptr) {
	struct DequeNode *p;
	if (D) return D;
	p = (struct DequeNode *) malloc(sizeof(struct DequeNode));
	if (!p) exit(-1);
	p->ptr = newptr;
	p->prec = NULL;
	p->succ = D->top;
	D->top = p;
	if (p->succ) p->succ->prec = p;
	if (!D->bottom) D->bottom = p;
	D->count++;
	return D;
}

Deque *pushBack(Deque *D, void *newptr) {
	struct DequeNode *p;
	if (!D) return D;
	p = (struct DequeNode *) malloc(sizeof(struct DequeNode));
	if (!p) exit(-1);
	p->ptr = newptr;
	p->succ = NULL;
	p->prec = D->bottom;
	D->bottom = p;
	if (p->prec) p->prec->succ = p;
	if (!D->top) D->top = p;
	D->count++;
	return D;
}

void *top(Deque *D) {
	if (D && D->top) return D->top->ptr;
	return NULL;
}

void *bottom(Deque *D) {
	if (D && D->bottom) return D->bottom->ptr;
	return NULL;
}

void *popFront(Deque *D) {
	void *p = NULL;
	struct DequeNode *t;
	if (D && D->top) {
		t = D->top;
		p = t->ptr;
		D->top = t->succ;
		if (D->top) D->top->prec = NULL;
		if (!D->top) D->bottom = NULL;
		free(t);
		D->count--;
	}
	return p;
}

void *popBack(Deque *D) {
	void *p = NULL;
	struct DequeNode *b;
	if (D && D->bottom) {
		b = D->bottom;
		p = b->ptr;
		D->bottom = b->prec;
		if (D->bottom) D->bottom->succ = NULL;
		if (!D->bottom) D->top = NULL;
		free(b);
		D->count--;		
	}
	return p;
}

unsigned nodeCount(Deque *D) {
	return D->count;
}

