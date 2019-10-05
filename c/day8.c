#include "day.h"
#define MAXINTS 1<<14
typedef struct Tup {
	struct Tup **children;
	uint8_t childc;
	uint8_t *data;
	uint8_t datac;
} Tup;
Tup *parse(Tup *given) //returns a tuple repesenting the entire tree
{
	Tup *node = malloc(sizeof(Tup));
	node->childc	= *given->data++;
	node->datac	= *given->data++;
       	node->children 	= malloc(node->childc*sizeof(Tup));
       	node->data	= malloc(node->datac);
	for (uint8_t i = 0; i < node->childc; i++)	node->children[i] = parse(given);	//recursively set children
	for (uint8_t k = 0; k < node->datac; k++)	node->data[k] = *given->data++;		//store metadata to node
	return node;
}
uint16_t checksum(Tup *node)	//checksum of a node: answer for part 1
{
	uint16_t total = 0;
	for (uint8_t i = 0; i < node->childc; i++) total += checksum(node->children[i]);
	return total+sum(node->data, node->datac);
}
uint16_t value(Tup *node)	//value function of a node; used for part 2
{
	if (node->childc){ //if there are children
		uint16_t total = 0;
		for (uint8_t i = 0; i < node->datac; i++) if (node->data[i] <= node->childc)
				total += value(node->children[node->data[i]-1]);
		return total; //get their total value
	}
	return sum(node->data, node->datac);
}
int main(){ //declarations
	uint8_t numbers[MAXINTS];
	FILE *f = fopen("input", "r");
	for (uint8_t *p = numbers; EOF!=fscanf(f, "%hhu", p++);); //getting input integers
	Tup root = { NULL, 0, numbers, 0}; //note that the "root" Tuple isn't a real representation of the root node.
	Tup *parsed = parse(&root); //parsing the integers to workable structs
	printf("cksum: %d\n", checksum(parsed));
	printf("value: %d\n", value(parsed));
}
