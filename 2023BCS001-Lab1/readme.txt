Lab 1 — README (Plain Text)
By Aashuti Gambhir (2023BCS-001)

Overview:
This lab demonstrates a complete end-to-end implementation of Principal Component Analysis (PCA) on a grayscale image using a Python + C++ pipeline.

The workflow is:

1. Read a grayscale image

2. Convert the image matrix into CSV format using Python

3. Read the CSV in C++

4. Perform mean centering

5. Compute the covariance matrix

6. Compute the largest eigenvalue and corresponding eigenvector using Power Iteration

7. Save all PCA results to a text file

8. The default working image size is 200 × 200 pixels to keep computation feasible and fast.

Objective:

1. Understand how image data can be treated as numerical feature matrices

2. Implement PCA from scratch without using external math libraries

3. Learn covariance matrix computation and eigenvalue estimation

4. Understand dimensionality reduction concepts used in Machine Learning

Files and Their Purpose:

1. convert.py

-Python preprocessing script

-Reads image.png in grayscale

-Resizes image to 200 × 200 pixels

-Saves pixel matrix as image_output.csv

2. main.cpp

-C++ implementation of PCA

-Reads image_output.csv

Computes:

Mean of each feature
Mean-centered data
Covariance matrix
Largest eigenvalue and eigenvector using Power Iteration
Writes results to pca_output.txt

3. image_output.csv

Intermediate data file
Contains pixel intensity values
Each row represents one image row
Each column represents a feature (pixel position)

4. pca_output.txt

Final PCA output file

Contains:

-Number of rows and columns
-Full covariance matrix
-Largest eigenvalue
-Corresponding eigenvector

Prerequisites:

1. Software:

Python 3.x
C++ compiler
MinGW (g++) OR
Microsoft Visual C++ (MSVC)

Python libraries:
numpy
opencv-python

Install Python dependencies using:
pip install numpy opencv-python

# Execution Steps:

Step 1: Image Preparation

Place the image file in the same folder as convert.py

Rename it to image.png
(or update the filename inside convert.py)

Step 2: Convert Image to CSV
Run:
python convert.py

Expected result:

Image is resized to 200 × 200
File image_output.csv is generated
Console prints original and resized image dimensions

Step 3: Compile the C++ PCA Program

Using g++:
g++ main.cpp -O2 -std=c++11 -o pca.exe

Using MSVC:
cl /EHsc /O2 main.cpp /Fe:pca.exe

Step 4: Run PCA
pca.exe

Expected result:

Program runs silently
File pca_output.txt is created with PCA results

Output Description (pca_output.txt):

The output file contains:
Number of samples (rows)
Number of features (columns)
Covariance matrix (square matrix of size m × m)
Largest eigenvalue (principal component magnitude)
Corresponding eigenvector (principal direction)
This eigenvector represents the direction of maximum variance in the image data.

Technical Notes:

PCA is implemented manually (no Eigen / LAPACK / OpenCV PCA used).
Power Iteration is used to find only the dominant eigenvalue, which is sufficient for first principal component analysis.
Image resizing is required to avoid excessive computation and memory usage.
For an image of size N × N, covariance computation is O(N³).

Common Issues and Fixes:

-Program runs but shows no output
-Output is written to pca_output.txt, not console.
-Program is very slow or appears stuck
-Reduce image size in convert.py
-Ensure resize dimensions match static array sizes in main.cpp
-“File not found” error
-Ensure image_output.csv exists
-Ensure correct working directory
-OpenCV include error in C++
-Not related to this PCA program
-Occurs only when compiling C++ files that use OpenCV
-Install OpenCV and configure include/lib paths if needed

Learning Outcomes:

After completing this lab, you will understand:

-How PCA works mathematically
-How images can be treated as feature matrices
-How covariance captures variance relationships
-How eigenvectors represent principal directions
-Why dimensionality reduction is essential in ML

Possible Extensions:

Change resize dimension to 100 × 100 for faster execution
Save eigenvector to CSV
Project data onto the first principal component
Compute multiple eigenvectors using deflation
Replace static arrays with dynamic memory allocation
Add timing analysis for covariance computation