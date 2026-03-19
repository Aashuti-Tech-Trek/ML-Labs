#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

int main() {

    ifstream file("image_output.csv");
    if (!file.is_open()) {
        return -1;
    }

    ofstream out("pca_output.txt");
    if (!out.is_open()) {
        return -1;
    }

    double img[200][200];
    int n = 0, m = 0;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        int col = 0;

        while (getline(ss, value, ',')) {
            img[n][col++] = stod(value);
        }

        if (n == 0) m = col;
        n++;
    }
    file.close();

    out << "Rows (pixels): " << n << endl;
    out << "Columns (features): " << m << endl;

    // Step 1: Mean
    double mean[m] = {0};
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++)
            mean[j] += img[i][j];
        mean[j] /= n;
    }

    // Step 2: Mean-centered
    double centered[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            centered[i][j] = img[i][j] - mean[j];

    // Step 3: Covariance
    double cov[m][m];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cov[i][j] = 0;
            for (int k = 0; k < n; k++)
                cov[i][j] += centered[k][i] * centered[k][j];
            cov[i][j] /= (n - 1);
        }
    }

    out << "\nCovariance Matrix:\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++)
            out << cov[i][j] << " ";
        out << endl;
    }

    // Step 4: Power Iteration
    double eigenVec[m];
    for (int i = 0; i < m; i++)
        eigenVec[i] = 1;

    double eigenVal = 0;

    for (int iter = 0; iter < 100; iter++) {
        double temp[m] = {0};

        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                temp[i] += cov[i][j] * eigenVec[j];

        double norm = 0;
        for (int i = 0; i < m; i++)
            norm += temp[i] * temp[i];
        norm = sqrt(norm);

        for (int i = 0; i < m; i++)
            eigenVec[i] = temp[i] / norm;

        eigenVal = norm;
    }

    out << "\nLargest Eigenvalue:\n" << eigenVal << endl;
    out << "\nCorresponding Eigenvector:\n";
    for (int i = 0; i < m; i++)
        out << eigenVec[i] << " ";
    out << endl;

    out.close();
    return 0;
}
