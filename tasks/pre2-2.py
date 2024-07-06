import tensorcircuit as tc
import tensorflow as tf
import math
import numpy as np
import scipy as sc

X, Y, Z = tc.gates._x_matrix, tc.gates._y_matrix, tc.gates._z_matrix

def subtask1():
    for P in [X, Y, Z]:
        print("---")
        print(np.exp(np.dot(1j, P)))

def subtask2()->bool:
    I = np.eye(2)
    for P in [X, Y, Z]:
        for id in range(100):
            theta = np.random.random() * np.pi * 2
            L = sc.linalg.expm(P * (1j * theta))
            R = I * np.cos(theta) + P * (1j * np.sin(theta))
            if not np.allclose(L, R, atol = 1e-8):
                print(f"Error when {P=}\n{theta=}\n{L=}\n{R=}\n")
                return False
    print("Test Succeeded.")
    return True


if __name__ == "__main__":
    # subtask1()
    assert(subtask2())