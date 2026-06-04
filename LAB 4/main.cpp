#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

typedef vector<double> Point;

double calcDistance(Point a, Point b) {
    double sum = 0;
    for (int i = 0; i < a.size(); i++) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

Point findMean(vector<Point> cluster, int dim) {
    Point mean(dim, 0.0);

    for (int i = 0; i < cluster.size(); i++) {
        for (int j = 0; j < dim; j++) {
            mean[j] += cluster[i][j];
        }
    }

    for (int j = 0; j < dim; j++) {
        mean[j] /= cluster.size();
    }

    return mean;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int datasets;
    fin >> datasets;

    for (int d = 1; d <= datasets; d++) {

        int n, dim, K;
        fin >> n >> dim >> K;

        vector<Point> data(n, Point(dim));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < dim; j++) {
                fin >> data[i][j];
            }
        }

        vector<Point> centroids(K, Point(dim));
        for (int k = 0; k < K; k++) {
            for (int j = 0; j < dim; j++) {
                fin >> centroids[k][j];
            }
        }

        fout << "Dataset " << d << "\n";
        

        vector<int> cluster(n, -1);
        vector<int> oldCluster(n, -1);

        int iteration = 0;

        while (true) {
            iteration++;

            for (int i = 0; i < n; i++) {
                double minDist = calcDistance(data[i], centroids[0]);
                int index = 0;

                for (int k = 1; k < K; k++) {
                    double dist = calcDistance(data[i], centroids[k]);
                    if (dist < minDist) {
                        minDist = dist;
                        index = k;
                    }
                }
                cluster[i] = index;
            }

            if (iteration == 1) {
                fout << "\nIteration 1 Distance Calculation:\n";
                for (int i = 0; i < n; i++) {
                    fout << "Point ";
                    for (int j = 0; j < dim; j++)
                        fout << data[i][j] << " ";

                    fout << ": ";

                    for (int k = 0; k < K; k++) {
                        fout << "d(C" << k + 1 << ")="
                             << fixed << setprecision(2)
                             << calcDistance(data[i], centroids[k]) << " ";
                    }

                    fout << "-> Cluster " << cluster[i] + 1 << "\n";
                }
            }

            vector<vector<Point>> groups(K);
            for (int i = 0; i < n; i++) {
                groups[cluster[i]].push_back(data[i]);
            }


            vector<Point> newCentroids = centroids;
            for (int k = 0; k < K; k++) {
                if (groups[k].size() > 0) {
                    newCentroids[k] = findMean(groups[k], dim);
                }
            }

            if (iteration == 1) {
                fout << "\nCentroids after first iteration:\n";
                for (int k = 0; k < K; k++) {
                    fout << "C" << k + 1 << ": ";
                    for (int j = 0; j < dim; j++)
                        fout << newCentroids[k][j] << " ";
                    fout << "\n";
                }
            }

            bool changed = false;
            for (int i = 0; i < n; i++) {
                if (cluster[i] != oldCluster[i]) {
                    changed = true;
                    break;
                }
            }

            if (!changed && iteration > 1) {
                fout << "\nFinal Clusters after Convergence:\n";

                for (int k = 0; k < K; k++) {
                    fout << "Cluster " << k + 1 << " (Centroid: ";
                    for (int j = 0; j < dim; j++)
                        fout << newCentroids[k][j] << " ";
                    fout << ")\nMembers: ";

                    for (int i = 0; i < n; i++) {
                        if (cluster[i] == k) {
                            fout << "(";
                            for (int j = 0; j < dim; j++)
                                fout << data[i][j] << " ";
                            fout << ") ";
                        }
                    }
                    fout << "\n\n";
                }
                break;
            }

            oldCluster = cluster;
            centroids = newCentroids;
        }

        
    }

    fin.close();
    fout.close();
    return 0;
}