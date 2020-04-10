#include "utils.h"

//returns a dynamically allocated vector of Resources
Resource* get_page_resources(const char *URL_Name, int *n){
    int i, j, url_name_len = strlen(URL_Name);
    unsigned int resource_nr = 0;
    unsigned long size = 0;
    if(URL_Name == NULL){
        return NULL;
    }

    for(i = 0; i < url_name_len; i++){
        resource_nr += URL_Name[i];
    }

    resource_nr %= 13;
    Resource *result = (Resource *)calloc(resource_nr, sizeof(Resource));
    *n = resource_nr;
    for(i = 0; i < resource_nr; i++){

        sprintf(result[i].id, "%s-(%d)", URL_Name, i);
        size = 0;
        for(j = 0; j < strlen(result[i].id); j++){
            size += result[i].id[j];
        }

        /* Some randomness */
        size ^= size << 3;
        size += size >> 5;
        size ^= size << 4;
        size += size >> 17;
        size ^= size << 25;
        size += size >> 6;

        /* 100MB Maximum size */
        result[i].size = size % 104857601;
        result[i].downloaded_size = 0;
    }

    return result;
}

void list_dl(Resource *array,int nr)
{   
    int i;
    for(i = 0 ;i < nr ;i++)
        printf("[%d \"%s\" : %ld]\n",i,array[i].id,array[i].size);
}

void freeResource(Resource *r)
{
    free(r);
}

void freeResources(Resource *array,int nr)
{  int i;
    for(i = 0 ;i < nr ;i++)
        freeResource(&array[i]);
}