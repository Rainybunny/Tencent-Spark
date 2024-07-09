import tensorcircuit as tc
import tensorflow as tf
import numpy as np
import scipy as sc
import matplotlib.pyplot as plt

from tensorcircuit.cloud import apis
apis.set_provider("local")

Z = tc.gates._z_matrix

cir = tc.Circuit(2)
cir.H(0)
cir.CNOT(0, 1)

N = 1024
res = apis.submit_task(circuit = cir, device = "testing", shots = N).results()

expc = 0
for str, cnt in res.items():
    print(f"{str=} {cnt=}")
    if str == '00' or str == '11':
        expc += cnt
    else:
        expc -= cnt
expc /= N
print(expc)
