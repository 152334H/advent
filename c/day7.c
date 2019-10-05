#include "day.h"
#define rm_dep_p1(k)	((indn_c(order, k, order_c) == order_c)?(order[order_c++]=k):0)
#define passtime()	do { t++;\
			for (uint8_t _i = 0; _i < 5; _i++)\
				if (workers[_i].step){\
					if (workers[_i].time) workers[_i].time--;\
					else {\
						order[order_c++] = workers[_i].step;\
						workers[_i].step = 0;\
					}\
				}\
			} while (0);
typedef struct Worker {
	char step;
	char time;
} Worker;
Worker workers[5]={{0,0}};
uint16_t t = 0;
uint8_t indn_c(char*, char, uint8_t);
create_indn(c, char);
_Bool p2_rm_dep(char k, char *order, uint8_t order_c)
{
	for (uint8_t i = 0; i < 5 && workers[i++].step;) if (i == 5) return 1;
	if ((indn_c(order, k, order_c) == order_c) && (indn_c((char*)workers, k, 10) == 10))
		for (uint8_t i = 0; i < 5; i++)
			if (!workers[i].step){
				workers[i].time = 59+((workers[i].step = k)^64);
				break;
			}
	return 0;
}
void try(_Bool part2)
{	//compact function for both parts
	FILE *f = fopen("input", "r");
	char dep[128][32] = {0}, order[32] = {0}, order_c = 0, k, v, undone_c = 26; //dep[C] tracks step C's dependencies, order[] tracks the order of steps, k&v are scanf and index variables, undone_c counts the steps remaining
	while (EOF != fscanf(f, "Step %c must be finished before step %c can begin.\n", &v, &k)) dep[k][dep[k][31]++] = v; //dep[x][31] == len(dep[x])
	while (undone_c) {
		if (part2) passtime();
		for (undone_c = 0, k = 'A'; k <= 'Z'; k++) //looping through the steps,
			for (uint8_t i = 0; i < dep[k][31]; i++, undone_c++){
				uint8_t ind = indn_c(order, dep[k][i], order_c);	//check if any step is executed
				if (ind != order_c) for (v = i, dep[k][31]--; v < dep[k][31]; v++) dep[k][v] = dep[k][v+1];
			}
		for (k = 'A'; k <= 'Z'; k++) if (!dep[k][31]) if (part2?p2_rm_dep(k, order, order_c):rm_dep_p1(k)) break;	//remove steps with no deps
	}
	if (part2) for (uint8_t i = 0; i < 5 || !printf("%d\n", t+sum((uint8_t*)workers, 5)); i++) workers[i].step = 0;	//print result
	else puts(order);
	fclose(f);
}
int main(void)
{
	try(0);
	try(1);
}
