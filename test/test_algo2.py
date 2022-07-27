#!/usr/bin/python3
import algo2
import matrix
import graph
def normal_erdo(graph_util,i):
    if (graph_util.deg(i)<graph_util.n*graph_util.p) :
        return 0
    else :
        return 1
def f(graph_util,liste):
    retour=0
    for i in liste:
        retour+=graph_util.deg(i)-graph_util.n*graph_util.p-1
    return retour
def v(graph_util,liste):
    retour=len(liste)*graph_util.n*graph_util.p*(1-graph_util.p)
    return retour

mymatrix=matrix.matrix_0_1(1)
A=graph.graphs(1,0)
print(type(A))
A.gen_rand_sans_poid(10,0.3)
for i in range(10):
    for j in range(10):
        print(A.getedje(i,j),end=" ")
    print()
print()

print(A.n,A.p)
algo2.algo_2_choice_tree(mymatrix,A,A,2,4,2,normal_erdo,f,v)
for i in range(mymatrix.size):
    for j in range(mymatrix.size):
        print(mymatrix.getval(i,j),end=" ")
    print()
algo2.algo_2(mymatrix,A,A,2,4)
for i in range(mymatrix.size):
    for j in range(mymatrix.size):
        print(mymatrix.getval(i,j),end=" ")
    print()



#Exemple wigner
A.gen_Wigner(10,0) #genere dans a un graph de wigner
Z=graph.graphs(1,0)
Z.gen_Wigner(10)
B=A.sub_wigner(Z,0.1) #creation du graph avec du bruit
A.sparce_wigner(0.09) #sparcification du graph
B.sparce_wigner(0.09)
#Affichage du graph A
for i in range(10):
    for j in range(10):
        print(A.getedje(i,j),end=" ")

    print()
algo2.algo_2(mymatrix,A,B,2,4) #creation de la matrice de correlation
for i in range(mymatrix.size):
    for j in range(mymatrix.size):
        print(mymatrix.getval(i,j),end=" ")
    print()

