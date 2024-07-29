import numpy as np
import transpiler as tp
from scipy import linalg as la
import tensorcircuit as tc
from tensorcircuit.cloud import apis
apis.set_provider("local")
import random
import matplotlib.pyplot as plt

n = 9
v = np.array([1, -1]) / (2 ** 0.5)
u = v
for i in range(n - 1):
    u = np.kron(u, v)
c = tc.Circuit(n,inputs=u)
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
T=200
def RX(k,theta):
    c.rx(k,theta=theta)
def RZZ(x,y,theta):
    c.rzz(x,y,theta=theta)
for i in range(n):
    RX(i,T)
for x,y in e:
    RZZ(x,y,T*2)
for i in range(n):
    RX(i,T)
u=c.state()

c.draw(output = 'mpl')
plt.show()

print(np.inner(u.conj().T,hp @ u))
#u = la.expm(-1j * (h0 + hp) * T) @ u
#print(np.inner(u.conj().T,hp @ u))
# prm,cir=tp.transpile(c, saveLog = True)


prm,cir = tp.transpile(c, True)

# print(cir.state())
# print(np.inner())
cir.draw(output = 'mpl')
plt.show()
