#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef STIVA
#define STIVA

typedef void (*TFreeS)(void *info);
typedef void (*afiElS)(void *info);
typedef struct celSt
{
	struct celSt *urm;
	void *info;
}TCelSt,*ACelSt;

typedef struct stiva
{
	size_t dime; //dim unui element = dim unei pg web
	ACelSt vf; //adresa celulei din varf
}TStiva,*ASt;

#define VF(a) (((AST)(a))->vf)
#define DIME(a) (((ASt)(a))->dime)
#define EMPTYS(a) ( (((Ast)(st))->vf) == NULL)
//functii de push,pop si trebuie sa parcurg stiva fara a itera ??

void *InitS(size_t d);
//functie pt inserare in stiva: 1 a reusit,0 = n a reusit
int Push(void *a,void *ae); // ae = adr elem de inserat 
int Top(void *a,void *ae);//copiaza elem din varful stivei la adr ae
int Pop(void *a,void *ae); //sterge elem din varful stivei si pastreaza info la adr ae
void DistrS(void **a);
void AfisS(void *a,afiElS afis);//echiv cu afisarea unei liste
void RastoarnaS(void *dest,void *src);

#endif