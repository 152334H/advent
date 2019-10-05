#include <stdio.h>
#include <stdint.h>

//defines are only to make main() less recondite
#define getsum(x1,y1,o)	summed[x1][y1]+summed[x1-o][y1-o]-summed[x1-o][y1]-summed[x1][y1-o]
#define sum(x1,y1)	pwr(x1,y1) +summed[x1-1][y1] +summed[x1][y1-1] -summed[x1-1][y1-1]
static uint16_t INPUT;
int16_t pwr(uint16_t x, uint16_t y)
{	//setting ID to x+10 requires less operations than a #define directive
	uint16_t ID = x+10;
	return (ID*y+INPUT)*ID/100%10-5;
}
int main(void){
	FILE *f = fopen("input", "r");
	int32_t max = 0, psum = 0, summed[301][301] = {0}, X, Y, S; //summed-area table
	fscanf(f, "%hu\n", &INPUT);

	for (uint16_t x = 1; x < 301; x++) for (uint16_t y = 1; y < 301; y++) summed[x][y] = sum(x,y); //compute summed[][]
	for (uint16_t x = 4; x < 298; x++) for (uint16_t y = 4; y < 301; y++)
			if ((psum = getsum(x,y,3)) > max) X = x-2, Y = y-2, max = psum; //find the highest 3x3 sum
	printf("part 1: '%d,%d'\n", X, Y);
	for (uint16_t s = 4; s < 301; s++) for (uint16_t y = s+1; y < 301; y++) for (uint16_t x = s+1; x < 301; x++)
				if ((psum = getsum(x,y,s)) > max) X = x-s+1, Y = y-s+1, S = s, max = psum; //find the highest sum
	printf("part 2: '%d,%d,%d'\n", X, Y, S);
}
