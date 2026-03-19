#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double gaussian(double x, double mean, double variance) {
    double coeff = 1.0 / sqrt(2 * M_PI * variance);
    double exponent = exp(-((x - mean) * (x - mean)) / (2 * variance));
    return coeff * exponent;
}

int main() {
    ifstream fin("input1.txt");
    ofstream fout("output1.csv");

    if (!fin) {
        cout << "Error opening input file!" << endl;
        return 0;
    }

    int n;
    fin >> n;

    vector<double> X(n);
    for (int i = 0; i < n; i++)
        fin >> X[i];

    int K;
    fin >> K;

    vector<double> pi(K), mu(K), var(K);

    for (int i = 0; i < K; i++)
        fin >> pi[i];

    for (int i = 0; i < K; i++)
        fin >> mu[i];

    for (int i = 0; i < K; i++)
        fin >> var[i];

    int maxIterations;
    fin >> maxIterations;

    vector<vector<double>> gamma(n, vector<double>(K));

    const double epsilon = 1e-6;

    fout << "Iteration,Cluster,Mean,Variance,MixingCoefficient\n";

    for (int iter = 0; iter < maxIterations; iter++) {

        vector<double> old_mu = mu;
        vector<double> old_var = var;
        vector<double> old_pi = pi;

        for (int i = 0; i < n; i++) {
            double denom = 0;

            for (int k = 0; k < K; k++) {
                gamma[i][k] = pi[k] * gaussian(X[i], mu[k], var[k]);
                denom += gamma[i][k];
            }

            for (int k = 0; k < K; k++) {
                gamma[i][k] /= denom;
            }
        }

        for (int k = 0; k < K; k++) {

            double Nk = 0;
            double newMean = 0;
            double newVar = 0;

            for (int i = 0; i < n; i++) {
                Nk += gamma[i][k];
                newMean += gamma[i][k] * X[i];
            }

            newMean /= Nk;

            for (int i = 0; i < n; i++) {
                newVar += gamma[i][k] * pow(X[i] - newMean, 2);
            }

            newVar /= Nk;

            pi[k] = Nk / n;
            mu[k] = newMean;
            var[k] = newVar;

            fout << iter + 1 << ","
                 << k + 1 << ","
                 << mu[k] << ","
                 << var[k] << ","
                 << pi[k] << "\n";
        }

        bool converged = true;

        for (int k = 0; k < K; k++) {
            if (fabs(mu[k] - old_mu[k]) > epsilon ||
                fabs(var[k] - old_var[k]) > epsilon ||
                fabs(pi[k] - old_pi[k]) > epsilon) {
                converged = false;
                break;
            }
        }

        if (converged) {
            cout << "Algorithm converged at iteration "
                 << iter + 1 << endl;
            break;
        }
    }

    fout.close();
    cout << "EM Algorithm Completed. Results saved in output.csv\n";

    return 0;
}
