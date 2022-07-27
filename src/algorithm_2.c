#include "graph.h"
#include "matrix_0_1.h"
#include "partition_tree.h"
#include "algorithm_2.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
static void ramdom_J(int m,int w, int J[][m],int nbchild){
    //a uniforme random of subset of {-1,1}^m of cardinality 2*w creation
    for(int i=0;i<w;i++){
        for (int j = 0; j < m; j++)
        {
            J[i][j]=rand()%nbchild;
        }
        
    }
}
struct matrix_0_1* algorithm_2(struct graph* T,struct graph* T_2,int m){
    int nb_cycle=0;
    struct matrix_0_1* b=matrix_0_1_init(graph_get_n(T));
    int nb_ar_sans_signe=0;
    int w=1;
    for(int i=0;i<m;i++){
        w*=2;
    }
    if(m<0){
        fprintf(stderr,"m is greater or equal than 0");
        return NULL;
    }
    if(w<0){
        fprintf(stderr,"w is greater or equal than 0");
        return NULL;
    }
    long n=graph_get_n(T);;
    //printf("%lf\n",graph_get_p(T));
    double f1i,f2i,v1i,v2i;
    int J[w][m];
    double sum;
    struct tree* f1[n];
    struct tree* f2[n];
    for(int i=0;i<n;i++){
        //printf("%d\n",i);
        f1[i]=tree_create_tree(i,m,T,&nb_cycle,&nb_ar_sans_signe);
        //printf("%d\n",i);
        f2[i]=tree_create_tree(i,m,T_2,&nb_cycle,&nb_ar_sans_signe);
    }
    printf("%lf\n",graph_estim_mean(T));
    tree_post_tree(f1[2]);
    ramdom_J(m,w,J,2);
    /*J[0][0]=1;
    J[0][1]=1;
    J[1][0]=1;
    J[1][1]=0;
    J[2][0]=0;
    J[2][1]=1;
    J[3][0]=0;
    J[3][1]=0;*/

    if(matrix_Set_Size(b,n)){
        return NULL;
    }
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            //calculating the sum of the if
            sum=0;
            for(int k=0;k<w;k++){
                tree_fsi_vsi(f1[i],J[k],m,T,&f1i,&v1i);
                tree_fsi_vsi(f2[j],J[k],m,T_2,&f2i,&v2i);
                //printf("%lf : %lf\n%lf : %lf\n",f1i,v1i,f2i,v2i);
                if (v1i!=0 || v2i!=0)
                {
                    
                    sum+=pow(f1i-f2i,2)/(v1i+v2i);
                }
                
                
            }
            //printf("\n");
            //printf("%lf\n",sum);
            //printf("%d,%d:%f\n",i,j,sum);
            matrix_Change_Val(b,i,j,sum);
            matrix_Change_Val(b,j,i,sum);
            //printf("%d,%d: %lf\n",i,j,sum);
        }
        //printf("\n");
        //printf("%d\n",i);
        
    }
    //printf("%lf\n",w*(1-1/sqrt(log(n))));
    return b;
}


struct matrix_0_1* algorithm_2_2(struct graph* T,struct graph* T_2,int m,int nbchild,PyObject *my_callback,PyObject *f,PyObject *v,PyObject* MG1,PyObject* MG2){
    //int nb_cycle=0;
    //int nb_ar_sans_signe=0;
    struct matrix_0_1* b=matrix_0_1_init(graph_get_n(T));
    int w=1;
    for(int i=0;i<m;i++){
        w*=nbchild;
    }
    long n=graph_get_n(T);
    //printf("%lf\n",graph_get_p(T));
    double f1i,f2i,v1i,v2i;
    int J[w][m];
    double sum;
    struct tree* f1[n];
    struct tree* f2[n];
    for(int i=0;i<n;i++){
        //printf("%d\n",i);
        f1[i]=tree_create_tree_2(i,m,T,nbchild, my_callback,f,v,MG1);
        if(f1[i]==NULL){
            return NULL;
        }
        //printf("%d\n",i);
        f2[i]=tree_create_tree_2(i,m,T_2, nbchild,my_callback,f,v,MG2);
        if(f2[i]==NULL){
            return NULL;
        }
    }
    //tree_post_tree(f1[2]);
    ramdom_J(m,w,J,nbchild);
    J[0][0]=1;
    J[0][1]=1;
    J[1][0]=1;
    J[1][1]=0;
    J[2][0]=0;
    J[2][1]=1;
    J[3][0]=0;
    J[3][1]=0;
    if(matrix_Set_Size(b,n)){
        return NULL;
    }
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            //calculating the sum of the if
            sum=0;
            for(int k=0;k<w;k++){
                tree_fsi_vsi(f1[i],J[k],m,T,&f1i,&v1i);
                tree_fsi_vsi(f2[j],J[k],m,T_2,&f2i,&v2i);
                //printf("%lf : %lf\n%lf : %lf\n",f1i,v1i,f2i,v2i);
                if (v1i!=0 || v2i!=0)
                {
                    
                    sum+=pow(f1i-f2i,2)/(v1i+v2i);
                }
                
                
            }
            //printf("\n");
            //printf("%lf\n",sum);
            //printf("%f ",sum2);
            if(matrix_Change_Val(b,i,j,sum)==-1){
                return NULL;
            }
            if(matrix_Change_Val(b,j,i,sum)==-1){
                return NULL;
            }
            //printf("%d,%d: %lf\n",i,j,sum);
        }
        //printf("\n");
        //printf("%d\n",i);
        
    }
    //printf("%lf\n",w*(1-1/sqrt(log(n))));
    for(int i=0;i<n;i++){
        tree_clear_tree(f1[i]);
        tree_clear_tree(f2[i]);
    }
    //printf("%d\n",nb_cycle);
    //printf("nombre noeud sans cycle: %lf\n",nb_ar_sans_signe*1.0/10000);
    return b;
}

