import tensorcircuit as tc

cir = tc.Circuit(4)
cir.cnot(2, 3)
cir.cnot(1, 2)
cir.cnot(0, 1)
cir.cnot(2, 3)
cir.cnot(1, 2)
cir.cnot(0, 1)

def circuitOutput(cir):
    L = cir.to_qir()
    print(cir._nqubits)
    for gate in L:
        print(gate["gatef"])
        print(len(gate["index"]), end = "")
        for x in gate["index"]: print(" %d" % x, end = "")
        print("")
        # print(gate["index"])
        if "parameters" in gate: # only for rx/ry/rz
            print(gate["parameters"]["theta"])
        else:
            print("0.0")

circuitOutput(cir)
