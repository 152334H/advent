#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(){
	FILE *f = fopen("input", "r");
	char fabric[1000][1000] = {0};
	uint16_t ID, x, y, X, Y, dx, dy;
	uint32_t conflict=0;
	while (EOF != fscanf(f,"#%hu @ %hu,%hu: %hux%hu\n",&ID,&x,&y,&dx,&dy))	//looping through input,
		for (X = x; X < x+dx; X++) for (Y = y; Y < y+dy; Y++) if (fabric[X][Y]++ == 1) conflict++;//count sq ft
	printf("conflicting: %d\n", conflict);
	fseek(f,0,SEEK_SET);	//reread the file
	for (_Bool ans = 1; EOF != fscanf(f,"#%hu @ %hu,%hu: %hux%hu\n",&ID,&x,&y,&dx,&dy); ans = ans?printf("p2: %u\n",ID):1)
		for (X=x; X<x+dx; X++) for (Y=y; Y<y+dy; Y++) if (fabric[X][Y] != 1) ans = 0;	//prints ID when clear isn't set
}
