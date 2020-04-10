#include "TBrowser.h"
#include "TTab.h"
#include "utils.h"
#include "TLista.h"
#include "TStiva.h"
#define MAX_URL 50
TBrowser *initBrowser()
{
	TBrowser *b = calloc(1,sizeof(TBrowser));
	if(!b)
		return NULL;
	b->tab = InitLista();
	b->tab->info = calloc(1,sizeof(TTab));
	b->downloaded = NULL;
	b->downloads = NULL;
	b->history = NULL;
	return b;
}

TTab *newtab(TBrowser *b){

	TLista p = b->tab;
	for(; p->urm != NULL; p = p->urm);
	p->urm = InitLista();
	p->urm->info = calloc(1,sizeof(TTab));
	p = p->urm;
	TTab *tab = (TTab*)(p->info);
	return tab;
}
TTab * changeTab(TBrowser *b,int index)
{
	int nr = 0;
	TLista p = b->tab;
	for(; nr != index;nr++,p = p->urm);
	TTab *tab = (TTab*)(p->info);
	return tab;
}
void addHistory(TBrowser *b,char *URL)
{
	if(b->history == NULL)
		b->history = InitQ(MAX_URL);

	IntrQ((void*)(&b->history),URL);
}
void afisUrlHistory(void *info){
	printf("%s\n",(char*)info);
}
void delUrlHistory(void *info)
{
	free(info);
}
void history(TBrowser *b)
{
	if(b->history)
	{
		AfisQ(b->history,afisUrlHistory,delUrlHistory);
	}
	else
		printf("istoric global gol\n");
}

void printOpenedTabs(TBrowser *b)
{
	TLista p = b->tab;
	int index = 0;
	for(; p != NULL ;index++, p = p->urm){
		TTab *tab = (TTab*)(p->info);
		if(tab->currentPage == NULL)
			printf("(%d : empty)\n",index);
		else
			printf("(%d : %s)\n",index,tab->currentPage->URL);

	}
}
void afisResourceQ(void *info)
{
	Resource *r = (Resource*)info;
	printf("%s %lu/%lu\n",r->id,r->size - r->downloaded_size,r->size);
}
void freeResourceQ(void *info)
{
	Resource *r = (Resource*)info;
	free(r);
}
int cmpResources(void *x,void *y)
{
	Resource *r1,*r2;
	r1 = (Resource*)x;
	r2 = (Resource*)y;
	if(r1->downloaded_size - r1->downloaded_size >  r2->size - r2->downloaded_size)
		return -1;
	return 1;
}

void download(TBrowser *b,int index,TTab *t)
{

	Resource *r = calloc(1,sizeof(Resource));
	if(!r)
		return;
	strcpy(r->id ,t->currentPage->resources[index].id);
	r->size = t->currentPage->resources[index].size;
	r->downloaded_size = t->currentPage->resources[index].downloaded_size;
	if(b->downloads == NULL)
		b->downloads = InitQ(sizeof(Resource));
	if(!b->downloads)
		return;
	IntrQSorted((void*)&(b->downloads),r,cmpResources,freeResourceQ); //IntrQSorted(void **q,void *ae,TFCmp cmp,TFreeQ fEl)
}	



void showDownloads(TBrowser *b)
{
	//afisez din AQ downloads care are elem de tip resursa 
	if(b->downloads != NULL)
		AfisQ(b->downloads,afisResourceQ,freeResourceQ);

	//afisez din TLista downloaded 
}

void freeHistoryElem(void *info)
{
	char *str = (char*)info;
	free(str);
}

void delhistory(TBrowser *b,int nrEntries)
{
	if(nrEntries > 0)
		DistrQN((void*)&b->history,freeHistoryElem,nrEntries);
	else
		DistrQ((void*)&b->history,freeHistoryElem);

}

void wait(TBrowser *b,long bandwidth)
{
	AQ coada = b->downloads;
	Resource *aux = calloc(1,sizeof(Resource));
	if(!aux)
		return;

	while(!EMPTYQ(coada) && bandwidth)
	{
		ExtrQ((void*)&coada,aux,freeResourceQ);
		if(aux->size > bandwidth && aux->downloaded_size + bandwidth <= aux->size) // adaug in lista de downloadaate daca size < bandwidth si scad size din bandwidth
		{
		 aux->downloaded_size += bandwidth;
		 bandwidth = 0;
		 IntrQSorted((void*)&coada,aux,cmpResources,freeResourceQ);
		}
		else if(bandwidth + aux->downloaded_size > aux->size)
		{	
			bandwidth  = bandwidth - aux->downloaded_size - aux->size;
			aux->downloaded_size = aux->size;
			if(b->downloaded == NULL)
				b->downloaded = InitLista();
			Inserare(&b->downloaded,aux);
		}
	}	

}

void deltab(TBrowser *b)
{
	//nu verificam daca nu ramane niciun tab deschis dupa ce l sterg pe ultimul deschis ca sa pun **
	TLista p = b->tab,aux;
	for(;p->urm->urm != NULL; p = p->urm);

	aux = p->urm;
	p->urm = NULL;
	//eliberez tabul care este info celulei din lista
	TTab *t = (TTab*)aux->info;
	/*
	DistrS(t->back,freePage);
	DistrS(t->forward,freePage);
	freePage(t->currentPage);
	*/
}