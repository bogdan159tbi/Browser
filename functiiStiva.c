#include "TStiva.h"

void *InitS(size_t d)
{
	ASt st = (ASt)calloc(1,sizeof(TStiva));
	if(!st)
		return NULL;
	st->dime = d;
	st->vf = NULL;
	return (void*)st;
}

int Push(void *st,void *ae)
{
	ACelSt aux = (ACelSt)calloc(1,sizeof(TCelSt));
	if(!aux)
		return 0;
	aux->info = calloc(1,((ASt)st)->dime);
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	memcpy(aux->info,ae,((ASt)st)->dime);
	aux->urm = ((ASt)st)->vf;
	((ASt)st)->vf = aux;
}

int Pop(void  *s,void *ae)
{
	if(EMPTYS(s))
		return 0;
	memcpy(ae,((ASt)st)->vf,((ASt)st)->dime);
	ACelSt aux = ((ASt)st)->vf;
	((ASt)st)->vf = aux->urm;
	//elibereaza aux->info care este o pagina web
	free(aux);
	return 1;
}
int Top(void *st,void *ae)
{
	if(EMPTYS(s))
		return 0;
	memcpy(ae,((ASt)st)->vf,((ASt)st)->dime);
	return 1;
}

void DistrS(void **st,TFreeS f)// st == (ASt)st adica distruge o lista
{
	ASt p = (ASt)(*st),aux;
	for(; p != NULL; )
	{
		aux = p;
		p = p->urm;
		f(aux->info);
		free(aux);
	}
}

void AfisS(void *a,afiElS afis)
{
	ASt p = (ASt)a;
	for(;p != NULL ; p = p->urm)
		afis(p->info);
}

void RastoarnaS(void *dest,void *src)
{
	if(src->dime != dest->dime || (TStiva*)src == NULL) 
		return;
	ACelSt ld = ((ACelSt)dest)->vf;
	ACelSt ls = ((ACelSt)src)->vf;

}