#define LINEMAX 1<<6
#define LINELEN 1<<6
#define CHARMAX 1<<12
#include "day.h"
char *around(char *grid[], uint8_t x, uint8_t y)
{	//returns the values of the coordinates forming the 3x3 square around (x,y)
	char *ls = malloc(9);
	for (uint8_t i = 0, dy = (y?y-1:0); (dy <= y+1 && dy < 50) || (ls[i] = '\0'); dy++)
		for (uint8_t dx = (x?x-1:0); dx <= x+1 && dx < 50; dx++)
			if (dy != y || dx != x) ls[i++] = grid[dy][dx];
	return ls;
}
int main(void)
{
	FILE *f = fopen("input", "r");
	char *lines[LINEMAX], buf[CHARMAX], *copy[LINEMAX], bufcopy[CHARMAX];
	uint32_t values[1<<10];
	uint16_t i = readlns(f, lines, buf, 0), v = 0;
	for (uint8_t k = 0; k < i; k++)	copy[k] = lines[k]-*lines+bufcopy;
	for (uint16_t m = 0; m < 999; m++){
		memcpy(bufcopy, buf, CHARMAX);
		for (uint8_t cy = 0; cy < i; cy++) for (uint8_t cx = 0; cx < i; cx++){
				char *adj = around(copy, cx, cy);
				switch (copy[cy][cx]) {
					case '.':	if (strchrc(adj, '|') >= 3) lines[cy][cx] = '|';
							break;
					case '|':	if (strchrc(adj, '#') >= 3) lines[cy][cx] = '#';
							break;
					case '#':	if (!strchr(adj, '#') || !strchr(adj, '|')) lines[cy][cx] = '.';
				}
		}
		for (uint16_t k = 0, lumb_c = 0, tree_c = 0; k < i || ((values[v++] = lumb_c*tree_c) && 0); k++)
			lumb_c += strchrc(copy[k], '#'), tree_c += strchrc(copy[k], '|');
		if (m && !(m%28) && values[m] == values[m-28]){
			printf("part 1: %u\npart 2: %u\n", values[10], values[1000000000%28 +m-28]);
			printf("%u\n", m);
			break;
		}
	}
}
