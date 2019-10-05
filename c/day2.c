#define LINELEN 26
#include "day.h"
#define LINEMAX 1<<8
#define CHARMAX 1<<13
uint8_t strdiff(char s[], char t[])
{	//returns number of different chars
	uint8_t i = 0;
	if (!*s || !*t) return 0;
	do if (*s++ != *t++) i++;
	while (*s && *t);
	return i;
}
char *str_and(char s[], char t[])
{	//s = s && t
	char *tmp = s;
	uint8_t index = 0, len = strlen(s);
	for (uint8_t i = 0; i < len; i++,s++,t++) if (*s == *t) tmp[index++] = *t;
	tmp[index] = '\0';
	return tmp;
}
int main(){
	FILE *f = fopen("input","r");
	char *lines[LINEMAX], buf[CHARMAX];
	uint8_t two = 0, three = 0, i = readlns(f, lines, buf, 0);
	for (uint8_t k = 0; k < i; k++){//for all lines
		uint8_t d[1<<7] = {0};	//init. list of character counts; a pseudo-dict
		for (char *p = lines[k]; *p;) d[*p++]++;	//count the number of characters in the line
		for (char c = 'a'; c <= 'z'; c++) if (d[c] == 2 || d[c] == 3) d[d[c]]=1; //check for 2/3 character count
		if (d[2]) two++;	//add accordingly if necessary
		if (d[3]) three++;
	}
	printf("%d*%d == %d\n", two, three, two*three);	//show part 1 ans
	for (char **p = lines; i--; p++)	//looping through the lines
		for (uint8_t k = 1; k <= i; k++)	//looping through the lines below
			if (strdiff(p[0], p[k]) == 1)	//if there is only a diff of 1 char
				return puts(str_and(p[0],p[k])); //show part 2 ans
}
