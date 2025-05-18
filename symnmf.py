import sys
import numpy as np
import pandas as pd
import symnmfmodule as cmod

def py_symnmf(points, rows, k):
    np.random.seed(1234)
    W = cmod.norm(points)
    mean = np.sum(W)/(rows*rows)
    H = np.random.uniform(0, 2*np.sqrt(mean/k), (rows, k))
    matrix = cmod.symnmf(k, W, H.tolist())
    return matrix

def processInput(input_data):
    matrix = pd.read_csv(input_data, sep=",", header=None).to_numpy()
    rows = matrix.shape[0]
    cols = matrix.shape[1]
    matrix = matrix.tolist()
    return matrix, rows, cols

def main():
    k = int(sys.argv[1])
    points, rows, cols = processInput(sys.argv[3])

    # Error checking
    if k <= 0 or k >= rows:
        print("An Error Has Occurred")
        exit()

    if sys.argv[2] == "symnmf":
        matrix = py_symnmf(points, rows, k)
    elif sys.argv[2] == "sym":
        matrix = cmod.sym(points)
    elif sys.argv[2] == "ddg":
        matrix = cmod.ddg(points)
    elif sys.argv[2] == "norm":
        matrix = cmod.norm(points)
    else:
        print("An Error Has Occurred")
        exit()

    for point in matrix:
        for cord in point[:-1]:
            print("%.4f" % cord, end=",")
        print("%.4f" % point[-1])

if __name__ == "__main__":
    main()


