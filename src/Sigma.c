#include "graph.h"
#include "matrix_0_1.h"
#include "partition_tree.h"
#include "algorithm_2.h"
#include "algorithm_3.h"
#include <stdio.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

static PyObject *Sigma(PyObject *self,PyObject *args, PyObject *kwds){
    static char *kwlist[]={"G1","G2","prof","p","nbchild","class","f","v",NULL};
    double p=-1;
    int nbchild=-1,m;
    struct matrix_0_1* b;
    PyObject* temp1=NULL;
    PyObject* temp3=NULL;
    PyObject* tempcall=NULL;
    PyObject* tempf=NULL;
    PyObject* tempv=NULL;
    PyObject *retour=NULL; 
    struct graph *G1=NULL;
    struct graph *G2=NULL;
    double *temp2;
    if (!PyArg_ParseTupleAndKeywords(args,kwds, "OOi|diOOO",kwlist, &temp3,&temp1,&m,&p,&nbchild,&tempcall,&tempf,&tempv))
        return NULL;
    if(!PyArray_CheckExact(temp3)){
        PyErr_SetString(PyExc_TypeError, "G1 isn't an object with type Array");
        return NULL;
    }
    if(!PyArray_CheckExact(temp1)){
        PyErr_SetString(PyExc_TypeError, "G2 isn't an object with type Array");
        return NULL;
    }
    if(!PyArray_ISFLOAT((PyArrayObject *)temp3)){
        PyErr_SetString(PyExc_TypeError, "G1 isn't an object with subtype Float");
        return NULL;
    }
    if(!PyArray_ISFLOAT((PyArrayObject *)temp1)){
        PyErr_SetString(PyExc_TypeError, "G2 isn't an object with subtype Float");
        return NULL;
    }
    if(PyArray_NDIM((PyArrayObject *)temp3)!=2){
        PyErr_SetString(PyExc_TypeError, "G1 isn't an object with matrix");
        return NULL;
    }
    if(PyArray_NDIM((PyArrayObject *)temp1)!=2){
        PyErr_SetString(PyExc_TypeError, "G2 isn't an object with matrix");
        return NULL;
    }
    if(PyArray_DIMS((PyArrayObject *)temp3)[0]!=PyArray_DIMS((PyArrayObject *)temp3)[1]){
        PyErr_SetString(PyExc_TypeError, "G1 isn't an squarred matrix");
        return NULL;
    }
    if(PyArray_DIMS((PyArrayObject *)temp1)[0]!=PyArray_DIMS((PyArrayObject *)temp1)[1]){
        PyErr_SetString(PyExc_TypeError, "G2 isn't an squarred matrix");
        return NULL;
    }
    if(PyArray_DIMS((PyArrayObject *)temp1)[0]!=PyArray_DIMS((PyArrayObject *)temp3)[0]){
        PyErr_SetString(PyExc_TypeError, "G1 and G2 don't have the same dimension");
        return NULL;
    }
    if(m<0){
        PyErr_SetString(PyExc_ValueError, "The profondeur is geater or equal than 0");
        return NULL;
    }
    if(nbchild!=-1&&nbchild<=0){
        PyErr_SetString(PyExc_ValueError, "nbchild is greater than 0 if you pass the decision fonction or nbchild is equal to -1 for Wigner");
        return NULL;
    }
    int n=PyArray_DIMS((PyArrayObject *)temp1)[0];
    G1=graph_init(n,p);
    G2=graph_init(n,p);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            temp2=(double *)PyArray_GETPTR2((PyArrayObject *)temp3,i,j);
            graph_set_adjacent_vertice(G1,i,j,*temp2);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            temp2=(double *)PyArray_GETPTR2((PyArrayObject *)temp1,i,j);
            graph_set_adjacent_vertice(G2,i,j,*temp2);
        }
    }
    if(nbchild==-1){
        if(p!=-1&&(p>1||p<0)){
            graph_dealloc(G1);
            graph_dealloc(G2);
            PyErr_SetString(PyExc_ValueError, "p is between 0 and 1 for Erdos-Renyi or p is equal to -1 for Wigner");
            return NULL;
        }
        b=algorithm_2(G1,G2, m);
        for(int i=0;i<matrix_Size(b);i++){
            for(int j=0;j<matrix_Size(b);j++){
                printf("%lf ",matrix_Val_i_j(b,i,j));
            }
            printf("\n");
        }
        printf("\n");
        retour=algorithm_3(b);
        return retour;
    }else{
        if (!PyCallable_Check(tempcall)) {
            PyErr_SetString(PyExc_TypeError, "class must be callable(a fonction)");
            return NULL;
        }
        Py_XINCREF(tempcall);
        if (!PyCallable_Check(tempf)) {
            PyErr_SetString(PyExc_TypeError, "f must be callable(a fonction)");
            return NULL;
        }
        Py_XINCREF(tempf);
        if (!PyCallable_Check(tempv)) {
            PyErr_SetString(PyExc_TypeError, "v must be callable(a fonction)");
            return NULL;
        }
        Py_XINCREF(tempv);
        b=algorithm_2_2(G1,G2,m,nbchild,tempcall,tempf,tempv,temp3,temp1);
        
        return algorithm_3(b);
    }
}

static struct PyMethodDef sigma_Methodes []= {
    {"sigma",(PyCFunction)Sigma,METH_VARARGS | METH_KEYWORDS,"this is algorithm 2 of the Document Exact Matching of Random Graphs with Constant Correlation"},
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef sigmamodule = {
    PyModuleDef_HEAD_INIT,
    "sigma",
    NULL,
    -1,
    sigma_Methodes
};
PyMODINIT_FUNC PyInit_sigmaV1(void){
    PyObject *m;
    srand(time(NULL));
    m=PyModule_Create(&sigmamodule);
    if(m==NULL){
        return NULL;
    }
    assert(! PyErr_Occurred());
    import_array(); // Initialise Numpy
    if (PyErr_Occurred()) {
        return NULL;
    }
    return m;
}