#include "matrix_0_1.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
static void supprime(int * V,int ind,int *tvm){
    (*tvm)--;
    for (int i=ind; i<*tvm;i++){
        V[i]=V[i+1];
    }
}

PyObject *algorithm_3(struct matrix_0_1* b){
    int V1[matrix_Size(b)];
    int tV1=matrix_Size(b);
    int V2[matrix_Size(b)];
    int tV2=matrix_Size(b);
    PyObject *pi=PyList_New(matrix_Size(b));
    int tpi=0;
    for (int i=0;i<b->size;i++){
        V1[i]=i;
        V2[i]=i;
    }
    int i = 0;
    while ( i < tV1)
    {  
        int j = 1;
        int i_min[matrix_Size(b)];
        i_min[0]=0;
        int nb_min=1;
        double min=matrix_Val_i_j(b,i,V2[0]);
        while ( j < tV2)
        {
            double val=matrix_Val_i_j(b,i,V2[j]);
            if(min>val){
                min=val;
                nb_min=1;
                i_min[0]=j;
                /*pi[V1[i]]=V2[j];
                tpi++;
                supprime(V1,i,&tV1);
                supprime(V2,j,&tV2);
                j=tV2;
                i--;*/
            }else if(val==min){
                i_min[nb_min]=j;
                nb_min++;
            }
            j++;
            
        }
        
        int p=rand()%nb_min;
        PyList_SET_ITEM(pi,i,PyLong_FromLong(V2[i_min[p]]));
        tpi++;
        i++;
        supprime(V2,i_min[p],&tV2);
        
    }
    
    
    return pi;
}

/*int* algorithm_3(struct matrix_0_1* b){
    int V1[b->size];
    int tV1=b->size;
    int V2[b->size];
    int tV2=b->size;
    int *pi=(int *)malloc(b->size*sizeof(int));
    int tpi=0;
    for (int i=0;i<b->size;i++){
        V1[i]=i;
        V2[i]=i;
    }
    int i = 0;
    while ( i < tV1)
    {  
        int j = 1;
        int i_min[b->size];
        i_min[0]=0;
        int nb_min=1;
        double min=val_i_j_matrix_0_1(b,V1[i],V2[0]);
        while ( j < tV2)
        {
            double val=val_i_j_matrix_0_1(b,V1[i],V2[j]);
            if(min>val){
                min=val;
                nb_min=1;
                i_min[0]=j;*/
                /*pi[V1[i]]=V2[j];
                tpi++;
                supprime(V1,i,&tV1);
                supprime(V2,j,&tV2);
                j=tV2;
                i--;*/
            /*}else if(val==min){
                i_min[nb_min]=j;
                nb_min++;
            }
            j++;
            
        }
        int p=random()%nb_min;
        pi[V1[i]]=V2[i_min[p]];
        tpi++;
        supprime(V1,i,&tV1);
        supprime(V2,p,&tV2);
        
    }
    
    
    return pi;
    
}*/
