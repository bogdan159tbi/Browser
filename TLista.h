#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef LISTA
#define LISTA

typedef void (*TFreeL)(void *info);
typedef void (*afiElL)(void *info);

typedef struct celula
{
	void *info;
	struct celula *urm;
}TCelula,*TLista;

TLista InitLista();
int Inserare(TLista *l,void *ae);
void DistrL(TLista *al,TFree felib);
void afisareLista(TLista l,afiEl fafis);

#endif