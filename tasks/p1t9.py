import numpy as np
import tensorcircuit as tc
from matplotlib import pyplot as plt

N = 12 # super bad
ONE = 3 # constant \ket 1
cir = tc.Circuit(N)

def or3(x, y, z, res):
    ary = [x, y, z]
    for a in ary:
        cir.toffoli(ONE, a, res)
    for i in range(3):
        for j in range(i + 1, 3):
            cir.toffoli(i, j, res)

def and3(x, y, z, res):
    # # May simply use or3; or...
    # cir.x(x); cir.x(y); cir.x(z)
    # or3(x, y, z, res); cir.x(res)
    # cir.x(z); cir.x(y); cir.x(x)
    cir.toffoli(x, y, res)
    cir.toffoli(res, z, x)
    cir.toffoli(res, z, y)
    cir.toffoli(x, y, res)
    cir.toffoli(ONE, res, x)
    cir.toffoli(ONE, res, y)

def oracle():
    cir.toffoli(0, 1, 4)


