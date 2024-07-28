import math
import transpiler as tp
import tensorcircuit as tc

cir = tc.Circuit(2)

cir.x(0)
cir.cnot(0, 1)
cir.cnot(1, 0)
cir.cnot(0, 1)
cir.h(1)
cir.rz(1, theta = math.pi)

ref, cir = tp.transpile(cir)
psi = cir.state()

print(ref)
for z in psi:
    print("%.2f %.2f" % (z.real, z.imag))
