#include "TTab.h"
#include "TLista.h"
#include "TCoada.h"
#ifndef TBROWSER
#define TBROWSER

typedef struct browser
{
	TLista tab;
	AQ downloads;//cu info elem de tip resource
	TLista downloaded;// cu info elem de tip resource
	AQ history;//cu stringuri URL
}TBrowser, *ABrowser;

TBrowser *initBrowser();
TTab * newtab(TBrowser *b);//creeaza un tab nou ,gol // TLista pt ca o celula din taburi are info egla ttab
void deltab(TBrowser *b);//intotdeauna va ramane un tab gol deschis
TTab* changeTab(TBrowser *b,int index);
void printOpenedTabs(TBrowser *b);//afiseaza pagina din fiecare tab folosing functia din TTab.h printPage
void history(TBrowser *b);//afiseaza elem AQ history care contine stringuri URL
void delhistory(TBrowser *b,int nr);//distruge coada AQ history
void showDownloads(TBrowser *b);//afiseaza prima oara elem de tip resource din AQ downloads si dupa din TLista downloaded
void addHistory(TBrowser *b,char *URL);
void afisUrlHistory(void *info);
void delUrlHistory(void *info);
void download(TBrowser *b,int index,TTab *t);
void afisResourceQ(void *info);
void freeResourceQ(void *info);
void freeHistoryElem(void *info);
int cmpResources(void *x,void *y);
void wait(TBrowser *b,long bandwith);//modifca dim de descarcat din AQ downloads daca s a term o baga n TLista downloaded
#endif