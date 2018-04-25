#include "headers.h"

int main(int argn, char *args[]) {
	node *T = NULL;
	int i = 1, j, h;
	char *demo[] = {"69",	"5",	"25",	"125",	"don't","panic","42",	"-2",
			"tree",	"1",	"2",	"3",	"4",	"5",	"6",	"7",
			"8",	"9",	"10",	"12",	"90",	";)"};
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (argn == 1) {
		i = 0;
		args = demo;
		argn = 22;
	}
	for (; i < argn; i++) {
		h = 2 * Height(T) + 2;
		printf("\033[%dA\n", h);
		for (j = 0; j < h; j++) printf("%*s\n", w.ws_col, "");
		printf("\033[%dA\n", h + 1);
		
		T = Insert(T, args[i]);
		Print(T);
		usleep(200000);
	}
	printf("Press Enter to delete: "); getchar();
	printf("\033[2A\n");
	while (T) {
		h = 2 * Height(T) + 2;
		printf("\033[%dA\n", h);
		for (j = 0; j < h; j++) printf("%*s\n", w.ws_col, "");
		printf("\033[%dA\n", h + 1);
		
		T = Delete(T, args[--i]);
		Print(T);
		usleep(200000);
	}
}

