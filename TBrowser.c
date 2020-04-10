#include "TBrowser.h"
#include "TTab.h"
#include "utils.h"
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
	IntrQ((void*)&(b->downloads),r);
}	

void afisResourceQ(void *info)
{
	Resource *r = (Resource*)info;
	printf("%s %lu/%lu\n",r->id,r->downloaded_size,r->size);
}
void freeResourceQ(void *info)
{
	Resource *r = (Resource*)info;
	free(r);
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