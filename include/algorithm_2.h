#ifndef ALGORITHM_2_H
#define ALGORITHM_2_H 1
#include "matrix_0_1.h"
#include "graph.h"
//void algorithm_2(struct matrix_0_1*,struct graph*,struct graph*,int m,int w);
//this is algorithm 2 of the Document Exact Matching of Random Graphs with Constant Correlation
//b will be initializate
struct matrix_0_1* algorithm_2(struct graph* T,struct graph* T_2,int m);
struct matrix_0_1* algorithm_2_2(struct graph* T,struct graph* T_2,int m,int nbchild,PyObject *my_callback,PyObject *f,PyObject *v,PyObject* MG1,PyObject* MG2);
#endif