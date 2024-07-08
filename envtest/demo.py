from matplotlib import pyplot as plt
import tensorflow as tf
import tensorcircuit as tc

K = tc.set_backend("tensorflow")

n, nlayers = 4, 2
# number of qubits, number of layers


def ladder_layout_circuit(params, pbc=False):
    """
    `params` is for circuit trainable parameters
    """
    c = tc.Circuit(n)
    offset = 0 if pbc else 1
    for j in range(nlayers):
        for i in range(n - offset):
            c.cnot(i, (i + 1) % n)
        for i in range(n):
            c.rx(i, theta=params[j, i])
    return c


## open boundary ladder

ladder_layout_circuit(K.ones(shape=[nlayers, n])).draw(output="mpl")
