#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TCoada.h"
#include "TStiva.h"
#include "utils.h"
#define MAX_REQUEST 256



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
		
		if(okcmd2)
			{
				printf("%s ",cmd);
				printf("%s\n",cmd2);
			}
			else
				printf("%s\n",cmd);
	}

	return 0;
}