#include "TTab.h"
#include "utils.h"
#include "TStiva.h"
TPage *initPage(char *URL)
{
	TPage *webpg = calloc(1,sizeof(TPage));
	if(!webpg)
		return NULL;
	webpg->URL = calloc(strlen(URL),sizeof(char));
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
	free(pg->URL);
	int i;
	freeResources(pg->resources,pg->nrRes);
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
		if(tab->forward != NULL)
		if(!EMPTYS(tab->forward)) 
			DistrS(tab->forward,freePage);
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