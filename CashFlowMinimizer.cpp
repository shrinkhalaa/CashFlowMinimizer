#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// A utility function that returns the index of the minimum value in a vector
int getMin(vector<int>& arr) {
    int minInd = 0;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[minInd]) {
            minInd = i;
        }
    }
    return minInd;
}

// A utility function that returns the index of the maximum value in a vector
int getMax(vector<int>& arr) {
    int maxInd = 0;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > arr[maxInd]) {
            maxInd = i;
        }
    }
    return maxInd;
}

// A utility function to return the minimum of two values
int minOf2(int x, int y) { return (x < y) ? x : y; }

// Recursive function to minimize cash flow
void minCashFlowRec(vector<int>& amount) {
    // Find the indexes of the minimum and maximum values in the amount vector
    int maxCredit = getMax(amount), maxDebit = getMin(amount);

    // If both amounts are 0, then all amounts are settled
    if (amount[maxCredit] == 0 && amount[maxDebit] == 0) {
        return;
    }

    // Find the minimum of two amounts
    int min = minOf2(-amount[maxDebit], amount[maxCredit]);
    amount[maxCredit] -= min;
    amount[maxDebit] += min;

    // Print the cash flow transaction
    cout << "Person " << maxDebit << " pays " << min << " to Person " << maxCredit << endl;

    // Recur for the updated amount vector
    minCashFlowRec(amount);
}

int main() {
    int n; // Number of persons
    cout << "Enter the number of persons: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0)); // Adjacency matrix to store the amounts

    cout << "Enter the amounts to be paid (row-wise):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    vector<int> amount(n, 0); // Vector to store the net amount for each person

    // Calculate the net amount for each person
    for (int p = 0; p < n; p++) {
        for (int i = 0; i < n; i++) {
            amount[p] += (graph[i][p] - graph[p][i]);
        }
    }

    // Call the recursive function to minimize cash flow
    minCashFlowRec(amount);

    return 0;
}