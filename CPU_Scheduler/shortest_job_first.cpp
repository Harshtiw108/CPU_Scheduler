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
    vector<pair<int,int>> v;
    for (int j=0; j<n; j++) {
        v.push_back({arr[j],j+1});
    }
   sort(v.begin(),v.end());
   vector<int > v1(n);
   int max =0;
   for (int j=0; j<n; j++) {
        max = max + v[j].first;
        v1[v[j].second-1]=max;
    }
    cout << "Completion time for each of the process is: " << endl;
    for (int j=0; j<n; j++) {
       cout << v1[j] << " ";
    }
    cout << endl;
    max =0;
     for (int j=0; j<n; j++) {
        v1[v[j].second-1]=max;
        max = max + v[j].first;
    }
    cout << "Waiting time for each of the process is: " << endl;
     long long sum = 0;
     for (int j=0; j<n; j++) {
       cout << v1[j] << " ";
       sum = sum + v1[j];
    }
    float x = sum/n;
     cout << "Average waiting time for each process is: " << x<< endl;
    return 0;
}
