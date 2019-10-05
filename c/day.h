#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#pragma once
void errpt(char error[]);
void errex(char error[], int exit_code);
uint8_t strchrc(char*, char);
uint16_t sum(uint8_t *list, uint8_t count);	//helper function to add up integers in a list
uint16_t readnlns(FILE *f, char *lines[], char *buf, _Bool newline, uint16_t n);
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
#ifdef LINELEN
#define readlns(f,lns,buf,nl)	readnlns(f,lns,buf,nl,(LINELEN)+1)
#endif
#define create_indn(N,T)	uint8_t indn_##N(T t[], T p, uint8_t n)\
{\
	for(uint8_t k = 0; k < n; k++) if (t[k] == p) return k;\
	return n;\
}
#define create_mnind(t,c,T,nT)	T t##nind_##T(T v[], nT n)\
{\
	nT m = 0;\
	for (nT i = 1; i < n; i++) if (v[i] c v[m]) m = i;\
	return m;\
}

#ifdef H_MAX
#ifndef V_MAX
#error	Hash required, but no V_MAX defined
#endif
#ifndef V_TYPE
#define V_TYPE	uint32_t
#endif
typedef struct Hash {
#ifdef D_HASH
	uint32_t def;
#endif
#if V_MAX>(1<<15)
	uint32_t len;
	uint32_t hash[H_MAX]; //points to number <= len
#else
	uint16_t len;
	uint16_t hash[H_MAX]; //points to number <= len
#endif
	V_TYPE values[V_MAX];
} Hash;
#ifdef D_HASH
#define hash_get(h,k)	(h->hash[k]?h->values[h->hash[k]]:h->def)
Hash *create_Hash(int def)
#else
#define hash_get(h,k)	(h->values[h->hash[k]])
Hash *create_Hash(void)
#endif
{
	Hash *d = malloc(sizeof(Hash));
	d->len++;
#ifdef D_HASH
	d->def = def;
#endif
	return d;
}
_Bool safe_hash_push(Hash *h, V_TYPE i){
	if (h->hash[i] < h->len && h->values[h->hash[i]] == i) return 0;
	h->values[h->len] = i;
	h->hash[i] = h->len++;
	return 1;
}
void hash_set(Hash *h, uint32_t k, V_TYPE v)
{
	h->values[h->len] = v;
	h->hash[k] = h->len++;
}
#define hash_push(h,i) h.hash[h.values[h.len]=i] = h.len++	//NOTE: undef behavior; h.len++ is expected to be incremented AFTER [h.len] is read
#endif
