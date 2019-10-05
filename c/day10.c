#include <math.h>
#include <stdio.h>
#include <stdint.h>

#define vect(x,y)	y+((uint16_t)(x)<<8)
#define coord(x,y)	(uint32_t)y+((uint64_t)(x)<<32)
#define x(c)	(int32_t)((c&0xFFFFFFFF00000000)>>32)
#define y(c)	(int32_t)(c&0xFFFFFFFF)
#define dx(c)	(int8_t)((c&0xFF00)>>8)
#define dy(c)	(int8_t)(c&0xFF)
#define move(n) for (uint16_t k = 0; k < i; k++) coords[k] = coord(x(coords[k])+n*dx(velocity[k]), y(coords[k])+n*dy(velocity[k]))
uint16_t velocity[1<<9];
uint64_t coords[1<<9];
void print_stars(uint64_t coords[], uint16_t i, int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax)
{
	for (int32_t y = ymin; y <= ymax; y++, putchar('\n'))
		for (int32_t x = xmin; x <= xmax; x++){
			uint64_t c = coord(x,y);
			for (uint16_t k = 0; k < i && !((c == coords[k]) && putchar(c = '#')); k++);
			if (c != '#') putchar('.');
		}
}
int main(void)
{
	FILE *f = fopen("input", "r");
	uint32_t x, y, ydiff = 1<<30;
	uint16_t i = 0, t = 0;
	uint8_t dx, dy;
	while (EOF != fscanf(f, "position=<%d, %d> velocity=<%hhd, %hhd>\n", &x, &y, &dx, &dy)){
		coords[i] = coord(x,y);
		velocity[i++] = vect(dx,dy);
	}
	int32_t ymax, ymin, cy, xmax = -999, xmin = 999, cx = 0;
	while (1){ //approximate and approach the convergence point
		ymax = -999, ymin = 999;
		for (uint16_t k = 0; k < i; k++){
			cy = y(coords[k]);
			if (cy < ymin) ymin = cy;
			if (cy > ymax) ymax = cy;
		}
		if (ymax-ymin >= ydiff) break;
		ydiff = ymax-ymin;
		t += (cy = powf(10, (uint8_t)log10f(ydiff) -1));//do fast approximation using powers of 10
		move(cy);
	}
	for (uint16_t k = 0; k < i; k++){
		cx = x(coords[k]);
		if (cx < xmin) xmin = cx;
		if (cx > xmax) xmax = cx;
		cy = y(coords[k]);
		if (cy < ymin) ymin = cy;
		if (cy > ymax) ymax = cy;
	}
	print_stars(coords, i, xmin,xmax,ymin,ymax);
	printf("%d\n", t);
}
