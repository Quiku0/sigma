#!/usr/bin/python3
import graph
import math as mth

mygraph=graph.graphs(p=0.4,n=10)
print(mygraph.p)
n=mygraph.n
print(n)
mygraph.setedje(1,1,1)
print("bonjour")
print(mygraph.getedje(1,1))
mygraph.n=20
print(mygraph.n)
print(mygraph.p)
mygraph.gen_rand_sans_poid(10,0.4)
print(mygraph.n)
print(mygraph.p)
for i in range(5):
    for j in range(5):
        print(mygraph.getedje(i,j),end=" ")
    print()
graphe=mygraph.gen_sub_sans_poid(0.5)
print(dir(mygraph),"\n")
print(dir(graphe))
print(mygraph.__str__)
print(graphe.__class__)
print(graphe.n)
print(graphe.p)
for i in range(10):
    for j in range(10):
        print(graphe.getedje(i,j),end=" ")
    print()
print()
graph2=mygraph.gen_sub_sans_poid(0.5)
for i in range(10):
    for j in range(10):
        print(graph2.getedje(i,j),end=" ")
    print()
mygraph.gen_Wiger(9,0.4)
print()
for i in range(9):
    for j in range(9):
        print(mygraph.getedje(i,j),end=" ")
    print()
print()
Z=graph.graphs(1,0)
Z.gen_Wiger(9,0.4)
A=mygraph.sub_wiger(Z,0.1)
for i in range(9):
    for j in range(9):
        print(A.getedje(i,j),end=" ")
    print()
print()
Z.gen_Wiger(9,0.4)
B=mygraph.sub_wiger(Z,0.1)
for i in range(9):
    for j in range(9):
        print(B.getedje(i,j),end=" ")
    print()
mygraph.sparce_wiger(0.2*mth.sqrt(mth.log(9)/9))
print()
for i in range(9):
    for j in range(9):
        print(mygraph.getedje(i,j),end=" ")
    print()
print(mygraph.deg(1))
print(mygraph.deg(1))
print(graph.graphs.deg.__doc__)