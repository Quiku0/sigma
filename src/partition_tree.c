#include "partition_tree.h"
#include "files.h"
#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
struct node* tree_init_node(int level){
    /*create the node with the good level, the other oarameter is at zero*/
    if(level<0){
        fprintf(stderr, "The parameter needs to be positive or null.");
        return NULL;
    }
    struct node* nodes=(struct node*)malloc(sizeof(struct node));
    nodes->level=level;
    nodes->signature=(int *)NULL;
    nodes->partition=(int *)NULL;
    nodes->nexts=NULL;
    nodes->nb_next=0;
    nodes->nb_vertice=0;
    nodes->fsi=0;
    nodes->vsi=0;
    return nodes;
}

void tree_copy_signature(struct node* start,struct node* end,int plus){
    /*copy the signature of node start into the node end with the addtionnal the sign give by plus */
    end->signature=(int *)malloc(end->level*sizeof(int)); //initialisation of signature table
    for(int i=0;i<start->level;i++){
        //copy the signature
        end->signature[i]=start->signature[i];
    }
    end->signature[start->level]=plus;
    //add the signature for this level
}
struct tree* tree_create_tree(int i,int m,struct graph* rand_graph,int* nb_cycle,int* pile_vide){
    //create the tree of algorithm 1 of the document: Exact Matching of Random Graphs with Constant Correlation
    struct tree* trees=(struct tree*)malloc(sizeof(struct tree));
    struct node* node_l;
    struct node* node_r;
    struct files file;
    int* vue=calloc(graph_get_n(rand_graph),sizeof(int));
    struct node* nodes=tree_init_node(0);
    //variable initialisation
    init_file(&file);
    //tree
    trees->nb_nodes=1;
    trees->level_max=m;
    //T^0 inialisation
    nodes->nb_vertice=1;
    nodes->partition=(int *)malloc(sizeof(int));
    nodes->partition[0]=i;
    nodes->nb_next=2;
    nodes->nexts=(struct node**)malloc(2*sizeof(struct node*));
    nodes->nexts[0]=NULL;
    nodes->nexts[1]=NULL;
    //vue is a vecteur for prohibit a repetition of a vertice in our tree
    vue[i]=1;
    nodes->nb_vertice=1;
    trees->vertax=nodes;
    while(nodes!=NULL&&nodes->level<m){
        //this while and the file structure replace the two for boucle in the algorithm 
        node_l=tree_init_node(nodes->level+1);
        node_l->nb_next=2;
        node_l->nexts=(struct node**)malloc(2*sizeof(struct node*));
        node_l->nexts[0]=NULL;
        node_l->nexts[1]=NULL;
        node_r=tree_init_node(nodes->level+1);
        node_r->nb_next=2;
        node_r->nexts=(struct node**)malloc(2*sizeof(struct node*));
        node_r->nexts[0]=NULL;
        node_r->nexts[1]=NULL;
        //create and calculate the two T^k+1
        for(int t=0;t<nodes->nb_vertice;t++){
            for (int j=0;j<graph_get_n(rand_graph);j++){
                if(graph_adjacent_vertice(rand_graph,nodes->partition[t],j) ){
                    if(!vue[j]){
                        vue[j]=1;
                        double val;
                        double mean;
                        if(graph_get_p(rand_graph)==-1){
                            val=graph_adjacent_vertice(rand_graph,nodes->partition[t],j);
                            mean=0;
                        }else{
                            val=graph_deg(rand_graph,j);
                            mean=graph_get_n(rand_graph)*graph_get_p(rand_graph);
                        }
                        if(val<mean){
                            node_l->partition=(int *)realloc(node_l->partition,(node_l->nb_vertice+1)*sizeof(int));
                            node_l->partition[node_l->nb_vertice]=j;
                            node_l->nb_vertice++;
                        }else{
                            node_r->partition=(int *)realloc(node_r->partition,(node_r->nb_vertice+1)*sizeof(int));
                            node_r->partition[node_r->nb_vertice]=j;
                            node_r->nb_vertice++;
                        }
                    }else{
                        (*nb_cycle)++;
                    }
                }
            }
        }
        if(node_l->nb_vertice){
            //add in the correct place the T_-1
            tree_copy_signature(nodes,node_l,-1);
            nodes->nexts[0]=node_l;
            put_on(node_l,&file);
            trees->nb_nodes++;
        }else{
            //deletion of non significative node in the tree
            free(node_l);
        }
        if(node_r->nb_vertice){
            //add in the correct place the T_+1
            tree_copy_signature(nodes,node_r,+1);
            nodes->nexts[1]=node_r;
            put_on(node_r,&file);
            trees->nb_nodes++;
        }else{
            //deletion of non significative node in the tree
            free(node_r);
        }
        nodes=(struct node*)scroll(&file);
    }
    if(nodes==NULL){
        //printf("file vide\n");
        (*pile_vide)++;
    }else{
        put_on(NULL,&file);
    }
    double mean;
    if(graph_get_p(rand_graph)==-1){
        mean=graph_estim_mean(rand_graph);
    }else{
        mean=graph_get_n(rand_graph)*graph_get_p(rand_graph);
    }
    while(nodes!=NULL&&nodes->level<m+1){
        for(int t=0;t<nodes->nb_vertice;t++){
            for (int j=0;j<graph_get_n(rand_graph);j++){
                if(graph_adjacent_vertice(rand_graph,nodes->partition[t],j)!=0&& !vue[j]){
                    vue[j]=1;
                    nodes->fsi+=graph_deg(rand_graph,j)-1-mean;
                    nodes->vsi+=1;
                }
            }
        }
        if(graph_get_p(rand_graph)!=-1){
            nodes->vsi*=graph_get_n(rand_graph)*graph_get_p(rand_graph)*(1-graph_get_p(rand_graph));
        }else{
            nodes->vsi*=graph_estim_mean(rand_graph)*(1-graph_estim_mean(rand_graph)/graph_get_n(rand_graph));
        }
        nodes=(struct node*)scroll(&file);
    }
    //erase the none used value in the file
    clear_file(&file);
    free(vue);
    return trees;
}

struct tree* tree_create_tree_2(int i,int m,struct graph* rand_graph,int nb_next,PyObject* call,PyObject* f,PyObject* v,PyObject* MG){
    //create the tree of algorithm 1 of the document: Exact Matching of Random Graphs with Constant Correlation
    PyObject *arglist;
    PyObject *result;
    struct tree* trees=(struct tree*)malloc(sizeof(struct tree));
    struct files file;
    int* vue=calloc(graph_get_n(rand_graph),sizeof(int));
    struct node* nodes=tree_init_node(0);
    //variable initialisation
    init_file(&file);
    //tree
    trees->nb_nodes=1;
    trees->level_max=m;
    //T^0 inialisation
    nodes->nb_vertice=1;
    nodes->partition=(int *)malloc(sizeof(int));
    nodes->partition[0]=i;
    //vue is a vecteur for prohibit a repetition of a vertice in our tree
    vue[i]=1;
    nodes->nb_vertice=1;
    trees->vertax=nodes;
    while(nodes!=NULL&&nodes->level<m){
        //this while and the file structure replace the two for boucle in the algorithm 
        nodes->nb_next=nb_next;
        nodes->nexts=(struct node**)malloc(nb_next*sizeof(struct node*));
        for(int i=0;i<nb_next;i++){
            nodes->nexts[i]=tree_init_node(nodes->level+1);
        }
        //create and calculate the two T^k+1
        for(int t=0;t<nodes->nb_vertice;t++){
            for (int j=0;j<graph_get_n(rand_graph);j++){
                if(graph_adjacent_vertice(rand_graph,nodes->partition[t],j)&& !vue[j]){
                    vue[j]=1;
                    arglist = Py_BuildValue("(Oi)",MG,j);
                    result =PyObject_CallObject(call,arglist);
                    if(result==NULL){
                        return NULL;
                    }
                    long enpla=PyLong_AsLong(result);
                    if(enpla<-1&&enpla>nodes->nb_next){
                        fprintf(stderr,"error fonction");
                        return NULL;
                    }else if(enpla>-1){
                        nodes->nexts[enpla]->partition=(int *)realloc(nodes->nexts[enpla]->partition,(nodes->nexts[enpla]->nb_vertice+1)*sizeof(int));
                        nodes->nexts[enpla]->partition[nodes->nexts[enpla]->nb_vertice]=j;
                        nodes->nexts[enpla]->nb_vertice++;
                    }else{
                        vue[j]=0;
                    }
                }
            }
        }
        for(int i=0;i<nodes->nb_next;i++){
            if(nodes->nexts[i]->nb_vertice!=0){
                tree_copy_signature(nodes,nodes->nexts[i],i);
                put_on(nodes->nexts[i],&file);
                trees->nb_nodes++;
            }else{
                //deletion of non significative node in the tree
                tree_clear_node(nodes->nexts[i]);
                nodes->nexts[i]=NULL;
            }
        }
        nodes=(struct node*)scroll(&file);
    }
    if(nodes!=NULL)
        put_on(NULL,&file);
    while(nodes!=NULL&&nodes->level<m+1){
        int* vue2=calloc(graph_get_n(rand_graph),sizeof(int));
        PyObject *pi=PyList_New(0);
        for(int t=0;t<nodes->nb_vertice;t++){
            for (int j=0;j<graph_get_n(rand_graph);j++){
                if(graph_adjacent_vertice(rand_graph,nodes->partition[t],j)!=0&& !vue[j]&& !vue2[j]){
                    vue[j]=1;
                    vue2[j]=1;
                    PyList_Append(pi,PyLong_FromLong(j));
                }
            }
        }
        arglist = Py_BuildValue("(OO)",MG,pi);
        result =PyObject_CallObject(f,arglist);
        if(result==NULL){
            return NULL;
        }
        nodes->fsi=PyFloat_AsDouble(result);
        Py_DECREF(arglist);
        arglist = Py_BuildValue("(OO)",MG,pi);
        result =PyObject_CallObject(v,arglist);
        if(result==NULL){
            return NULL;
        }
        nodes->vsi=PyFloat_AsDouble(result);
        Py_DECREF(arglist);
        Py_DECREF(pi);
        free(vue2);
        nodes=(struct node*)scroll(&file);
    }
    Py_DECREF(arglist);
    Py_DECREF(result);
    //erase the none used value in the file
    clear_file(&file);
    free(vue);
    return trees;
}
void tree_post_sign(struct node* nodes){
    /*post the node signature in the terminal*/
    for(int i=0;i<nodes->level;i++){
        printf("%d ",nodes->signature[i]);
    }
    printf("\n");
}
void post_nodes(struct node* nodes){
    /*post all detail about the current node and her children in the terminal*/
    if(nodes!=NULL){
        printf("T de level %d et de signature ",nodes->level);
        tree_post_sign(nodes);
        printf("contient les noeud :\n");
        for (int i = 0; i < nodes->nb_vertice; i++)
        {// post the node's vertices
            printf("%d ",nodes->partition[i]);
        }
        printf("\n");
        printf("%lf,%lf\n",nodes->fsi,nodes->vsi);
        printf("\n");
        for (int i=0; i<nodes->nb_next;i++){
            post_nodes(nodes->nexts[i]);
        }
        //make the same post for her right child
    }
}
void tree_post_tree(struct tree* trees){
    // post all information of all tree nodes in the terminal
    post_nodes(trees->vertax);
}
void tree_clear_node(struct node* nodes){
    //erase all node part in the heap
    if(nodes!=NULL){
        for(int i=0; i<nodes->nb_next; i++){
            tree_clear_node(nodes->nexts[i]);
        }
        free(nodes->nexts);
        free(nodes->signature);
        free(nodes->partition);
        free(nodes);
    }
}
void tree_clear_tree(struct tree* trees){
    //erase all tree part in the heap
    tree_clear_node(trees->vertax);
    free(trees);
}
void fsi_vsi_nodes(struct node* nodes,int m,struct graph* graphs,double* fsi,double* vsi){
    if(nodes!=NULL){
        //seach of the T^m+1 nodes
        if(nodes->level==m){
            /*for (int i = 0; i < nodes->nb_vertice; i++)
            {
                if(graph_get_p(graphs)!=0){
                    *fsi+=graph_deg(graphs,nodes->partition[i])-1-graph_get_n(graphs)*graph_get_p(graphs);
                }else{
                    *fsi+=graph_deg(graphs,nodes->partition[i])-1-graph_estim_mean(graphs);
                }
            }*/
            *fsi+=nodes->fsi;
            *vsi+=nodes->vsi;
            //printf("%lf, %lf\n",nodes->vsi,*vsi);
            //printf("%lf : %lf\n",*fsi,*vsi);
        }else{
            for(int i=0;i<nodes->nb_next;i++){
                fsi_vsi_nodes(nodes->nexts[i],m,graphs,fsi,vsi); 
            }
        }
    
    }
}
void tree_fsi_vsi(struct tree* trees, int * s, int l_s,struct graph* graphs,double* fsi,double* vsi){
    //vi et fi is the algorithm 1 du from document Exact Matching of random Graphs with Constant Correction contraine by s
    if(l_s>trees->level_max+1){
        fprintf(stderr,"s is to long");
    }else{
        //search of good sub_tree
        struct node* nodes=trees->vertax;
        int j=0;
        while(nodes!=NULL&&j<l_s){
            nodes=nodes->nexts[s[j]];
            j++;
        }
        //calculate of fi and vi
        *fsi=0;
        *vsi=0;
        fsi_vsi_nodes(nodes,trees->level_max,graphs,fsi,vsi);
        
    }
    
}
