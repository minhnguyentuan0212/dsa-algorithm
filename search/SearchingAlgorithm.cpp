#include <iostream>
#include <math.h>
using namespace std;
int jumpSearch(int arr[], int x, int n) {
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
    int step = sqrt(n);
    int i = 0;
    for (; i < n; i+=step){
        cout<<i<<" ";
        if (arr[i] == x) return i;
        if (arr[i] > x) break;
    }
    int pre = n/step;
    pre *= step;
    if (i >= n) {
        for (int j = pre + 1; j <= n; j++){
            cout<<j<<" ";
            if (j == n) break;
            if (arr[j] == x) return j;
            if (arr[j] > x) break;
        } 
    }
    else {
        for (int j = i - step + 1; j < i; j++){
            cout<<j<<" ";
            if (arr[j] == x) return j;
            if (arr[j] > x) break;
        }
    }
    return -1;
}
int main(){
int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613 };
int x = 614;
int n = sizeof(arr) / sizeof(arr[0]);
int index = jumpSearch(arr, x, n);

if (index != -1) {
    cout << "\nNumber " << x << " is at index " << index;
}
else {
    cout << "\n" << x << " is not in array!";
}
}