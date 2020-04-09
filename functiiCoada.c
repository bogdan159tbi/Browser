#include "TCoada.h"

void *InitQ(size_t d) // d e dim unui elem introdus in caoda
{
	AQ q = (AQ)calloc(1,sizeof(TCelQ));
	if(!q)
		return NULL;
	q->dime = d;
	q->ic = q->sc = NULL;
	return (void*)q;
}

int IntrQ(void **a,void *ae)
{
	ACelQ aux = calloc(1,sizeof(TCelQ));
	if(!aux)
		return 0;
	memcpy(aux->info,ae,(*a)->dime);//ae sa fie alocat inainte sau fac ca la stiva sa aloc aux->info;
	aux->urm = NULL;
	if(!EMPTYQ(*a))
	{
		(*a)->sc->urm = aux;
		(*a)->sc = aux;
	}
	else
	{
		(*a)->ic = aux;
		(*a)->sc = aux;
	}
	return 1;
}

int ExtrQ(void **a,void *ae,TFreeQ freeEl)
{
	if(!EMPTYQ)
	{
		ACelQ aux = calloc(1,sizeof(TCelQ));
		if(!aux)
		return 0;
		aux->info = calloc(1,(*a)->dime);
	 	if((*a)->sc == (*a)->ic){
			aux = (*a)->ic;
			(*a)->ic = (*a)->sc = NULL;
	 	}
		else
		{
			aux = (*a)->ic;
			(*a)->ic = aux->urm;
		}
		memcpy(ae,aux->info,(*a)->dime);
		//elibereaza aux->info;
		freeEl(aux->info);
		free(aux);
		return 1;
	}
	else
		return 0;

}

void DistrQ(void **a,TFreeQ freeEl)
{
	AQ q = (AQ)(*a),aux;
	for(;q != NULL; )
	{
		aux = q;
		q = q->urm;
		freeEl(aux->info);
		free(aux);
	}	
	free(*a);
	*a = NULL;
}



void IntrQSorted(void **q,void *ae,TFCmp cmp)
{
	if(EMPTYQ(*q))
	{
		IntrQ(q,ae);
		return;
	}
	AQ aux = InitQ(((AQ)(*q))->dime);//nus daca sa pun void* la aux
	if(!aux)
		return;

	void *elem = calloc(1,((AQ)(*q))->dime);
	if(!elem)
	{
		free(aux);
		return;
	}
	while(!EMPTYQ(*q))
	{
		if(cmp((*q)->ic,ae) < 0 )
		{
			ExtrQ(q,el);
			IntrQ(&aux,elem);
		}
		else
			break;
	}
	IntrQ(&aux,el);
	while(ExtrQ(q,el))
		IntrQ(&aux,el);
	free(el);//pt ca fac memcpy la intrq
	(*q)->ic = aux->ic;
	(*q)->sc = aux->sc;
	free(aux);
}