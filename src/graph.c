#include "graph.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>


void graph_dealloc(struct graph* gp){
    for (int i = 0; i < gp->n; i++)
    {
        free(gp->adjacent[i]);
    }
    free(gp->adjacent);
    free(gp->deg);
    free(gp);
}
struct graph *graph_init(int n, double p){
    //printf("oui\n");
    struct graph *gp;
    if(n>=0){
        if((p>1||p<0)&&p!=-1){
            fprintf(stderr, "P is between [0,1].\n");
            return NULL;
        }
        gp=(struct graph*)malloc(sizeof(struct graph));
        gp->n=n;
        gp->p=p;
        gp->adjacent=(double **)calloc(gp->n,sizeof(double *));
        if(gp->adjacent==NULL){
            fprintf(stderr, "Erreur memoir\n");
            return NULL;
        }
        gp->deg=(double *)calloc(gp->n,sizeof(double));
        if(gp->deg==NULL){
            fprintf(stderr, "Erreur memoir\n.");
            return NULL;
        }
        gp->mean=0;
        for (int i = 0; i < gp->n; i++)
        {
            gp->adjacent[i]=(double *)calloc(gp->n,sizeof(double));
            if(gp->adjacent[i]==NULL){
                gp->n=i;
                fprintf(stderr, "Erreur memoir\n.");
                return NULL;
            }
            gp->deg[i]=-1;
        }
    }else{
        fprintf(stderr,"N is greater than 0.\n");
        return NULL;
    }
    return gp;
}




int graph_set_n(struct graph* gp, long value){
    if(value<0){
        fprintf(stderr,"N is greater than 0.\n");
        return -1;
    }else{
        for (int i = 0; i < gp->n; i++)
        {
            free(gp->adjacent[i]); 
            
        }
        free(gp->adjacent);
        free(gp->deg);
        gp->n=value;
        gp->adjacent=(double **)calloc(gp->n,sizeof(double *));
        if(gp->adjacent==NULL){
            fprintf(stderr, "Erreur memoir\n.");
            return -1;
        }
        gp->deg=(double *)calloc(gp->n,sizeof(double));
        if(gp->deg==NULL){
            fprintf(stderr, "Erreur memoir\n.");
            return -1;
        }
        for (int i = 0; i < gp->n; i++)
        {
            gp->adjacent[i]=(double *)calloc(gp->n,sizeof(double));
            if(gp->adjacent[i]==NULL){
                gp->n=i;
                fprintf(stderr, "Erreur memoir\n.");
                return -1;
            }
        }
        return 0;
    }
}

int graph_set_p(struct graph* gp,double p){
    if(p>1||p<0){
        fprintf(stderr,  "P is between [0,1].\n");
        return -1;
    }else{
        gp->p=p;
        return 0;
    }
}
int graph_set_adjacent_vertice (struct graph *gp, int i, int j,double value){
    //adjacent_vertice returns the number of edges between two vertices
    if(i<0||i>=gp->n){
        fprintf(stderr,   "i is between [0,%ld].\n",gp->n);
        return 1;
    }
    if(i<0||j>=gp->n){
        fprintf(stderr,   "j is between [0,%ld].\n",gp->n);
        return 1;
    }
    if(value<0){
        fprintf(stderr, "value is greater than 0\n");
        return 1;
    }
    
    gp->adjacent[i][j]=value;
    gp->adjacent[j][i]=value;
    return 0;
}
/*static PyObject *generate_graph(struct graph *gp, PyObject *args, PyObject *kwds){
// generate_graph generate the Erdos-Rényi model graph with n vertice and a probability p
    int i,j;
    //printf("%ld\n",time(NULL));
    for (int i = 0; i < gp->n; i++)
    {
        //printf("%d\n",i);
        free(gp->adjacent[i]);
        
    }
    //printf("oui\n");
    free(gp->deg);
    free(gp->adjacent);
    //printf("oui\n");
    if(graph_init(gp,args,kwds)){
        return NULL;
    }
    //printf("oui\n");
    gp->mean=gp->n*gp->p;
    for(i=0; i<gp->n; i++)
        for(j=0;j<i; j++)
        {
            if((rand()*1.0)/RAND_MAX <= gp->p) 
            {
                gp->adjacent[i][j]=1.0; 
                gp->adjacent[j][i]=1.0;
            }
    }
    return PyLong_FromLong(1); 
}
static PyObject *generate_a_sub_graph(struct graph *gp, PyObject *args, PyObject *kwds){
    int i,j; 
    double a=1;
    static char *kwlist[]={"a",NULL};
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "|d",kwlist,&a)){
        return NULL;
    }
    if(a<0||a>1){
        PyErr_SetString(PyExc_ValueError, "alpha is between [0,1]");
        return NULL;
    }
    //printf("%lf\n",a);
    //PyObject ar[3]={PyLong_FromLong(gp->n),PyLong_FromLong(gp->p),NULL};
    struct graph* A=(struct graph *)graph_new(Py_TYPE(gp),NULL,NULL);
    //graph_init(A,ar,NULL);
    A->n=gp->n;
    A->p=gp->p;
    A->adjacent=(double **)calloc(A->n,sizeof(double *));
    if(A->adjacent==NULL){
        PyErr_NoMemory();
        return NULL;
    }
    A->deg=(double *)calloc(gp->n,sizeof(double));
    if(A->deg==NULL){
        PyErr_NoMemory();
        return NULL;
    }
    for (int i = 0; i < A->n; i++)
    {
        A->adjacent[i]=(double *)calloc(A->n,sizeof(double));
        if(A->adjacent[i]==NULL){
            gp->n=i;
            PyErr_NoMemory();
            return NULL;
        }
        A->deg[i]=-1;
    }
    A->mean=gp->mean;
    for(i=0; i<A->n; i++)
        for(j=0;j<i; j++)
        {
            double ran=rand()*1.0;
            //printf("%lf\n",ran);
            if(gp->adjacent[i][j] && (ran)/RAND_MAX <a) 
            {
                A->adjacent[i][j]=1; 
                A->adjacent[j][i]=1;
            }
    }
    //printf("\n%lf\n",graph_estim_mean(gp));
    return (PyObject *)A;
}
static PyObject *generate_graph_Wigner(struct graph *gp, PyObject *args, PyObject *kwds){
    for (int i = 0; i < gp->n; i++)
    {
        //printf("%d\n",i);
        free(gp->adjacent[i]);
        
    }
    //printf("oui\n");
    free(gp->deg);
    free(gp->adjacent);
    //printf("oui\n");
    if(graph_init(gp,args,kwds)){
        return NULL;
    }
    gp->p=0;
    double U1, U2;
    for(int i=0; i<gp->n; i++){
        for(int j=0;j<=i; j++){
            U1=rand()*1.0/RAND_MAX;
            U2=rand()*1.0/RAND_MAX;
            if(i==j){
                gp->adjacent[i][j]=2*cos(2*M_PI*U1)*sqrt(-2*log(U2))/gp->n;
            }else{
                double val=cos(2*M_PI*U1)*sqrt(-2*log(U2))/gp->n;
                gp->adjacent[i][j]=val;
                gp->adjacent[j][i]=val;
                
                
            }
        }
        //printf("%lf\n",gp->deg[i]);
    }
    return PyLong_FromLong(1);
}

static PyObject *generate_a_sub_Wigner(struct graph *gp, PyObject *args, PyObject *kwds){
    int i,j; 
    double a=0;
    PyObject *temp;
    struct graph* Z;
    static char *kwlist[]={"newg","a",NULL};
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "O|d",kwlist,&temp,&a)){
        return NULL;
    }
    if(a<0){
        PyErr_SetString(PyExc_ValueError, "value is greater than 0");
        return NULL;
    }
    if(!graph_ISPyObject(temp)){
        PyErr_SetString(PyExc_TypeError, "Seconde parameter must be a graph.graphs from module graph");
        return NULL;
    }
    Z=(struct graph *)temp;
    //printf("%lf\n",a);
    //PyObject ar[3]={PyLong_FromLong(gp->n),PyLong_FromLong(gp->p),NULL};
    struct graph* A=(struct graph *)graph_new(Py_TYPE(gp),NULL,NULL);
    //graph_init(A,ar,NULL);
    A->n=gp->n;
    A->p=gp->p;
    A->adjacent=(double **)calloc(A->n,sizeof(double *));
    if(A->adjacent==NULL){
        PyErr_NoMemory();
        return NULL;
    }
    A->deg=(double *)calloc(gp->n,sizeof(double));
    if(A->deg==NULL){
        PyErr_NoMemory();
        return NULL;
    }
    A->mean=0;
    for (int i = 0; i < A->n; i++)
    {
        A->adjacent[i]=(double *)calloc(A->n,sizeof(double));
        if(A->adjacent[i]==NULL){
            gp->n=i;
            PyErr_NoMemory();
            return NULL;
        }
        A->deg[i]=-1;
    }
    for(i=0; i<A->n; i++)
        for(j=0;j<=i; j++)
        {
            //double ran=rand()*1.0;
            //printf("%lf\n",ran);
            //printf("%d,%d\n",i,j);
            A->adjacent[i][j]=sqrt(1-a*a)*gp->adjacent[i][j]-a*Z->adjacent[i][j]; 
            //printf("%d,%d\n",i,j);
            A->adjacent[j][i]=sqrt(1-a*a)*gp->adjacent[i][j]-a*Z->adjacent[i][j];
    }
    return (PyObject *)A;
}
static PyObject *sparce_graph_Wigner(struct graph *gp, PyObject *args, PyObject *kwds){
    double niv=sqrt(log(gp->n)/gp->n);
    static char *kwlist[]={"niv",NULL};
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "|d",kwlist,&niv)){
        return NULL;
    }
    if(niv<0){
        PyErr_SetString(PyExc_ValueError, "value is greater than 0");
        return NULL;
    }
    for(int i=0; i<gp->n; i++){
        for(int j=0;j<=i; j++){
            if(fabs(gp->adjacent[i][j])<=niv){
                gp->adjacent[i][j]=0;
                gp->adjacent[j][i]=0;
            }
        }
    }
    //printf("\n%lf\n",graph_estim_mean(gp));
    return PyLong_FromLong(1);
}*/
long graph_get_n(struct graph* g){
    if(g==NULL){
        fprintf(stderr,"Mauvais argument\n");
        return -1;
    }
    return g->n;
}
double graph_get_p(struct graph* g){
    if(g==NULL){
        fprintf(stderr,"Mauvais argument\n");
        return -1;
    }
    return g->p;
}
double graph_deg(struct graph* g,int i){
    if(g==NULL){
        fprintf(stderr,"Mauvais argument\n");
        return -1;
    }
    double degre=0;
    if(g->n>i&&i>=0){    
        if(g->deg[i]==-1){
            //printf("%d\n",i);
            for(int j=0;j<g->n;j++){
                    degre+=fabs(g->adjacent[i][j]);
            }
            //printf("%d\n",i);
            g->deg[i]=degre;
        }else{
            //printf("%d\n",i);
            degre=g->deg[i];
        }
        return degre;
    }else{
        fprintf(stderr,"i is between [0,n[\n");
        return -1;
    }
}
double graph_adjacent_vertice (struct graph* graphs, int i, int j){
    //adjacent_vertice returns the number of edges between two vertices
    if(graphs==NULL){
        fprintf(stderr,"Mauvais argument\n");
        return -1;
    }
    if(i<0||i>=graphs->n){
        fprintf(stderr,"i is between [0,%ld].\n",graphs->n);
        return -1;
    }
    if(i<0||j>=graphs->n){
        fprintf(stderr,"j is between [0,%ld].\n",graphs->n);
        return -1;
    }
    return graphs->adjacent[i][j];
}
double graph_estim_mean(struct graph* g){
    if(g==NULL){
        fprintf(stderr,"Mauvais argument\n");
        return -1;
    }
    double mean=0;
    //printf("%lf\n",g->mean);
    if(g->mean==0){
        for(int i=0;i<g->n;i++){
            for(int j=0;j<g->n;j++){
                mean+=g->adjacent[i][j];
            }
        }
        mean/=g->n;
        //printf("%lf\n",mean);
        g->mean=mean;
    }else{
        //printf("%lf\n",mean);
        mean=g->mean;
    }
    return mean;
}