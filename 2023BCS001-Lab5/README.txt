
ML LAB ASSIGNMENT
FUZZY C-MEANS CLUSTERING
BY AASHUTI GAMBHIR (2023BCS-001)


1. AIM
------
To implement the Fuzzy C-Means (FCM) clustering algorithm and apply it on given datasets
to compute cluster centers, identify overlapping data points, and analyze cluster separation.


2. THEORY / CONCEPTS
-------------------

Clustering is an unsupervised learning technique used to group similar data points.
Unlike K-Means clustering, which assigns each data point to exactly one cluster,
Fuzzy C-Means (FCM) allows a data point to belong to multiple clusters with different
degrees of membership.

In FCM:
- Each data point has a membership value between 0 and 1 for every cluster.
- The sum of membership values for a data point is equal to 1.
- This approach is useful when cluster boundaries are not clearly defined.


3. IMPORTANT TERMS
------------------

1. Number of clusters (c):
   The total number of clusters to be formed.

2. Fuzziness parameter (m):
   Controls the level of fuzziness in clustering.
   - m > 1
   - m = 2 is commonly used.
   Higher value of m results in more overlap between clusters.

3. Membership matrix (U):
   A matrix where U[i][j] represents the degree of membership of the i-th data point
   in the j-th cluster.


4. OBJECTIVE FUNCTION OF FUZZY C-MEANS
-------------------------------------

The objective function minimized by FCM is:

Jm = Σ Σ (u_ij)^m ||x_i − v_j||²
     i   j

Where:
- u_ij is the membership of data point x_i in cluster j
- m is the fuzziness parameter
- v_j is the center of cluster j
- x_i is the i-th data point

This function:
- Penalizes large distances between points and cluster centers
- Penalizes incorrect membership assignments
- Allows smooth cluster boundaries


5. CLUSTER CENTER FORMULA
------------------------

Cluster centers are calculated using:

v_j = [ Σ (u_ij)^m x_i ] / [ Σ (u_ij)^m ]

This formula computes a weighted mean, where data points with higher membership
values have more influence on the cluster center.


6. QUESTION 1 SUMMARY
--------------------

Dataset: {2, 4, 6, 8}
Number of clusters: 2
Fuzziness parameter: m = 2

Computed cluster centers:
- Cluster 1 center ≈ 3.33
- Cluster 2 center ≈ 6.67

Interpretation:
- Lower values belong more to Cluster 1
- Higher values belong more to Cluster 2
- Data points 4 and 6 show overlapping membership


Differences between K-Means and Fuzzy C-Means:
1. K-Means uses hard assignment, FCM uses soft assignment.
2. K-Means assigns a point to one cluster only, FCM allows overlap.


7. QUESTION 2 SUMMARY
--------------------

Dataset:
{12, 15, 18, 22, 25, 48, 52, 55, 58, 60}

"Similar to Table 1" means:
- Smaller values have higher membership in Cluster 1
- Larger values have higher membership in Cluster 2
- Boundary values have nearly equal membership

Computed cluster centers:
- Cluster 1 center ≈ 22
- Cluster 2 center ≈ 55

Overlapping data points:
- 22, 25 (and slightly 48)

Cluster separation:
- Clear separation between smaller and larger values
- Minimal overlap near boundary
- FCM effectively models uncertainty


8. CODE EXPLANATION
-------------------

The C++ program implements the Fuzzy C-Means algorithm using file input and output.

Main steps in the code:

1. Reads input from input2.txt:
   - Number of data points
   - Number of clusters
   - Dataset values
   - Initial membership matrix

2. Uses fuzziness parameter m = 2.

3. Computes cluster centers using the standard FCM weighted average formula.

4. Identifies overlapping data points by checking if the difference between
   membership values of two clusters is less than 0.1.

5. Writes the following to output2.txt:
   - Cluster centers
   - Overlapping data points (or 'None' if no overlap exists)

The code ensures proper file handling and produces clean, complete output
suitable for ML lab submission.


9. CONCLUSION
-------------

Fuzzy C-Means clustering is an effective soft clustering technique that allows
data points to belong to multiple clusters with varying degrees of membership.
Compared to K-Means, FCM provides more realistic clustering results when data
contains uncertainty or overlapping boundaries.
