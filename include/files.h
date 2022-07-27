#ifndef FILES_H
#define FILES_H 1

/*the end of the files is the next pointer to NULL
all elements are stored the heap*/
struct elem{
    void * data;
    struct elem* next;
};
/*a empty file is the variable nb_elem at 0*/
struct files
{
    int nb_elem;
    struct elem* head;
    struct elem* tail;
};

void init_file(struct files*);
//files initialization
void clear_file(struct files *);
//delete files from heap
void put_on(void *,struct files *);
//add an element in the file
void* scroll(struct files*);
//delete an element in the file and return it
#endif