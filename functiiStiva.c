#include "TStiva.h"

int EMPTYS(void *a)
{
  if((((ASt)(a))->vf) == NULL)
	return 1;

  return 0;
}
void *InitS(size_t d)
{
	ASt st = (ASt)calloc(1,sizeof(TStiva));
	if(!st)
		return NULL;
	st->dime = d;
	st->vf = calloc(1,sizeof(TCelSt));
	st->vf = NULL;
	return (void*)st;
}

int PushS(void *st,void *ae)
{
	ACelSt aux = (ACelSt)calloc(1,sizeof(TCelSt));
	if(!aux)
		return 0;
	aux->info = calloc(1,((ASt)(st))->dime);
	memcpy(aux->info,ae,((ASt)st)->dime);

	aux->urm = ((ASt)(st))->vf;
	((ASt)st)->vf = aux;

	return 1;
}

int PopS(void *s,void *ae,TFreeS f)
{
	if(EMPTYS(s))
		return 0;
	memcpy(ae,((ASt)(s))->vf->info,((ASt)(s))->dime);
	ACelSt aux = ((ASt)(s))->vf;
	((ASt)(s))->vf = aux->urm;
	//elibereaza aux->info care este o pagina web
	f(aux->info);
	free(aux);
	return 1;
}
int Top(void *st,void *ae)
{
	if(EMPTYS(st))
		return 0;
	memcpy(ae,((ASt)st)->vf,((ASt)st)->dime);
	return 1;
}

void DistrS(void **st,TFreeS f)// st == (ASt)st adica distruge o lista
{
	ACelSt p = ((ASt)(*st))->vf,aux;
	void *elem = calloc(1,((ASt)(*st))->dime);
	if(!elem)
		return;
	while(!EMPTYS(*st))
		PopS(st,elem,f);
	f(elem);
	free(*st);
	*st = NULL;// e buna asta?
}

void AfisSt(void *a,afiElS afis,TFreeS f)
{
	ACelSt p = ((ASt)a)->vf;
	void *elem = calloc(1,((ASt)a)->dime);
	while (!EMPTYS(a))
	{
		PopS(a,elem,f);
		afis(elem);
	}
	free(elem);
}

void RastoarnaS(void *dest,void *src)
{
	if( ((ASt)src)->dime != ((ASt)dest)->dime || src == NULL) 
		return;

	ACelSt ld = ((ASt)dest)->vf,aux;
	ACelSt ls = ((ASt)src)->vf;
	for(; ls != NULL; ls = ls->urm)
	{
		aux = ls;
		aux->urm = ld;
		ld = aux;
	}
	((ASt)src)->vf = NULL;
	((ASt)dest)->vf = ld;
}