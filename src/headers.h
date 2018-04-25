#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct AVLnode {
	struct AVLnode *parent, *left, *right;
	char *key;
	int height;
} node;

node *Insert(node *, char *);

node *Search(node *, char *);

node *Delete(node *, char *);

char *Key(node *);

int Height(node *);

int Beta(node *);

node *Pred(node *);

bool SmallerThen(char *, char *);

bool EqualsTo(char *, char *);

node *TreeMax(node *);

int Max(int, int);

void Update(node *);

node *FixTree(node *);

node *RotateLeft(node *);

node *RotateRight(node *);

node *Balance(node *);

void Print(node *);

void Check(node *);

