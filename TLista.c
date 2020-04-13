#include "TLista.h"

TLista InitLista()
{
	TLista aux = (TLista)calloc(1,sizeof(TCelula));
	if(!aux)
		return NULL;
	aux->info = NULL;
	return aux;
}

int Inserare(TLista *l,void *ae)
{
	TLista aux = calloc(1,sizeof(TCelula)),p = *l,pre = NULL;
	if(!aux)
		return 0;
	//aux->info = calloc(1,sizeof(ae));
	aux->info = ae;
	aux->urm = NULL;

	if(p == NULL)
		*l = aux;
	else{
		for(; p != NULL; pre = p, p = p->urm);
		pre->urm = aux;
	}
	return 1;
}

void DistrL(TLista *l,TFreeL f)
{
	TLista p = *l,aux;

	for(; p != NULL; )
	{
		aux = p;
		p = p->urm;
		//eliberare info care poate fi pg web ,elem de tip resursa .Oare tre o functie de eliberare ca parametru ??
		f(aux->info); 
		free(aux);
	}

	//free(*l);
	*l = NULL;
}

void afisareLista(TLista l,afiElL fafis)
{
	for(; l != NULL; l = l->urm)
		fafis(l->info);
}