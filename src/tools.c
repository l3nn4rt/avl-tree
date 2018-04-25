#include "headers.h"

int Max(int a, int b) { return (a > b ? a : b); }

char *Key(node *p) { return (p ? p->key : strdup("-")); }

int Height(node *p) { return (p ? p->height : -1); }

int Beta(node *p) { return Height(p->left) - Height(p->right); }

bool SmallerThen(char *s0, char *s1) { return atoi(s0) < atoi(s1); }

bool EqualsTo(char *s0, char *s1) { return !strcmp(s0, s1); }

node *TreeMax(node *p) {
	while (p && p->right) p = p->right;
	return p;
}

node *Pred(node *p) {
	if (p && p->left) return TreeMax(p->left);
	while (p && p->parent && p == p->parent->left) p = p->parent;
	return p->parent;
}

void Update(node *p) {
	int l, r;
	if (!p) return;
	l = Height(p->left);
	r = Height(p->right);
	p->height = 1 + Max(l, r);
}

node *RotateLeft(node *p) {
	node *q;
	if (!p || !p->right) exit(1);
	q = p->right;
	q->parent = p->parent;
	if (q->parent) {
		if (p == q->parent->left) q->parent->left = q;
		else q->parent->right = q;
	}
	p->parent = q;
	p->right = q->left;
	if (p->right) p->right->parent = p;
	q->left = p;
	Update(p);
	Update(q);
	return q;
}

node *RotateRight(node *p) {
	node *q;
	if (!p || !p->left) exit(1);
	q = p->left;
	q->parent = p->parent;
	if (q->parent) {
		if (p == q->parent->left) q->parent->left = q;
		else q->parent->right = q;
	}
	p->parent = q;
	p->left = q->right;
	if (p->left) p->left->parent = p;
	q->right = p;
	Update(p);
	Update(q);
	return q;
}

node *Balance(node *p) {
	if (Beta(p) > 1) {
		if (Beta(p->left) < 0) RotateLeft(p->left);
		p = RotateRight(p);
	} else if (Beta(p) < -1) {
		if (Beta(p->right) > 0) RotateRight(p->right);
		p = RotateLeft(p);
	}
	return p;
}

node *FixTree(node *t) {
	node *p = t;
	while (t) {
		Update(t);
		p = t = Balance(t);
		t = t->parent;
	}
	return p;
}

int CheckRic(node *p) {
	int count = 0;
	if (!p) return count;
	count += CheckRic(p->left);
	printf(	"key:%4s\theight:%4d\tbeta:%4d\tparent:%4s\tleft:%4s\tright:%4s\n",
		Key(p), Height(p), Beta(p), Key(p->parent), Key(p->left), Key(p->right));
	count += CheckRic(p->right);
	return count + 1;
}

void Check(node *p) {
	int count = CheckRic(p);
	printf("node count: %d\n", count);
}

