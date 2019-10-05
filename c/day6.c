#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define x(c)	(c>>10)
#define y(c)	(c&((1<<10)-1))
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
#define coord(x,y)	(x<<10)+y	//coordinate is stored as a 20+ bit number
int main(void)
{
	uint8_t i = 0, xmin = 255, ymin = 255;
	int16_t grid[400][400] = {0};
	uint16_t area=0, x, y, xmax = 0, ymax = 0;
	uint32_t coords[1<<6] = {0};
	FILE *f = fopen("input", "r");
	while (EOF != fscanf(f, "%hu, %hu\n",&x,&y)){ //go through input
		xmax = max(x,xmax);	//boundaries here are used for for loops
		ymax = max(y,ymax);
		xmin = min(x,xmin);
		ymin = min(y,ymin);
		coords[i++] = coord(x,y);	//add to coordinate list
	}
	for (x = xmin; x <= xmax; x++) for (y = ymin; y <= ymax; y++){
		uint32_t dist = 0, sc;
		uint16_t dmin = 1<<14, dd;
		_Bool skip = 0;
		for (uint8_t k = 0; k < i; k++){
			dist += dd = abs(x(coords[k])-x) + abs(y(coords[k])-y);	//get and add manhatten dist
			if (dd < dmin) {	//when new minimum is found
				dmin = dd;	
				sc = coords[k];	//store the coordinate
				skip = 0;
			} else if (dd == dmin) skip = 1;
		}
		if (!skip) grid[x(sc)][y(sc)]+=(x == xmin || x == xmax || y == ymin || y == ymax)?-99:1; //if not infinite
		if (dist < 10000) area++;	//for part 2
	}
	uint16_t max = 0;
	for (uint8_t k = 0; k < i; k++) if (max < grid[x(coords[k])][y(coords[k])]) max = grid[x(coords[k])][y(coords[k])];
	printf("%d\n%d\n", max, area);
	fclose(f);
}
