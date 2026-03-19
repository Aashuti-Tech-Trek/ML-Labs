#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ifstream fin("input2.txt");
    ofstream fout("output2.txt");

    if (!fin) {
        cout << "Error opening input file!" << endl;
        return 0;
    }

    int n, c;
    fin >> n;       
    fin >> c;       

    vector<double> X(n);
    for (int i = 0; i < n; i++)
        fin >> X[i];

    vector<vector<double>> U(n, vector<double>(c));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < c; j++)
            fin >> U[i][j];

    double m = 2.0;  

    vector<double> centers(c, 0.0);

    for (int j = 0; j < c; j++) {
        double numerator = 0.0;
        double denominator = 0.0;

        for (int i = 0; i < n; i++) {
            double weight = pow(U[i][j], m);
            numerator += weight * X[i];
            denominator += weight;
        }

        centers[j] = numerator / denominator;
    }
    fout << fixed << setprecision(4);
    fout << "Cluster Centers:\n";
    for (int j = 0; j < c; j++)
        fout << "Cluster " << j + 1 << " Center = " << centers[j] << "\n";

    fout << "\nOverlapping Data Points:\n";

    bool foundOverlap = false;
    for (int i = 0; i < n; i++) {
        if (abs(U[i][0] - U[i][1]) < 0.1) {
            fout << X[i] << " ";
            foundOverlap = true;
        }
    }

    if (!foundOverlap) {
        fout << "None";
    }

    fout << endl;

    fin.close();
    fout.close();

    cout << "FCM results written to output.txt" << endl;
    return 0;
}
