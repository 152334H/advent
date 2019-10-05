#define H_MAX 1<<17
#define V_MAX H_MAX
#define REQUIRES_HASH
#include "day.h"
#undef REQUIRES_HASH
#define M 1<<10
int main(void)
{
	FILE* f = fopen("input", "r");
	char line[8];	//holds the current line in input file
	int freq = 0, list[M], i;	//freq is the current frequency, list holds the input, i is the line count
	Hash set[2];	//+ and - sets (the Hash is implemented using array indexing, so negative values are disastrous)

	while (fgets(line, 9, f)){ //!=NULL
		safe_hash_push(&set[freq < 0], abs(freq)); //add current freq to set
		freq += (list[i++] = atoi(line));	//add value to freq
	}
	printf("total: %d\n", freq);

	while (1){
		for (unsigned k = 0;freq += list[k++], k < i;) //continuously loop through values
			if (!safe_hash_push(&set[freq < 0], abs(freq)))	//when a duplicate is found
				return !printf("failed to push %d\n", freq); //return 0 on success
	}
}
