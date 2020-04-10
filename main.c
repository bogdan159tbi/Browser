#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
#include "TCoada.h"
#include "TStiva.h"
#include "utils.h"
*/
#include "TBrowser.h"
#include "TTab.h"
#define MAX_REQUEST 256
#define WIDTH 1024



void elimVectorResurse(void*info)
{
	Resource *r = (Resource*)info;
	free(r);

}
void afisrResurse(void *info)
{
	int i;
	Resource *r = (Resource*)info;
	printf("%s %ld\n",r->id,r->size);
}

int main()
{
	char request[MAX_REQUEST];
	long bandwith = WIDTH;
	
//citirea
	/*
	while(fgets(request,MAX_REQUEST,stdin))
	{	char cmd[20],cmd2[20];
		char *tok;		
		int okcmd2 = 0;
		if(strstr(request," "))
		{
			tok = strtok(request," ");
			strcpy(cmd,tok);
			tok = strtok(NULL,"\n");
			strcpy(cmd2,tok);
			okcmd2 = 1;
		}
		else
		{
			tok = strtok(request,"\n");
			strcpy(cmd,tok);
		}
		if(!strcmp("set_band",cmd))
		{
			bandwith = atoi(cmd2);
			bandwith *= WIDTH;
		}

	}
	*/
	TBrowser *b = initBrowser();
	TTab *tab = b->tab->info;
	gotoURL(tab,"google.com");
	addHistory(b,"google.com");
	gotoURL(tab,"facebook.com");
	addHistory(b,"facebook.com");
	back(tab);
	forward(tab);
	back(tab);
	forward(tab);
	gotoURL(tab,"yahoo.com");
	addHistory(b,"yahoo.com");
	back(tab);
	//list_dl(tab->currentPage->resources,tab->currentPage->nrRes);
	//history(b);
	TTab *t2 = newtab(b);
	gotoURL(t2,"instagram.com");
	download(b,1,tab);
	showDownloads(b);
	return 0;
}