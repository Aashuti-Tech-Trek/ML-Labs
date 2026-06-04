K-MEANS CLUSTERING — README
by Aashuti Gambhir 2023BCS-001
Date: 29-01-2026

Purpose
-------
This document explains the C++ program `main.cpp` that implements the K-Means clustering algorithm. The program reads one or more datasets from `input.txt`, runs K-Means (printing first-iteration distances and tracking iterations), and writes results to `output.txt`.

1) Definition (Quick) 
- K-Means is an unsupervised clustering algorithm that partitions n data points into K clusters.
- Each cluster is represented by a centroid (the mean of all points assigned to that cluster).
- Objective: Minimize the sum of squared distances between points and their cluster centroids.

2) High-level algorithm (iterative steps) 
1. Initialize K centroids (provided in input).
2. Assignment step: compute Euclidean distance from each point to each centroid and assign the point to the nearest centroid.
3. Update step: recompute each centroid as the mean of the points assigned to it.
4. Repeat steps 2–3 until assignments no longer change (convergence).

3) Mapping the algorithm to the code (key components) 
- Data type:
  - `typedef vector<double> Point;` — a point or centroid in d-dimensional space.

- Distance:
  - `double calcDistance(Point a, Point b)` — computes Euclidean distance: sqrt(sum (a_i - b_i)^2).

- Centroid update:
  - `Point findMean(vector<Point> cluster, int dim)` — sums coordinates of cluster points and divides by cluster size to return the new centroid.

- I/O:
  - `ifstream fin("input.txt");` reads datasets.
  - `ofstream fout("output.txt");` writes iteration details and final clusters.

- Iteration & convergence:
  - The program performs assignment for each point (closest centroid), groups points, computes new centroids, and compares cluster labels with those from the previous iteration.
  - Distances are printed only for iteration 1 (lab requirement).

4) Input format (exact)
- First line: D = number of datasets
- For each dataset:
  - Line: `n dim K`  (n = number of points, dim = dimensionality, K = number of clusters)
  - Next n lines: each line contains `dim` numeric values (point coordinates)
  - Next K lines: each line contains `dim` numeric values (initial centroid coordinates)

Example (this repository's `input.txt`):
```
2
4 1 2
2
4
10
12
2
10
15 2 3
2 20
3 25
4 30
5 35
6 40
8 65
9 70
10 75
11 80
12 85
15 45
16 50
17 55
18 60
19 65
2 20
8 65
15 45
```

5) Output (what the program writes into `output.txt`) 
- For each dataset:
  - Iteration 1 distances: distance from each point to each centroid and the assigned cluster (rounded to two decimals).
  - Centroids after the first iteration.
  - Final clusters and centroids after convergence.

6) Worked examples (explain the lab datasets) 
Dataset 1 (1-D example)
- Data: X = {2, 4, 10, 12}, K = 2, initial centroids: C1=2, C2=10
- Iteration 1 distances and assignments:
  - Point 2  : d(C1)=0,  d(C2)=8  → Cluster 1
  - Point 4  : d(C1)=2,  d(C2)=6  → Cluster 1
  - Point 10 : d(C1)=8,  d(C2)=0  → Cluster 2
  - Point 12 : d(C1)=10, d(C2)=2  → Cluster 2
- Centroids after first iteration: C1=3.00, C2=11.00
- Converged clusters: Cluster 1 = {2,4} ; Cluster 2 = {10,12}

Dataset 2 (2-D example: Income, Score)
- Initial centroids: C1=(2,20), C2=(8,65), C3=(15,45)
- After iteration 1, centroids become approximately:
  - C1 = (3.00, 25.00)
  - C2 = (12.43, 71.43)
  - C3 = (11.80, 45.00)
- Final clusters after convergence (as produced by the program):
  - Cluster 1: (2,20),(3,25),(4,30),(5,35) — centroid ≈ (3.50, 27.50)
  - Cluster 2: (8,65),(9,70),(10,75),(11,80),(12,85),(18,60),(19,65) — centroid ≈ (12.43, 71.43)
  - Cluster 3: (6,40),(15,45),(16,50),(17,55) — centroid ≈ (13.50, 47.50)

7) Implementation notes & corner cases 
- Empty cluster: If a centroid has no assigned points, this implementation leaves the centroid unchanged (no division by zero).
- Precision: Distances are printed with two decimals for readability.
- Convergence: The algorithm stops when assignment labels do not change between iterations.

8) How to compile & run (Windows PowerShell)
- Compile: `g++ -std=c++11 main.cpp -o main`
- Run: `.\main`  (program reads `input.txt` and writes `output.txt` in the same folder)

9) Final remarks
- This implementation matches the K-Means steps taught in class: initialize, assign, update, repeat until convergence.
- The program is easy to extend: change input files to test different datasets, modify printing for more iterations, or add centroid-reinitialization logic for empty clusters.

If you’d like, I can also:
- Create a `README.md` (Markdown) with the same content for nicer display on GitHub 
- Add inline, well-commented annotations to `main.cpp` explaining each code block step-by-step 
Plotting the results
-------------------
A helper script `plot_clusters.py` is included to plot final clusters extracted from `output.txt`:
- Usage examples:
  - `python plot_clusters.py output.txt` — generate PNGs for all datasets (saved as `dataset_<i>_clusters.png`).
  - `python plot_clusters.py output.txt -d 1 --show` — plot dataset 1 and show it interactively.
- Notes: The script supports 1D (points on x axis) and 2D (scatter plot) clusters. For higher dimensions consider using PCA to reduce to 2D first.
End of README.
