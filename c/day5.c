#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define CDIFF	'a'-'A'
#define BITMAGIC 32 //Cuts program time in half, instead of comparing the units with CDIFF
#define react(s) do{ for (x = k = 0; x+k < max; x++){\
			if ((s[x+k]^s[x+1+k]) == BITMAGIC) k++;\
			else s[x-k] = s[x+k];\
		}\
		s[max = x-k] = '\0';\
	} while (k)
char *strcpy_rmchar(char d[], char s[], char c)
{	//copy string s[] to d, ignoring all instances of char c.
	*d = *s;
	do if (*s == c || *s == c+CDIFF) d--;
	while ((*++d = *++s));
	return d;
}
int main(){
	char input[50002], buf[50002];	//input takes the contents of the given input; buf serves as a copy
	uint32_t x, k, len, in = open("input", O_RDONLY), input_size = read(in, input, sizeof(input)), max = input_size;
	//x is both a string index and a misc. integer value. k is an offset for a string index. len is used to hold the puzzle answers. in is the file descriptor of the input file. input_size is the initial filesize of the input file. max is the diminishing size of the polymer. 
	close(in);
	*strchr(input, '\n') = '\0'; 	//remove trailing newline
	react(input);			//"calls" the macro for the reaction of the polymer
	printf("length after reacting: %d\n", len = strlen(input)); //print part 1 ans
	for (char c = 'A'; c <= 'Z'; c++){				//for each unit type,
		max = input_size-(strcpy_rmchar(buf, input, c)-buf);	//remove the units
		react(buf);						//and test the reaction,
		if ((x = strlen(buf)) < len) len = x;			//checking if it's the smallest
	}
	printf("with a char removed, the minimum unit number is %d\n", len);
}
