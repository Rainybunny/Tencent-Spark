import tensorcircuit as tc
import tensorflow as tf
import numpy as np
import scipy as sc
import matplotlib.pyplot as plt

def krpow(M, n):
    R = M
    for _ in range(n - 1): R = np.kron(R, M)
    return R

X, Z = tc.gates._x_matrix, tc.gates._z_matrix
n = int(input())
