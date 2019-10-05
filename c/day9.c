#include "day.h"
create_mnind(max, >, uint32_t, uint16_t);
#define maxnind(v,n)	maxnind_uint32_t(v,n)
#define move_index(dist)	if (dist < 0)	for (uint8_t i = 0; i < -dist; i++) current_index = current_index->back;\
				else		for (uint8_t i = 0; i < dist; i++) current_index = current_index->fwd
typedef struct Item Item;	//Item is a node in a doubly linked list
struct Item {
	Item *back;
	Item *fwd;
	uint32_t marble;
};
void insert(uint32_t marble);
uint16_t players;
uint32_t pop(void), place(uint32_t marble);
static Item circle = { &circle, &circle, 0 };	//starting marble of 0 begins the list
static Item *current_index = &circle;

void insert(uint32_t value)
{	//inserts marble at the current_index
	Item *new = malloc(sizeof(Item));
	new->marble = value;
	new->fwd = current_index;
	new->back = current_index->back;
	current_index = current_index->back = current_index->back->fwd = new; //RTL evaulation is important here.
}
uint32_t pop(void)
{	//remove item at the current_index
	uint32_t tmp = current_index->marble;
	current_index->back->fwd = current_index->fwd;
	current_index->fwd->back = current_index->back;
	free(current_index);
	current_index = current_index->fwd; //undef behaviour, but should shift the current_index to it's correct position
	return tmp;
}
void reset(void)
{
	for (Item *ind = circle.fwd; ind!=&circle; ind = ind->fwd, free(ind->back));
	current_index = circle.fwd = circle.back = &circle;
	circle.marble = 0;
}
void try(uint32_t maxmarb){
	uint32_t score[players], i = 0; //1<<31 < max < 1<<32
	memset(score, 0, players*sizeof(uint32_t));
	while (++i <= maxmarb)	//loop over all marbles
		if (i % 23){
			move_index(2);
			insert(i);
		} else {	//if i is divisible by 23
			move_index(-7);
			score[i%players] += i+pop();			//add to a player's score
		}
	printf("maximum: %u\n", score[maxnind(score, players)]);
	reset();
}
int main(void)
{
	FILE *f = fopen("input", "r");
	uint32_t marbles;
	fscanf(f, "%hu players; last marble is worth %u points", &players, &marbles);
	try(marbles);
	try(marbles*100);
}
