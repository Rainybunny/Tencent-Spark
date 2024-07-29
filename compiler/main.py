import numpy as np
import transpiler as tp
# from error import get_readout_error,vector_to_dict,get_A,get_Aplus,get_res

# prm, cir = tp.transpile(cir)t

from scipy import linalg as la
import tensorcircuit as tc
from tensorcircuit.cloud import apis
apis.set_provider("local")
import random
import matplotlib.pyplot as plt

n = 9
X = tc.gates._x_matrix
Z = tc.gates._z_matrix
I = np.eye(2)
h0 = np.zeros((2 ** n, 2 ** n))
hp = np.zeros((2 ** n, 2 ** n))
for k in range(n):
    res = np.array([[1]])
    for i in range(n):
        if i == k:
            res = np.kron(res, X)
        else:
            res = np.kron(res, I)
    h0+=res
e = []
def addedge(x, y):
    global hp
    res = np.array([[1]])
    for i in range(n):
        if i == x or i == y:
            res = np.kron(res, Z)
        else:
            res = np.kron(res, I)
    hp += res
    e.append((x, y))
m=11
if n==9:
	m=15
	addedge(0, 1)
	addedge(3, 4)
	addedge(7, 8)
	addedge(2, 5)
	addedge(0, 3)
	addedge(4, 5)
	addedge(6, 7)
	addedge(1, 2)
	addedge(4, 7)
	addedge(5, 8)
	addedge(3, 6)
	addedge(1, 4)
	addedge(0, 8)
	addedge(2, 6)
	addedge(1, 3)
else:
	m=11
	addedge(0, 1)
	addedge(3, 4)
	addedge(2, 5)
	addedge(0, 3)
	addedge(4, 5)
	addedge(1, 2)
	addedge(1, 4)
	addedge(0, 5)
	addedge(2, 3)
	addedge(1, 3)
	addedge(1, 5)
ans=0
RES=[]
for i in range(2**n):
	RES.append(0)
	for x,y in e:
		if (((i>>x)&1)!=((i>>y)&1)):
			RES[i]+=1
	if ans<RES[i]:
		ans=RES[i]
c=tc.Circuit(n)
def RX(k,theta):
    c.rx(k,theta=theta)
def RZZ(x,y,theta):
    c.rzz(x,y,theta=theta)
def calc(tp,T,C):
    global c
    p1=7/24
    q1=2/3
    p2=3/4
    q2=-2/3
    p3=-1/24
    q3=1
    v = np.array([1, -1]) / (2 ** 0.5)
    u = v
    for i in range(n - 1):
        u = np.kron(u, v)
    for i in range(n):
        c.X(i)
        c.H(i)
    if tp==1:
        for k in range(C):
            for i in range(n):
                RX(i,T/C*p1*2)
            for x,y in e:
                RZZ(x,y,T/C*q1*2)
            for i in range(n):
                RX(i,T/C*p2*2)
            for x,y in e:
                RZZ(x,y,T/C*q2*2)
            for i in range(n):
                RX(i,T/C*p3*2)
            for x,y in e:
                RZZ(x,y,T/C*q3*2)
    else:
        for k in range(C):
            for i in range(n):
                RX(i,T/C)
            for x,y in e:
                RZZ(x,y,T/C*2)
            for i in range(n):
                RX(i,T/C)
    u = la.expm(-1j * (h0 + hp) * T) @ u
    print("answer:",(m-np.inner(u.conj().T,hp @ u))/2)

calc(1,n/3-1,5)
per,cir=tp.transpile(c)
# print(c.draw())
# A_plus = get_Aplus(13,0)
#apis.set_token()
res=apis.submit_task(provider="local",device="testing",circuit=cir,shots=1000000).results()
#res=apis.submit_task(provide="tencent",device="tianji_s2",circuit=cir,shots=10000).results()
#res=get_res(13, res, A_plus)
sum=0
Sum=0
for k,v in res.items():
	s=0
	print(k,v)
print(ans,sum,sum/ans,Sum)
