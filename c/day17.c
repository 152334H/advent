#include "day.h"
#define YMAX	1<<11
#define XMAX	1<<10
#define x(c)	(c&0xFFFF)
#define y(c)	(c>>16)
#define c(x,y)	(((uint32_t)y<<16)+x)
//void pop(tuple, &y, &x)
#define pop(c,a,b)	do {	uint32_t c_tmp = c;\
				a = y(c_tmp);\
				b = x(c_tmp);\
			} while (0)
static uint8_t tp_len = 0;
static char grid[YMAX][XMAX] = {[0 ... (YMAX)-1] = { [0 ... (XMAX)-1] = '.'}}; //GCC only
static uint32_t tp_list[1<<8];
void print_local(uint16_t cur_x, uint16_t h)
{	//testing function, isn't used
	char ln[72] = "\t"; ln[71] = '\0';
	for (uint16_t dx = cur_x-35, i = 1; dx <= cur_x+35 || !puts(ln); dx++) ln[i++] = (dx%10)+'0';
	for (uint16_t dy = h-2; dy <= h+2; dy++) printf("\t%.70s\n", &grid[dy][cur_x-35]);
}
uint32_t x_bound(uint16_t x, uint16_t y)
{	//returns the position of the liquid x-travel boundaries
	uint16_t min = x, max = x;
	while (grid[y][max+1] != '#' && (strchr("#~", grid[y+1][max]))) max++;
	while (grid[y][min-1] != '#' && (strchr("#~", grid[y+1][min]))) min--;
	return c(max,min);
}
void fill_water(uint16_t x, uint16_t y)
{	//fills up the current y with as much water as possible, starting from x
	uint16_t min, max;
	pop(x_bound(x,y), min, max);
	if (strchr("#~", grid[y+1][max]) && strchr("#~", grid[y+1][min])) memset(&grid[y][min], '~', max-min+1); //fill with ~ if flat
	else 	for (uint16_t dx = min; dx <= max; grid[y][dx++] = '|') if (grid[y+1][dx] == '.') tp_list[tp_len++] = c(dx,y); //fill with |, and also add a return point if necessary
}
int main(void)
{
	FILE *f = fopen("input", "r");
	uint16_t maxy = 0, miny = 99;
	char c;
	for (uint16_t x, X, y, Y, tmp, tmp_start, tmp_end; EOF != fscanf(f, "%c=%hu, %*c=%hu..%hu\n", &c, &tmp, &tmp_start, &tmp_end);){
		if (c&1){	//if it is Y
			x = tmp_start, X = tmp_end;
			y = Y = tmp;
		} else {
			x = X = tmp;
			y = tmp_start, Y = tmp_end;
		}
		for (uint16_t dy = y; dy <= Y; dy++) memset(&grid[dy][x], '#', X-x+1);
		maxy = max(Y, maxy), miny = min(y, miny);
	}
	for (uint16_t h = 0, cur_x = 500;;){	//loop to fill the entire water flow
		//print_local(cur_x, h);	//prints a localised map of the current water stream
		if (h > maxy && tp_len) pop(tp_list[--tp_len], h, cur_x);	//exit maximum depth
		if (strchr("|.", grid[h+1][cur_x])) grid[h++][cur_x] = '|';	//flow down if needed
		else if (grid[h][cur_x] == '~') h--;				//go back up if needed
		else if (grid[h][cur_x+1] == '|' || grid[h][cur_x-1] == '|'){	//if the surrounding water is flowing
			fill_water(cur_x,h);	//fill water (note: unoptimised due to creation of excess tp points)
			if (!tp_len) break;	//the lack of optimizatin allows this to work
			if (grid[h][cur_x] != '~') pop(tp_list[--tp_len], h, cur_x);	//if the water is supposed to flow
		} else fill_water(cur_x,h);	//fill if nothing else
	}
	for (uint16_t dy = miny, wc = 0, lc = 0; dy <= maxy || !printf("%d\n%d\n", wc, wc+lc); dy++)
		for (uint16_t dx = 0; dx < XMAX; dx++){
			if (grid[dy][dx] == '~') wc++;
			if (grid[dy][dx] == '|') lc++;
		}
}
