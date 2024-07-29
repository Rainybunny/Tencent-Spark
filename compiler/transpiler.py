import sys
import os
import tensorcircuit as tc
import subprocess as sp

def circuitOutput(cir, outf = sys.stdout):
    L = cir.to_qir()
    # print(cir._nqubits)
    for gate in L:
        print(gate["gatef"], file = outf)
        print(len(gate["index"]), end = "", file = outf)
        for x in gate["index"]:
            print(" %d" % x, end = "", file = outf)
        print("", file = outf)
        # print(gate["index"])
        if "parameters" in gate: # only for rx/ry/rz
            print(gate["parameters"]["theta"], file = outf)
        else:
            print("0.0", file = outf)

def transpile(cir: tc.Circuit, saveLog = False):
    RAW_FILE = './.raw_circuit'
    NEW_FILE = './.new_circuit'

    R_OUT = open(RAW_FILE, 'w')
    circuitOutput(cir, R_OUT)
    R_OUT.close()

    MAPPING_EXECUTABLE = './mapping'
    M_IN = open(RAW_FILE, 'r')
    M_OUT = open(NEW_FILE, 'w')

    proc = sp.Popen(
        [MAPPING_EXECUTABLE],
        stdin = M_IN, stdout = M_OUT
    )
    assert(not proc.wait())
    M_IN.close(), M_OUT.close()

    PHYQUBIT_NUM = 13
    res = tc.Circuit(PHYQUBIT_NUM)

    RES_IN = open(NEW_FILE, 'r')
    lines = RES_IN.readlines()
    lines = [line.strip() for line in lines]
    RES_IN.close()

    prm = list(map(int, lines[0].split()))
    for i in range(1, len(lines), 2):
        # print(lines[i], args, file = sys.stderr)
        if lines[i] == "rz":
            args = list(map(float, lines[i + 1].split()))
            theta = args.pop()
            args = list(map(int, args)) # ...ugly
            res.rz(*args, theta = theta)
        else:
            args = list(map(int, lines[i + 1].split()))
            getattr(res, lines[i])(*args)

    if not saveLog:
        os.remove(RAW_FILE)
        os.remove(NEW_FILE)

    return prm, res
