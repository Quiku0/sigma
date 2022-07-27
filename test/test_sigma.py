from turtle import shape
import sigmaV1
import numpy as np
def normal_erdo(A,i):
    if (sum(A[i])<A.shape[1]*0.3) :
        return 0
    else :
        return 1
def f(graph_util,liste):
    retour=0
    for i in liste:
        retour+=sum(A[i])-A.shape[1]*0.3-1
    return retour
def v(graph_util,liste):
    retour=len(liste)*A.shape[1]*0.3*(1-0.3)
    return retour
A=np.zeros((10,10))
A[0,7]=1
A[7,0]=1

A[1,7]=1
A[7,1]=1
A[1,8]=1
A[8,1]=1

A[2,3]=1
A[3,2]=1
A[2,4]=1
A[4,2]=1
A[2,9]=1
A[9,2]=1

A[3,6]=1
A[6,3]=1
A[3,7]=1
A[7,3]=1

A[5,6]=1
A[6,5]=1
A[5,7]=1
A[7,5]=1
A[5,8]=1
A[8,5]=1

A[6,7]=1
A[7,6]=1

A[8,9]=1
A[9,8]=1
print(A)


y=sigmaV1.sigma(A,A,2)
for i in range(len(y)):
    print(i,"=",y[i])
print()
y=sigmaV1.sigma(A,A,2,0.3,2,normal_erdo,f,v)
for i in range(len(y)):
    print(i,"=",y[i])