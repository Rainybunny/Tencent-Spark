import tensorcircuit as tc
import tensorflow as tf
import numpy as np
import scipy as sc
import matplotlib.pyplot as plt

Z = tc.gates._z_matrix

cir = tc.Circuit(2)
cir.H(0)
cir.CNOT(0, 1)

psi = cir.state("ket")
rho = np.outer(psi.conj().T, psi)
print(np.trace(rho @ np.kron(Z, Z)))
