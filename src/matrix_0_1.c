#include "matrix_0_1.h"
#include <stdlib.h>
#include <stdio.h>

void matrix_0_1_dealloc(struct matrix_0_1 *matrix){
    //delete a matrix_0_1
    for(int i=0; i<matrix->size;i++){
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}

struct matrix_0_1 *matrix_0_1_init(int size){
    //initialise a matrix_0_1
    struct matrix_0_1* matrix;
    if(size >= 0){//verif if the size>0
        matrix=(struct matrix_0_1 *)malloc(sizeof(struct matrix_0_1));//allocation the memory for the type matrix_0_1
        matrix->size=size;
        //allocation the double matrix 
        matrix->matrix=(double **)calloc(matrix->size,sizeof(double *));
        if(matrix->matrix==NULL){
            fprintf(stderr,"Error of malloc\n");
            return NULL;
        }
        for (int i = 0; i < matrix->size; i++)
        {
            matrix->matrix[i]=(double *)calloc(matrix->size,sizeof(double));
            if(matrix->matrix[i]==NULL){
                matrix->size=i;
                fprintf(stderr,"Erreur of malloc\n");
                return NULL;
            }
        }
        return matrix;
    }else{
        fprintf(stderr,"Erreur de size\n");
        return NULL;
    }
}

 int matrix_Change_Val(struct matrix_0_1* b,int i,int j,double k){
//changes the index value i,j to 1
    if(b==NULL){
        fprintf(stderr,"You pass a NULL Pointer for the matrix\n");
        return -1;
    }
    if(i<0||i>=b->size){//verif if the i is in [0;1[
        fprintf(stderr,"i is between [0,%d].\n",b->size);
        return -1;
    }
    if(i<0||j>=b->size){//verif if the j is in [0;1[
        fprintf(stderr, "j is between [0,%d].\n",b->size);
        return -1;
    }
    b->matrix[i][j]=k;
    return 0;
}

 double matrix_Val_i_j(struct matrix_0_1* b,int i,int j){
    //return the i,j value of the matrix 
    if(b==NULL){
        fprintf(stderr,"You pass a NULL Pointer for the matrix\n");
        return -1;
    }
    if(i>=0 && j>=0 && i<b->size && j<b->size){//verif if the indice is in the right zone
        return b->matrix[i][j];
    }else{
        fprintf(stderr,"Erreur indice trop en dehors de la bonne zone\n");
        return -1;
        
    }
}

 double matrix_Trace(struct matrix_0_1* b){
    //return the trace of the matrix
    if(b==NULL){
        fprintf(stderr,"You pass a NULL Pointer for the matrix");
        return -1;
    }
    double nb=0;
    for(int i=0;i<b->size;i++){
        //calcul the matrix
        nb+= b->matrix[i][i];
    }
    return nb;
}
 int matrix_Size(struct matrix_0_1* b){
     //return the size of the matrix
    if(b==NULL){
        fprintf(stderr,"You pass a NULL Pointer for the matrix");
        return -1;
    }
    return b->size;
}

 int matrix_Set_Size(struct matrix_0_1* b, int value){
     //change the size of the matrix
    if(value<0){//verif if new size>0
        fprintf(stderr,"N is greater than 0.");
        return 1;
    }else{
        if(b!=NULL){//verification que b est bien une matrice
            //liberation de la memoire 
            for (int i = 0; i < b->size; i++)
            {
                free(b->matrix[i]);
                
            }
            free(b->matrix);
        }else{
            //reservation de la mémoire pour la nouvelle matrice
           b=(struct matrix_0_1 *)malloc(sizeof(struct matrix_0_1));
        }
        b->size=value;
        //reservation de la memoire pour sauvegarder les valeurs
        b->matrix=(double **)calloc(b->size,sizeof(double *));
        for (int i = 0; i < b->size; i++)
        {
            b->matrix[i]=(double *)calloc(b->size,sizeof(double));
        }
        return 0;
    }
}
