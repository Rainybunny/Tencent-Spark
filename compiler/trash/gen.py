import tensorcircuit as tc

cir = tc.Circuit(13)
for i in range(12):
    for j in range(i + 1, 13):
        cir.cnot(i, j)

def circuitOutput(cir):
    L = cir.to_qir()
    # print(cir._nqubits)
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