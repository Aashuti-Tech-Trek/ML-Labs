#include <iostream>
#include <cmath>
using namespace std;

const int N = 8;   
const int M = 4;   

double mean(double X[N][M], int col) {
    double sum = 0;
    for (int i = 0; i < N; i++)
        sum += X[i][col];
    return sum / N;
}
double stddev(double X[N][M], int col, double mu) {
    double sum = 0;
    for (int i = 0; i < N; i++)
        sum += (X[i][col] - mu) * (X[i][col] - mu);
    return sqrt(sum / N);
}

int main() {
    double X[N][M] = {
        {1, 450, 120, 1.2},
        {1, 520, 135, 1.8},
        {1, 610, 150, 2.5},
        {1, 580, 148, 2.2},
        {1, 490, 130, 1.5},
        {1, 720, 170, 3.1},
        {1, 680, 165, 2.9},
        {1, 640, 155, 2.6}
    };

    double y[N] = {210, 245, 310, 295, 235, 360, 345, 325};

    double theta[M] = {0, 0, 0, 0};

       //PART 1: WITHOUT FEATURE SCALING
    double alpha = 1e-7;
    int iterations = 5000;

    for (int it = 0; it < iterations; it++) {
        double grad[M] = {0};

        for (int i = 0; i < N; i++) {
            double y_hat = 0;
            for (int j = 0; j < M; j++)
                y_hat += theta[j] * X[i][j];

            double error = y_hat - y[i];

            for (int j = 0; j < M; j++)
                grad[j] += error * X[i][j];
        }

        for (int j = 0; j < M; j++) {
            grad[j] /= N;
            theta[j] -= alpha * grad[j];
        }
    }

    cout << "Parameters WITHOUT scaling:\n";
    for (int j = 0; j < M; j++)
        cout << "theta[" << j << "] = " << theta[j] << endl;

       //PART 2: FEATURE SCALING
    double mu[M], sigma[M];

    for (int j = 1; j < M; j++) {
        mu[j] = mean(X, j);
        sigma[j] = stddev(X, j, mu[j]);

        for (int i = 0; i < N; i++)
            X[i][j] = (X[i][j] - mu[j]) / sigma[j];
    }
    for (int j = 0; j < M; j++)
        theta[j] = 0;

    alpha = 1e-3;

    for (int it = 0; it < iterations; it++) {
        double grad[M] = {0};

        for (int i = 0; i < N; i++) {
            double y_hat = 0;
            for (int j = 0; j < M; j++)
                y_hat += theta[j] * X[i][j];

            double error = y_hat - y[i];

            for (int j = 0; j < M; j++)
                grad[j] += error * X[i][j];
        }

        for (int j = 0; j < M; j++) {
            grad[j] /= N;
            theta[j] -= alpha * grad[j];
        }
    }

    cout << "\nParameters WITH scaling:\n";
    for (int j = 0; j < M; j++)
        cout << "theta[" << j << "] = " << theta[j] << endl;

    return 0;
}
