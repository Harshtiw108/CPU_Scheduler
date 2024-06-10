#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cout << "Number of processes scheduled" << endl;
    cin >> n;
    int arr[n];
    cout << "Give the burst time for each process in millisecond" << endl;
    for (int j=0; j<n; j++) {
        cin >> arr[j];
    }
    long long max = 0;
    cout << "Completion time for each of the process is: " << endl;
    for (int j=0; j<n; j++) {
        max = max + arr[j];
        cout << max << " ";
    }
    cout << endl;
    max = 0;
    long long sum = 0;
    cout << "Waiting time for each of the process is: " << endl;
    for (int j=0; j<n; j++) {
        cout << max << " ";
        sum = sum + max;
         max = max + arr[j];
    }
    cout << endl;
    float x = sum/n;
    cout << "Average waiting time for each process is: " << x << endl;
    return 0;
}