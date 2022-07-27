#include "files.h"
#include <stdio.h>
#include <stdlib.h>


void init_file(struct files* file){
    //files initialization
    file->nb_elem=0;
    file->head=NULL;
    file->tail=NULL;
}
void clear_file(struct files *file){
    //delete files from heap
    while (file->nb_elem!=0)
    {
      scroll(file);  
    }
    file->head=NULL;
    file->tail=NULL;
}
void put_on(void * data,struct files * file){
    //add an element in the file this new element will be at the head
    struct elem* element=(struct elem*)malloc(sizeof(struct elem));
    if(file->nb_elem==0){
        file->tail=element;
    }else{
        file->head->next=element;
    }
    element->next=NULL; 
    element->data=data;
    file->head=element;
    file->nb_elem++;
}
void* scroll(struct files*file){
    //delete the first element in the file and return it
    if(file->nb_elem==0){
        fprintf(stderr,"File is empty\n");
        return NULL;
    }
    void *data=file->tail->data;
    struct elem* for_free=file->tail;
    file->tail=file->tail->next;
    free(for_free);
    file->nb_elem--;
    return data;
}
