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
	Resource *r = (Resource*)info;
	printf("%s %ld\n",r->id,r->size);
}

int main(int argc,char *argv[])
{
	//obtin fisierele de citire iesire folosind param liniei de comanda
	char infile[10],outfile[10];
	strcpy(infile,argv[1]);
	strcpy(outfile,argv[2]);
	FILE *in , *out;
	in = fopen(infile,"rt");
	if(!in)
	{
	fprintf(stderr,"couldn't open file\n");
	return 1;
	}
	out = fopen(outfile,"wt");
	if(!out)
	{
		fclose(in);
		return 1;
	}

	char request[MAX_REQUEST];
	long bandwith = WIDTH;
	TBrowser *b = initBrowser();
	TTab *currentTab = (TTab*)(b->tab->info);
//citirea
	while(fgets(request,MAX_REQUEST,in))
	{	char cmd[200],cmd2[200] = "";
		char *tok;		
		int okcmd2 = 0;
	//printf("%s\n",request);
		if(strstr(request," "))
		{
			tok = strtok(request," ");
			strcpy(cmd,tok);
			tok = strtok(NULL,"\n");
			if(!tok)
				return 1;
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
			
		}
		else if(!strcmp("newtab",cmd))
			currentTab = newtab(b);
		else if(!strcmp("deltab",cmd))//sa eliberez memoria pt resurse pg web back forward si struc pagina si struc tab
			{
				TLista p = b->tab,aux,prev = NULL;
				if(p == NULL)
				{
					return 1;
				}
				for(;p->urm != NULL;prev = p, p = p->urm);
				aux = p;
				TTab *t = (TTab*)aux->info;
				if(t == currentTab)
				  currentTab = (TTab*)(prev->info);

				deltab(b);
			}
		else if(!strcmp("change_tab",cmd))
			currentTab = changeTab(b,atoi(cmd2));
		else if(!strcmp("print_open_tabs",cmd))
			printOpenedTabs(b,out);
		else if(!strcmp("goto",cmd)) 
		{
			char *URL = malloc(50);
			if(!URL)
				return 1;
			strcpy(URL,cmd2);
			gotoURL(currentTab,URL);
			addHistory(b,URL);
			wait(b,bandwith);
		}
		else if(!strcmp("back",cmd)) 
			back(currentTab);
		else if(!strcmp("forward",cmd))
			forward(currentTab);
		else if(!strcmp("history",cmd))  
			history(b,out);
		else if(!strcmp("del_history",cmd)){
			int nr = atoi(cmd2);
			delhistory(b,nr);
		}
		else if(!strcmp("list_dl",cmd)) {
			if(currentTab->currentPage)
			list_dl(currentTab->currentPage->resources,currentTab->currentPage->nrRes,out);
		}
		else if(!strcmp("downloads",cmd))
			showDownloads(b,out);
		else if(!strcmp("download",cmd))
		{
			int index = atoi(cmd2);
			download(b,index,currentTab);
		}
		else if(!strcmp("wait",cmd))
		{
			int seconds = atoi(cmd2);
			long bandwith2 = bandwith *seconds;
			wait(b,bandwith2);
		}
	}
	delBrowser(b);
	
	return 0;
}