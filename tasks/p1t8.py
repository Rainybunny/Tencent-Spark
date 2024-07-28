import numpy as np
import tensorcircuit as tc
from matplotlib import pyplot as plt

def halfAdder(cir, a, b: bool, carry):
    if b:
        cir.cnot(a, carry)
        cir.x(a)

def fullAdder(cir, a, b: bool, x, carry):
    if b:
        cir.cnot(a, carry)
        cir.cnot(x, carry)
    cir.toffoli(a, x, carry) # carry <- (a\land b) \lor (...) \lor (...)

    cir.cnot(x, a)
    if b: cir.x(a) # a <- a xor b xor x

def adderConstruct(n, A, C):
    cir = tc.Circuit(2 * n - 1,
                     A + [0 for _ in range((1 << 2 * n - 1) - (1 << n))])
    print(cir.state())
    # n+i is the carry bit for i

    halfAdder(cir, 0, C[0], n)
    if n == 1: return cir

    for i in range(1, n - 1):
        fullAdder(cir, i, C[i], n + i - 1, n + i)
    cir.cnot(2 * n - 2, n - 1)
    if C[n - 1]: cir.x(n - 1)
    return cir

print("input format:\nn\nC (01 string)\nA (binary id)")
n = int(input())
C = [c == '1' for c in input()]
ket = int(input(), base = 2)
A = [0 for _ in range(1 << n)]
A[ket] = 1
cir = adderConstruct(n, A, C)

print(cir.state())

cir.draw(output = 'mpl')
plt.show()
