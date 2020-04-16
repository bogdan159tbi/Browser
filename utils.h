#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef _DOWNLOAD_RESOURCE_
#define _DOWNLOAD_RESOURCE_

/*
	downloaded_size can be used to save the currently downloaded size;
	by default downloaded_size is set to 0
*/
typedef struct{
	char id[100];
	unsigned long size;
	unsigned long downloaded_size;
} Resource;

Resource* get_page_resources(const char *URL_Name, int *n);
void freeResource(Resource *r);
void afisResource(Resource *r);
void list_dl(Resource *r,int nr,FILE *out);//vector de resurse din pagina curenta a unui tab curent de ex
void freeResources(Resource *array,int nr); // elibereaza vector de resurse
#endif /* _DOWNLOAD_RESOURCE_ */