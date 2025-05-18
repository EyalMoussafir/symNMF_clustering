import sys
import kmeans as km
import symnmf as nmf
import numpy as np
from sklearn.metrics import silhouette_score

def main():
    k = int(sys.argv[1])
    points, rows, cols = nmf.processInput(sys.argv[2])
    iter = 300
    eps = 1e-4

    # Error checking
    if k <= 0 or k >= rows:
        print("An Error Has Occurred")
        exit()

    symnmf_matrix = nmf.py_symnmf(points, rows, k)
    symnmf_labels = [np.argmax(row) for row in np.array(symnmf_matrix)]

    centroids = km.py_kmeans(points, k, iter, eps)
    kmeans_labels = [km.min_distance(centroids, point) for point in points]

    print("nmf: %.4f" % silhouette_score(points, symnmf_labels))
    print("kmeans: %.4f" % silhouette_score(points, kmeans_labels))

if __name__ == "__main__":
    main()




