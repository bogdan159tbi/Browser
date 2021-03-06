#include "TTab.h"
#include "utils.h"
#include "TStiva.h"
TPage *initPage(char *URL)
{
	TPage *webpg = calloc(1,sizeof(TPage));
	if(!webpg)
		return NULL;
	webpg->URL = calloc(30,sizeof(char));
	if(!webpg->URL)
	{
		free(webpg);
		return NULL;
	}
	strcpy(webpg->URL,URL);
	webpg->resources = get_page_resources(URL,&webpg->nrRes);
	return webpg;
}

TTab *initTab()
{
	TTab *tab = calloc(1,sizeof(TTab));
	if(!tab)
		return NULL;
	tab->currentPage = NULL;
	tab->back = tab->forward = NULL;
	tab->urm = NULL;
	return tab;
}
void freePage(void *info)
{
	TPage *pg = (TPage*)info;
	if(!pg)
		return;
	free(pg->URL);
	int i;
	freeResources(pg->resources,pg->nrRes);
}
void freeURL(void *inf)
{
	free((char*)inf);
}
//modifica pagina curenta a tabului curent
void gotoURL(TTab *tab,char *URL)
{
	TPage *aux = initPage(URL);
	if(!aux)
		return;
	if(tab->currentPage == NULL)
		tab->currentPage = aux;
	else
	{	if(tab->back == NULL)
		tab->back = InitS(sizeof(TPage));

		PushS(tab->back,tab->currentPage);
		tab->currentPage = aux;
		
		if(tab->forward != NULL){
			
		while(!EMPTYS(tab->forward)){
		void *elem = calloc(1,((ASt)(tab->forward))->dime);
		PopS(tab->forward,elem,freeURL);
		free(elem);
		}
		//free(tab->forward);

		//if(!EMPTYS(tab->forward)) 
		//	DistrS(tab->forward,freePage);

			//free(((ASt)tab->forward)->vf);
			//free(tab->forward);
		}
		//adauga in istoricul global
		
	}

}
void back(TTab *tab)
{
	if(tab->back != NULL)
	{
		if(!EMPTYS(tab->back))
		{
			TPage *auxForward = tab->currentPage,*newCurrent;
			//Top(tab->back,tab->currentPage);

			if(tab->forward == NULL)
				tab->forward = InitS(sizeof(TPage));
			if(!tab->forward)
				return;
			PushS(tab->forward,auxForward);	
			//am adaugat in forward pg curenta si acum obtin pagina anterioara = newCurrent
			newCurrent = calloc(1,sizeof(TPage));
			PopS(tab->back,newCurrent,freePage);
			memcpy(tab->currentPage,newCurrent,sizeof(TPage));//doar ca nu dau free la aux->info = varful stivei back din POpS
		}
		else
			printf("can't go back,no pages in history.\n");
	}
	else
		printf("can't go back,no pages in history.\n");

}

void forward(TTab *tab)
{
	if(tab->forward != NULL)
	{
		if(tab->currentPage && tab->back != NULL)
		{
			PushS(tab->back,tab->currentPage);
			TPage *newCurrent = calloc(1,sizeof(TPage));
			if(!newCurrent)
				return;
			PopS(tab->forward,newCurrent,freePage);
			memcpy(tab->currentPage,newCurrent,sizeof(TPage));
		}
		else
			return;//conditie in caz ca forward nu are elem
	}
}

void elibereazaPagina(void *info)
{
	TPage *pg = (TPage *)info;
	if(!pg)
		return;
	free(pg->URL);
	free(pg->resources);
	free(pg);
}



void delTab(void *tab)
{
	TTab *t = (TTab*)tab;
	if(t->currentPage ){
		free(t->currentPage->URL);
		free(t->currentPage->resources);
		free(t->currentPage);
	}
	if((t)->back){
//	DistrS((t)->back,elibereazaPagina);

	ACelSt p = ((ASt)(t->back))->vf,aux;
	void *elem = calloc(1,((ASt)(t->back))->dime);
	if(!elem)
		return;
	while(!EMPTYS(t->back)){
		PopS(t->back,elem,freePage);
		freePage(elem);
	}
	free(elem);
	
	free(((ASt)t->back)->vf);
	free(t->back);
	}
	if((t)->forward){
	//DistrS((t)->forward,elibereazaPagina);

	ACelSt p = ((ASt)(t->forward))->vf,aux;
	void *elem = calloc(1,((ASt)(t->forward))->dime);
	if(!elem)
		return;
	while(!EMPTYS(t->forward)){
		PopS(t->forward,elem,freePage);
		freePage(elem);
	}
	free(elem);
	free(((ASt)t->forward)->vf);

	free(t->forward);
	}

	free(t);
}
