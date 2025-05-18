import math
import sys

# Calculate distance between a centeroid and a point
def distance(centroid, point):
    sum = 0
    for i in range(len(centroid)):
        sum += (centroid[i] - point[i]) ** 2
    return math.sqrt(sum)

# Find the index of the centroid closest to the given point
def min_distance(centroids, point):
    distances = [distance(centroid, point) for centroid in centroids]
    return distances.index(min(distances))

# Find the maximum distance between current centroids and the updated centroids
def max_distance(centroids, mean_centroids):
    distances = [distance(centroids[i], mean_centroids[i]) for i in range(len(centroids))]
    return max(distances)

# Assign each points to a clusters
def make_clusters(centroids, points, k):
    clusters = [[] for i in range(k)]
    for point in points:
        index = min_distance(centroids, point)
        clusters[index].append(point)
    return clusters

# Update centroids to the means of the clusters
def update_centroids(k, clusters):
    centroids = [[] for i in range(k)]
    for i in range(k):
        centroids[i] = mean(clusters[i])
    return centroids

# Calculate the mean of a cluster
def mean(cluster):
    if len(cluster) == 0:
        return []
    mean = []
    for i in range(len(cluster[0])):
        sum = 0
        for j in range(len(cluster)):
            sum += cluster[j][i]
        mean.append(float(sum / len(cluster)))
    return mean

# Kmeans algorithm
def py_kmeans(points, k, iter, eps):
    # Centroids first initialization
    centroids = []
    for i in range(k):
        centroids.append(points[i].copy())

    # Loop to update clusters and centroids
    for i in range(iter):
        clusters = make_clusters(centroids, points, k)
        mean_centroids = update_centroids(k, clusters)
        if max_distance(centroids, mean_centroids) < eps:
            centroids = mean_centroids
            break
        centroids = mean_centroids
    return centroids

def main():
    k = int(sys.argv[1])

    if len(sys.argv) == 3:
        iter = 300
        input_data = sys.argv[2]
    else:
        iter = int(sys.argv[2])
        input_data = sys.argv[3]

    # Read the points from file
    points = []
    with open(input_data, "r") as file:
        for line in file:
            points.append([float(x) for x in line.split(',')])

    # Error checking 2
    if k < 2 or k > len(points) - 1:
        print("Invalid number of clusters!")
        exit()
    if not isinstance(iter, int) or iter < 2 or iter > 999:
        print("Invalid maximum iteration!")
        exit()

    centroids = py_kmeans(points, k, iter, 1e-4)

    # Print the final centroids
    for centroid in centroids:
        for cord in centroid[:-1]:
            print("%.4f" % cord, end=",")
        print("%.4f" % centroid[-1])

if __name__ == "__main__":
    main()






