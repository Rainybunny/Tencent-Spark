import tensorcircuit as tc
import tensorflow as tf
import numpy as np
import scipy as sc
import matplotlib.pyplot as plt

X, Y, Z = tc.gates._x_matrix, tc.gates._y_matrix, tc.gates._z_matrix
M = [X, Y, Z]
P, Q = X, X

def calc(theta):
    v0 = np.array([[1], [0]])
    v = sc.linalg.expm(P * (0.5j * theta)) @ v0
    return (np.conj(v).T @ Q @ v)[0][0]

plt.figure()

N = 256
x = np.linspace(-np.pi, np.pi, N, endpoint = True)
y = [[[] for _ in range(3)] for _ in range(3)]
MI = [2]
MJ = [0, 1]
for i in MI:
    for j in MJ:
        P, Q = M[i], M[j]
        for theta in x:
            y[i][j].append(calc(theta))
        plt.plot(x, y[i][j], label = f"({i},{j})")

# plt.plot(x, np.sin(x), label = 'sin(x)')
# plt.plot(x, np.cos(x), label = 'cos(x)')
plt.legend()
plt.grid(True)
plt.show()
