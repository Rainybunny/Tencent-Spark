import tensorcircuit as tc
import tensorflow as tf
import math
import numpy as np
from scipy import linalg as la
import itertools
import qiskit as qk

## transform |x>|y> to |x>|y^f(x)>
def transF(cir: tc.Circuit, is_balanced):
    if is_balanced: cir.CNOT(0, cir._nqubits - 1)
    return cir

def solve(n, is_balanced):
    cir = tc.Circuit(n + 1,
    inputs = np.kron(np.array([0 for _ in range(1 << n)]), np.array([0, 1])))

    for i in range(n + 1): cir.h(i)
    cir = transF(cir, is_balanced)
    for i in range(n): cir.h(i)

    return cir.measure(*[i for i in range(n)], with_prob = True)

n = int(input())
is_balanced = bool(input())
answer = bool(solve(n, is_balanced)[1])
if (is_balanced == answer): print("Success.")
else: print("Wrong.")
