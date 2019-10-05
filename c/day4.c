#define G_N_MAX	1<<12
#define GUARDS	1<<5
#define H_MAX	G_N_MAX
#define V_MAX	GUARDS
#include "day.h"
create_mnind(max, >, uint8_t, uint8_t);
#define maxnind(v,n)	maxnind_uint8_t(v,n)
typedef struct Guard {
	uint16_t total_sleep;
	uint8_t mins_asleep[60];
} Guard;
int main(void)
{
	Guard actual_guards[GUARDS], *guards[G_N_MAX]={NULL};
	Hash guard_ls = {0,{0},{0}};
	FILE *f = popen("sort input", "r");
	char word[8];
	uint8_t i, t, sleep_t = 0;
	uint16_t guard_n;

	while (EOF!=fscanf(f,"[%*d-%*d-%*d %*d:%hhu] %*s %s%*[ beginshft\n]",&t,word)){
		if ('#' == *word){
			guard_n = atoi(word+1);
			if (!guards[guard_n]) guards[guard_n] = actual_guards+(hash_push(guard_ls, guard_n));
		} else if ('a' == *word) sleep_t = t;
		else {
			guards[guard_n]->total_sleep += t-sleep_t;
			for (i = sleep_t; i < t; i++) guards[guard_n]->mins_asleep[i]++;
		}
	}

	for (i = 0; guard_ls.values[i]; i++) //looping over all guard numbers,
		if (guards[guard_ls.values[i]]->total_sleep > guards[guard_n]->total_sleep) //if current guard's total sleep is larger than the stored guard's total sleep,
			guard_n = guard_ls.values[i]; //set a new stored guard
	printf("%d\n", guard_n*maxnind(guards[guard_n]->mins_asleep, 60));

	uint8_t max_min[GUARDS] = {0}, max_min_v[GUARDS] = {0};
	for (i = 0; guard_ls.values[i]; i++)
		max_min_v[i] = guards[guard_ls.values[i]]->mins_asleep[max_min[i] = maxnind(guards[guard_ls.values[i]]->mins_asleep, 60)];
	guard_n = maxnind(max_min_v, i);
	printf("%d\n", guard_ls.values[guard_n]*max_min[guard_n]);
}
