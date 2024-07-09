import tensorcircuit as tc
import tensorflow as tf
import numpy as np
import scipy as sc
import matplotlib.pyplot as plt

X, Z = tc.gates._x_matrix, tc.gates._z_matrix
n = int(input())

H = np.zeros((1 << n, 1 << n), dtype = complex)

for i in range(n):
    H += np.kron(np.kron(np.eye(1 << i), Z), np.eye(1 << n - i - 1))

# I'm not sure for this.
for i in range(n - 1):
    H += np.kron(np.kron(np.kron(np.eye(1 << i), X), X), np.eye(1 << n - i - 2))

print(H)

v = np.zeros((1 << n, 1), dtype = complex)
v[0][0] = 1
print((v.conj().T @ H @ v)[0][0])
