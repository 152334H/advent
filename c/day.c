#include "day.h"
#define CUL_RED		"\x1b[31m"
#define	CUL_RESET	"\x1b[0m"
void errpt(char s[]){ printf(CUL_RED "err: %s\n" CUL_RESET, s);}
void errex(char s[], int exit_code){ errpt(s); exit(exit_code);}
uint8_t strchrc(char *s, char c)
{	//counts occurance of char c in string s
	uint8_t i;
	for (i = 0; *s && (*s++ != c || ++i););
	return i;
}
uint16_t sum(uint8_t *list, uint8_t count)	//helper function to add up integers in a list
{
	uint16_t total = 0;
	for (uint8_t i = 0; i < count; i++) total += *list++;
	return total;
}
uint16_t readnlns(FILE *f, char *lines[], char *buf, _Bool newline, uint16_t n) //newline decides whether to keep the '\n'
{	//returns lines read
	char *tmp;
	uint16_t i = 0;
	while ((tmp=fgets(buf, n+1, f)) != NULL){
		lines[i++] = tmp;
		buf += strlen(buf); //points to the '\0' now
		if (newline){
			if (*(buf-1) != '\n'){
				*buf++ = '\n';
				*buf='\0';
			}
		} else {
			if (*(buf-1) == '\n') *--buf = '\0';
		}
		buf++;
	}
	return i;
}
