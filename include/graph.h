#ifndef GRAPH_H
#define GRAPH_H 1
/*
graph is a Erdos-Rényi graph
n is the number of vertice
p is the probability to have a edge between two vertice
adjacent is the adjacent matrix of the graph
adjacent is stored in the heap
the graph is stored in the heap
the empty graph is n=0
any values in the adjacent matrix are initialized to 0
*/
struct graph
{
    double p;
    long n;
    double **adjacent;
    double *deg;
    double mean;
};

/* This section is used when compiling spammodule.c */
struct graph *graph_init(int n, double p);
void graph_dealloc(struct graph* );
int graph_set_n(struct graph* gp, long value);
int graph_set_p(struct graph* gp,double p);
int graph_set_adjacent_vertice (struct graph *gp, int i, int j,double value);
long graph_get_n(struct graph* );
double graph_get_p(struct graph*);
double graph_deg(struct graph* g,int i);
double graph_adjacent_vertice (struct graph* graphs, int i, int j);
double graph_estim_mean(struct graph* g);

#endif