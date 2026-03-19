EXPECTATION–MAXIMIZATION (EM) ALGORITHM
Gaussian Mixture Model (1-D, K=2)
BY: Aashuti Gambhir(2023BCS-001)

Course: Machine Learning
Language Used: C++
Input File: input.txt
Output File: output.csv

1. PROBLEM STATEMENT

We are given 1-D datasets assumed to be generated from a 
mixture of two Gaussian distributions (K = 2).

We need to implement the Expectation–Maximization (EM) 
algorithm to estimate:

• Mixing coefficients (π1, π2)
• Means (μ1, μ2)
• Variances (σ1², σ2²)

-----------------------------------------------------------

QUESTION 1:
Dataset: X = {1, 2, 8, 9}
Initial Parameters:
π1 = 0.5, π2 = 0.5
μ1 = 2, μ2 = 8
σ1² = 1, σ2² = 1

-----------------------------------------------------------

QUESTION 2:
Dataset: X = {2, 3, 4, 10, 11, 12}
Initial Parameters:
π1 = 0.5, π2 = 0.5
μ1 = 3, μ2 = 11
σ1² = 1, σ2² = 1

2. WHAT IS EM ALGORITHM?

Expectation–Maximization (EM) is an iterative algorithm used 
to estimate parameters of probabilistic models when data has 
hidden variables.

In Gaussian Mixture Model (GMM), the hidden variable is:
Which cluster each data point belongs to.

EM works in two steps:

1. E-Step (Expectation)
2. M-Step (Maximization)

These two steps repeat until convergence.

3. MATHEMATICAL FORMULATION

Gaussian Probability Density Function:

N(x | μ, σ²) = 
(1 / sqrt(2πσ²)) * exp( - (x - μ)² / (2σ²) )

-----------------------------------------------------------

E-STEP:

Compute responsibility γik:

γik = 
πk * N(xi | μk, σk²)
----------------------------------------
Σj πj * N(xi | μj, σj²)

This gives probability that xi belongs to cluster k.

-----------------------------------------------------------

M-STEP:

Compute:

Nk = Σi γik

Updated Mean:
μk = (1 / Nk) Σi γik xi

Updated Variance:
σk² = (1 / Nk) Σi γik (xi − μk)²

Updated Mixing Coefficient:
πk = Nk / n

-----------------------------------------------------------

These steps repeat for given number of iterations.

4. ALGORITHM STEPS (CODE LOGIC)

Step 1:
Read input from input.txt

Step 2:
Initialize:
- Mixing coefficients
- Means
- Variances

Step 3:
Repeat for given iterations:

   ----- E STEP -----
   For each data point:
       Compute Gaussian probability
       Compute responsibility γ

   ----- M STEP -----
   For each cluster:
       Compute Nk
       Update mean
       Update variance
       Update mixing coefficient

Step 4:
Store updated parameters in output.csv

Step 5:
Repeat until convergence.

5. RESULTS ANALYSIS

QUESTION 1

Final Output:

Mean1 = 1.5
Variance1 = 0.25
π1 = 0.5

Mean2 = 8.5
Variance2 = 0.25
π2 = 0.5

-----------------------------------------------------------

Explanation:

Dataset: {1, 2, 8, 9}

Clearly two clusters:
Cluster 1 → {1, 2}
Cluster 2 → {8, 9}

Mean of first cluster:
(1 + 2) / 2 = 1.5

Variance:
[(1−1.5)² + (2−1.5)²] / 2
= (0.25 + 0.25) / 2
= 0.25

Similarly for second cluster:
Mean = 8.5
Variance = 0.25

Since clusters are perfectly separated,
EM converges immediately and parameters
do not change after first iteration.


QUESTION 2

Final Output:

Mean1 = 3
Variance1 = 0.666667
π1 = 0.5

Mean2 = 11
Variance2 = 0.666667
π2 = 0.5

-----------------------------------------------------------

Explanation:

Dataset: {2, 3, 4, 10, 11, 12}

Two natural clusters:

Cluster 1 → {2, 3, 4}
Cluster 2 → {10, 11, 12}

Mean of cluster 1:
(2 + 3 + 4) / 3 = 3

Variance:
[(2−3)² + (3−3)² + (4−3)²] / 3
= (1 + 0 + 1) / 3
= 0.6667

Mean of cluster 2:
(10 + 11 + 12) / 3 = 11

Variance:
= 0.6667

Again, clusters are well separated.
EM converges quickly and parameters stabilize.

6. WHY PARAMETERS DO NOT CHANGE AFTER ITERATION 1?

Because:

• Initial means are already close to true clusters.
• Data is clearly separated.
• Responsibilities become either 0 or 1.
• Hard clustering happens automatically.

Thus, algorithm converges in first iteration.

7. CONCLUSION

• EM successfully estimated parameters of two Gaussian clusters.
• For both datasets, convergence was very fast.
• When clusters are well separated, EM stabilizes quickly.
• Mixing coefficients remained 0.5 because both clusters
  have equal number of points.

This implementation works for:
- Any 1-D dataset
- Any number of iterations
- K = 2 Gaussian components
