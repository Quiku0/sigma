import graph as gp
import matrix as mt
import algo2 as al2
import algo3 as al3

####################
#   module graph  #
###################

#initialisatin de variable graph
G=gp.graphs(11,0.5)#deuxieme argument pas obligatoire et toutes les vertices à 0 
#acces ou modification de n ou p
print(G.n,G.p)
G.n=20
G.p=0.4
print(G.n,G.p)
#access ou modification de la matrice d'adjacence
print(G.getedje(1,1))
G.setedje(1,1,20.5)
print(G.getedje(1,1))
#degres d'un graph
G.deg(1)
G.deg(0)
#graph de Erdös-Renyi
G.gen_rand_sans_poid(10, 0.3)


for i in range(G.n):
    for j in range(G.n):
        print(G.getedje(i,j),end=" ")
    print()


A=G.gen_sub_sans_poid(0.99)


for i in range(A.n):
    for j in range(A.n):
        print(A.getedje(i,j),end=" ")
    print()

#graph de Wigner
print()
print()
G.gen_Wigner(10)
for i in range(G.n):
    for j in range(G.n):
        print(G.getedje(i,j),end=" ")
    print()
Z=gp.graphs(1)
Z.gen_Wigner(10)
B=G.sub_wigner(Z,0.01)


for i in range(B.n):
    for j in range(B.n):
        print(B.getedje(i,j),end=" ")
    print()

G.sparce_wigner(0.05)
for i in range(G.n):
    for j in range(G.n):
        print(G.getedje(i,j),end=" ")
    print()
print()
print()
####################
#   module matrix  #
####################

#initialisatin de variable martix_0_1
mymatrix=mt.matrix_0_1(10)
#modification de la taille
print(mymatrix.size)
mymatrix.size=20
print(mymatrix.size)
#modification des valeur inter de la matrice
print(mymatrix.getval(19,19))
mymatrix.setval(19,19,5.4)
print(mymatrix.getval(19,19))
#recuperation de la trace de la matrice
print(mymatrix.trace())

##########################
#   Erdos-Renyi standart #
##########################
print()
print()
A=gp.graphs(1)
mymatrix=mt.matrix_0_1(10)
A.gen_rand_sans_poid(10, 0.3)
G1=A.gen_sub_sans_poid(0.99)
G2=A.gen_sub_sans_poid(0.99)


al2.algo_2(mymatrix,G1,G2,2,4)


y=al3.algo_3(mymatrix)

for i in range(len(y)):
    print(i,"=",y[i])
##########################
#   Wigner standart #
##########################
print()
print()
A=gp.graphs(1)
A.gen_Wigner(10, 0.3)
Z=gp.graphs(10)
G1=A.sub_wigner(Z,0.1)
G2=A.sub_wigner(Z,0.1)

al2.algo_2(mymatrix,G1,G2,2,4)

y=al3.algo_3(mymatrix)

for i in range(len(y)):
    print(i,"=",y[i])


##########################
#   Erdos-Renyi Choisi #
##########################
print()
print()
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


A=gp.graphs(1)
A.gen_rand_sans_poid(10, 0.3)
G1=A.gen_sub_sans_poid(0.99)
G2=A.gen_sub_sans_poid(0.99)

al2.algo_2_choice_tree(mymatrix,A,A,2,4,2,normal_erdo,f,v)

y=al3.algo_3(mymatrix)

for i in range(len(y)):
    print(i,"=",y[i])