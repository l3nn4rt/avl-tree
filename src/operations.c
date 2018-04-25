#include "headers.h"

void SwapKeys(node *p0, node *p1) {
	char *t = p0->key;
	p0->key = p1->key;
	p1->key = t;
}

node *Search(node *r, char *s) {
	while (r && s && !EqualsTo(s, r->key))
		r = (SmallerThen(s, r->key) ? r->left : r->right);
	return r;
}

node *Insert(node *t, char *s) {
	node *p = (node *) malloc(sizeof(node));
	p->parent = p->left = p->right = NULL;
	p->key = strdup(s);
	p->height = 0;
	if(!t) return p;
	while(t) {
		p->parent = t;
		t = (SmallerThen(p->key, t->key) ? t->left : t->right);
	}
	t = p->parent;
	if (SmallerThen(p->key, t->key)) t->left = p;
	else t->right = p;
	return FixTree(t);
}

node *Remove(node *p) {
	node *q = p->parent;
	if (p->left && p->right) {
		q = Pred(p);
		// avoids a node removed here to change color when reprinted
		SwapKeys(p, q);
		//free(p->key);
		//p->key = strdup(q->key);
		return Remove(q);
	} else if (!p->left && !p->right) {
		if (q) {
			if (p == q->left) q->left = NULL;
			else q->right = NULL;
		}
	} else if (p->left) {
		if (!q) {
			q = p->left;
			q->parent = NULL;
		} else {
			if (p == q->left) q->left = p->left;
			else q->right = p->left;
			p->left->parent = q;
		}
	} else if (p->right) {
		if (!q) {
			q = p->right;
			q->parent = NULL;
		} else {
			if (p == q->left) q->left = p->right;
			else q->right = p->right;
			p->right->parent = q;
		}
	}
	free(p->key);
	free(p);
	return FixTree(q);
}

node *Delete(node *t, char *s) {
	node *p = Search(t, s);
	if (!p) return t;
	return Remove(p);
}

