import tensorcircuit as tc
import tensorflow as tf
import math
import numpy as np
import scipy as sc

X, Y, Z = tc.gates._x_matrix, tc.gates._y_matrix, tc.gates._z_matrix
Plist = [X, Y, Z]

def calc(P, Q, theta)->float:
    v0 = np.array([[1], [0]])
    v = sc.linalg.expm(P * (0.5j * theta)) @ v0
    return sc.linalg.dagger(v) @ Q @ v

if __name__ == "__main__":
    i, j, theta = input().split(' ')
    i, j, theta = int(i), int(j), float(theta)
    P = Plist[i]
    Q = Plist[j]
    print(calc(P, Q, theta))
