#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef COADA
#define COADA

typedef void (*TFreeQ)(void *info);
typedef int (*TFCmp)(void *x,void *y);
typedef struct celQ
{
	struct celQ *urm;
	void *info;
}TCelQ,*ACelQ

typedef struct coada
{
	size_t dime;
	ACelQ ic,sc;
}TCoada,*AQ;

#define EMPTYQ(a) ( ((AQ)(a))->ic == NULL && ((AQ)(a))->sc == NULL )

void *InitQ(size_t d);
int IntrQ(void *a,void *ae);
void ExtrQ(void *a,void *ae,TFreeQ freeEl);
void DistrQ(void **a,TFreeQ freeEl);
void IntrQSorted(void *q,void *ae);

#endif