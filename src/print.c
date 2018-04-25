#include "headers.h"
#include "deque.h"

/* Box-Drawing Chars */
#define RB "\e(0\x6a\e(B" // Right Bottom corner
#define RT "\e(0\x6b\e(B" // Right Top corner
#define LB "\e(0\x6d\e(B" // Left Bottom corner
#define LT "\e(0\x6c\e(B" // Left Top corner
#define BC "\e(0\x76\e(B" // Bottom Cross
#define HL "\e(0\x71\e(B" // Horizontal Line

int Hash(void *A) {
	long a = ((long)A * 17) % 547 + 1453, b = ((long)A * 107) % 439 + 361, x;
	int codes[] = {	30,	31,	32,	33,	34,	35,	36,	37,	//  [0:7] dark
			97,	96,	95,	94,	93,	92,	91,	90 };	// [8:15] light
	x = (a * a + b / 71) % 14 + 1;
	return codes[x];
}

/* Returns the necessary tree width that allows all the nodes not to be truncated. */
int Necessary(node *p, int h) {
	int local, sl, left, right, below;
	
	if (!p) return 0;
	left = Necessary(p->left, h - 1);
	right = Necessary(p->right, h - 1);
	below = (left > right ? left : right);
	local = 0; sl = strlen(p->key);
	while (sl > (1 << (local + h)) - 1) local++;
	return (local > below ? local : below);
}

void Print(node *T) {
	int i, h = Height(T), j, levelNodes = 1;
	int sizeBDC = sizeof(HL), span, width = Necessary(T, h), sons = 0;
	int keyLen, lSpan, rSpan;
	char *edgeStr, *spaceStr;
	Deque *printDeque = pushBack(createDeque(), T);
	node *np;
	
	for (i = 0; i < h + 1; i++) {
		// expresses the distance among elements in function of the level
		span = (1 << (h - i + width - 1)) - 1;
		// creates a string for the edges with box-drawing chars
		edgeStr = (char *) malloc(span * sizeBDC + sizeof(char)); // (*)
		edgeStr[0] = edgeStr[sizeBDC * span] = '\0';
		for (j = 0; j < span; j++) strcat(edgeStr, HL);
		// and one for absent edges and nodes with empty spaces
		spaceStr = (char *) malloc ((span + 1) * sizeof(char)); // (**)
		for (j = 0; j < span; j++) spaceStr[j] = ' ';
		spaceStr[span] = '\0';
		/***** EDGE SECTION BEGIN *****/
		for (j = 0; i != 0 && j < levelNodes; j++) {
			np = popFront(printDeque);
			// each bit represents precence/absence a specific brother
			if (np) sons += 1 << (j % 2);
			if (j % 2 == 0) {
				// left edge
				if (np) printf("%s%s%s", spaceStr, LT, edgeStr);
				else printf("%s %s", spaceStr, spaceStr);
			} else {
				if (sons == 0) printf(" ");
				if (sons == 1) printf(RB);
				if (sons == 2) printf(LB);
				if (sons == 3) printf(BC);
				sons = 0;
				// right edge
				if (np) printf("%s%s%s", edgeStr, RT, spaceStr);
				else printf("%s %s", spaceStr, spaceStr);
				printf(" ");
			}
			pushBack(printDeque, np);
		}
		if (i != 0) printf("\n");
		/***** EDGE SECTION END ********** NODE SECTION BEGIN *****/
		for (j = 0; j < levelNodes; j++) {
			np = popFront(printDeque);
			if (np) {
				keyLen = strlen(np->key);
				lSpan = span - keyLen / 2;
				rSpan = span + keyLen / 2 - keyLen + 1;
				printf(	"%*s" "\x1b[%dm" "%s" "\x1b[%dm" "%*s", 
					lSpan,"", Hash(np->key), np->key, 0, rSpan,"");
			} else {
				printf("%s %s", spaceStr, spaceStr);
			}
			printf(" ");
			if (np) {
				pushBack(printDeque, np->left);
				pushBack(printDeque, np->right);
			} else {
				pushBack(printDeque, NULL);
				pushBack(printDeque, NULL);
			}
		}
		printf("\n");
		/***** NODE SECTION END *****/
		free(edgeStr); // (*)
		free(spaceStr); // (**)
		levelNodes *= 2;
	}
}

