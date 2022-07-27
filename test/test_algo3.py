#!/usr/bin/python3
import algo3
import matrix
import random 
mymatrix=matrix.matrix_0_1(10)
for i in range(10):
    for j in range(10):
        mymatrix.setval(i,j,random.uniform(0,150))
for i in range(10):
    for j in range(10):
        print(mymatrix.getval(i,j),end=" ")
    print()
y=algo3.algo_3(mymatrix)
for i in range(10):
    print(i,"=",y[i])

