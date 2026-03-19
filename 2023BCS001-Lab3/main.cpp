#include <bits/stdc++.h>
using namespace std;

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

int main() {
    ofstream fout("output_alphaoooo1.txt");
    int n = 8;
    vector<double> temp = {450, 520, 610, 580, 490, 720, 680, 640};
    vector<double> press = {120, 135, 150, 148, 130, 170, 165, 155};
    vector<double> time = {1.2, 1.8, 2.5, 2.2, 1.5, 3.1, 2.9, 2.6};
    vector<int> y_cont = {210, 245, 310, 295, 235, 360, 345, 325};
    vector<int> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = (y_cont[i] >= 300) ? 1 : 0;
    }
    double theta0 = 0.0, theta1 = 0.0, theta2 = 0.0, theta3 = 0.0;

    double alpha = 0.00001;   
    int iterations = 10000;   

    for (int it = 0; it < iterations; it++) {
        double d0 = 0, d1 = 0, d2 = 0, d3 = 0;

        for (int i = 0; i < n; i++) {
            double z = theta0 +
                       theta1 * temp[i] +
                       theta2 * press[i] +
                       theta3 * time[i];

            double h = sigmoid(z);
            double error = h - y[i];

            d0 += error;
            d1 += error * temp[i];
            d2 += error * press[i];
            d3 += error * time[i];
        }
        theta0 -= alpha * d0 / n;
        theta1 -= alpha * d1 / n;
        theta2 -= alpha * d2 / n;
        theta3 -= alpha * d3 / n;
    }
    fout << "Alpha= " << alpha << "\n";
    fout << "Iterations= " << iterations << "\n";
    fout << "Learned Parameters:\n";
    fout << "theta0 = " << theta0 << endl;
    fout << "theta1 = " << theta1 << endl;
    fout << "theta2 = " << theta2 << endl;
    fout << "theta3 = " << theta3 << endl;
    fout << "\nPredictions:\n";
    fout << "Obs\tProbability\tClass\n";
    for (int i = 0; i < n; i++) {
        double z = theta0 +
                   theta1 * temp[i] +
                   theta2 * press[i] +
                   theta3 * time[i];

        double prob = sigmoid(z);
        int pred = (prob >= 0.5) ? 1 : 0;
        fout << i + 1 << "\t" << prob << "\t\t" << pred << endl;
    }
    fout.close(); 
    return 0;
}
