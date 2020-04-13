#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#ifndef TTAB
#define TTAB

typedef struct page
{
	char *URL;
	int nrRes;
	Resource* resources; //array of resources 
}TPage,*APage;

typedef struct tab
{
	TPage *currentPage;
	void *back,*forward;
	struct tab *urm;
}TTab,*ATab;

TPage *initPage(char *URL);
TTab *initTab();
void back(TTab *tab); // scoate din back daca nu e vida ,schimba pag curenta si o adauga n forward 
void forward(TTab *tab);// scoate din forward si o init ca pg curenta si pe cea curenta de dinainte o baga n back
void gotoURL(TTab *tab,char *URL); // modifica pagina curenta 
void printPage(TTab *t);//afiseaza url paginii din tab;
void freePage(void *info);
void delTab(void *t);
void elibereazaPagina(void *info);
#endif