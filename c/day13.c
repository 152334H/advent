#define LINEMAX 150
#define LINELEN 150
#include "day.h"

#define CHARMAX 1<<15
#define TURNCHR "\\/+"
#define CARTCHR "^<v>"
//giving names to confusing methods
#define coords(cart)		cart->x, cart->y
#define coords_eq(c1, c2)	c1->x == c2->x && c1->y == c2->y /* check if the coordinates of two carts are equal */
#define below(cart)		track[cart->y][cart->x]		/* get the track type below a cart */
#define is_leftright(dir)	(dir < 1<<6) /*'<' and '>' are less than 64, '^' and 'v' are lower */
#define is_change_dir(c)	below(c) != (is_leftright(cart->dir) ?'-':'|') /*checks if the track below a cart indicates a change in direction*/
#define should_increment(dir)	dir % 7 == 6 /* check whether a cart is increasing in axis*/
#define dir_index(dir)		strchr(CARTCHR, dir)-CARTCHR+1 /* indexes a char direction in the string CARTCHR */

typedef struct Cart {
	uint16_t x;
	uint16_t y;
	char dir;
	uint8_t turns;
} Cart;
Cart *cart_ls[17];
char *lines[LINEMAX], track[LINEMAX][LINEMAX+1];
uint8_t cart_c = 0, cart_max;
uint16_t tick  = 0;

char find_track(uint16_t x, uint16_t y)
{
	_Bool up, left, down, right;
	up    =	y	&& strchr("|" TURNCHR, lines[y-1][x]);
	down  =	y < 150 && strchr("|" TURNCHR, lines[y+1][x]);
	left  =	x	&& strchr("-" TURNCHR, lines[y][x-1]);
	right =	x < 150	&& strchr("-" TURNCHR, lines[y][x+1]);
	if (up && down && left && right)	return '+';
	if (up && down)				return '|';
	if (left && right)			return '-';
	if ((left && up) || (down && right))	return '/';
						return '\\';
}
uint8_t move_cart(Cart *cart)
{
	uint16_t *p = is_leftright(cart->dir)?&cart->x:&cart->y;
	should_increment(cart->dir) ?(*p)++:(*p)--;
	for (uint8_t c = 0; c < cart_c; c++)
	       	if (cart_ls[c] != cart && coords_eq(cart_ls[c], cart)){ //check all remaining carts for collisions
			if (cart_c == cart_max) printf("first collision at (%d,%d), tick %d\n", coords(cart), tick);
			free(cart_ls[c]);
			free(cart);
			uint8_t ind;
			for (uint8_t m = 0, n = 0; m < cart_c; m++)
				if (cart_ls[m] == cart) ind = m;
				else if (m != c) cart_ls[n++] = cart_ls[m];
			cart_c -= 2;
			return (c > ind) ? 1 : 2;
		}
	if (is_change_dir(cart)){
		int8_t shift = -1;
		if (below(cart) == '+'){ //if cart at intersection
			if (++cart->turns & 1) shift += cart->turns; //shift direction if not going straight
			cart->turns %= 3;	//lower turns to existing directions
		} else	shift = ((below(cart) == '/' && !is_leftright(cart->dir))\
				||(below(cart) == '\\' && is_leftright(cart->dir)?2:0));
		cart->dir = CARTCHR[(dir_index(cart->dir)+shift)%4];
	}
	return 0;
}
int compare(const void **p1, const void **p2)
{
	Cart *c1 = (Cart*)*p1;
	Cart *c2 = (Cart*)*p2;
	if (c1->y == c2->y) return c1->x-c2->x;
	/*else*/return c1->y-c2->y;
}
int main(void){
	FILE *in = fopen("input", "r");
	char buf[CHARMAX];
	uint16_t i = readlns(in, lines, buf, 1);
	for (uint16_t y = 0; y < i; track[y++][LINEMAX] = '\0')
		for (uint16_t x = 0; x < LINEMAX; x++)
			if (strchr(CARTCHR, lines[y][x])){ //parse input lines (note that strchr indexes '\0's as well)
				track[y][x] = find_track(x,y);
				cart_ls[cart_c]		= malloc(sizeof(Cart));
				cart_ls[cart_c]->dir	= lines[y][x];
				cart_ls[cart_c]->x	= x;
				cart_ls[cart_c++]->y	= y;
			} else track[y][x] = lines[y][x];
	cart_max = cart_c;
	do {
		for (uint8_t c = 0; c < cart_c; c++) c -= move_cart(cart_ls[c]); //push back index if collision occured
		qsort(cart_ls, cart_c, sizeof(Cart*), (int(*)(const void *, const void *))compare); //ensures LTR-UTD order
	} while (cart_c > 2 && ++tick);
	printf("Last cart standing: (%d,%d) at tick %d\n", coords(cart_ls[0]), tick);
}
