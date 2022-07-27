#include "graph.h"
#include <stdio.h>

int main(){
    struct graph* m=graph_init(10,0.3);
    printf("%lf\n",graph_adjacent_vertice(m,1,1));
    graph_set_adjacent_vertice(m,1,1,20.5);
    printf("%lf\n",graph_adjacent_vertice(m,1,1));
    printf("%lf\n",graph_deg(m,1));
    printf("%ld\n",graph_get_n(m));
    graph_set_n(m,11);
    printf("%ld\n",graph_get_n(m));
    printf("%f\n",graph_get_p(m));
    graph_set_p(m,0.3);
    printf("%f\n",graph_get_p(m));
    printf("%lf\n",graph_estim_mean(m));
    graph_dealloc(m);
}