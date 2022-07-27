#ifndef PARTION_TREE_H
#define PARTION_TREE_H 1
#include "graph.h"
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
/*
level corresponds of  lastest level in the tree
signature is the binary vector of node
partition is a vector of all vertices in Nt(T^k_s)^St(i,k+1)
nb_vertice is the partition
left is for the next vertice correspond child nodes with a degree superior of np
right is for the next vertice correspond child nodes with a degree superior of np
the void signature is defined by level=0
the void collection of vertices is defined by nb vertice=0
node,partition,signature is in the heap
*/
struct node{
    int level;
    int * signature;
    int nb_vertice;
    int * partition;
    int nb_next;
    struct node** nexts;
    double fsi;
    double vsi;
};

/*
tree is in the heap
*/
struct tree
{
    int nb_nodes;
    struct node* vertax;
    int level_max;
};
struct node* tree_init_node(int level);
/*create the node with the good level, the other oarameter is at zero*/
/*level is the level of all vertice*/

void tree_copy_signature(struct node* start,struct node* end,int plus);
/*copy the signature of node start into the node end with the addtionnal the sign give by plus */

void tree_post_sign(struct node* nodes);
 /*post the node signature in the terminal*/
void tree_post_tree(struct tree* trees);
// post all information of all tree nodes in the terminal
struct tree* tree_create_tree_2(int i,int m,struct graph* rand_graph,int ,PyObject *,PyObject *,PyObject *,PyObject* MG);
//create the tree of algorithm 1 of the document: Exact Matching of Random Graphs with Constant Correlation
/*i is the vertax of the graph
m is a depth parameter
n is the number of vertice in the graph
np is the value we will return
rand_graph is the graph we will appoximate
*/

struct tree* tree_create_tree(int i,int m,struct graph* rand_graph,int* nb_cycle,int *pile_vide);
//create the tree of algorithm 1 of the document: Exact Matching of Random Graphs with Constant Correlation
/*i is the vertax of the graph
m is a depth parameter
n is the number of vertice in the graph
np is the value we will return
rand_graph is the graph we will appoximate
*/
void tree_clear_node(struct node* nodes);
//erase all node part in the heap
void tree_clear_tree(struct tree* trees);
//erase all tree part in the heap

void tree_fsi_vsi(struct tree* trees, int * s, int l_s, struct graph* graphs,double* fsi,double* vsi);
//vi et fi is the algorithm 1 du from document Exact Matching of random Graphs with Constant Correction contraine by s
/*
trees is the tree
s is road
n is the number of vertice
l_s is the lenght of the road
graph is the graph adjencent matrix
p is the probability of a edje between two vertice
fsi and vsi are the result variable
*/

#endif