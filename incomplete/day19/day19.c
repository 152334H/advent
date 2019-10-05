#include <stdio.h>
#include <stdlib.h>
#include "day.h"
void main(int argc, char**argv)
{
	if (argc != 2) errex("Execute this program using the .sh", 1);
	unsigned long long regist[] = {0,0,0,atoi(argv[1]),0,0}; 
	for (regist[4] = 1; regist[4] <= regist[3] || !printf("%llu\n", regist[0]); regist[4]++)
		if (regist[3]%regist[4] == 0) regist[0]+=regist[4];
}
