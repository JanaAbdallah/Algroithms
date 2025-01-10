#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long* a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    long long* leftArr = new long long[n1];
    long long* rightArr = new long long[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    long long inv_count = 0;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            a[k++] = leftArr[i++];
        } else {
            a[k++] = rightArr[j++];
            inv_count += (n1 - i); 
        }
    }

    while (i < n1) {
        a[k++] = leftArr[i++];
    }
    while (j < n2) {
        a[k++] = rightArr[j++];
    }

    delete[] leftArr;
    delete[] rightArr;

    return inv_count;
}

long long CountInv(long long* a, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        inv_count += CountInv(a, left, mid);
        inv_count += CountInv(a, mid + 1, right);
        inv_count += CountInvMerge(a, left, mid, right);
    }
    return inv_count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    while (true) {
        int n;
        cin >> n; 
        if (n == 0) break; 

        long long* arr = new long long[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        long long inversions = CountInv(arr, 0, n - 1);
        cout << inversions << endl; 

        delete[] arr; 
    }
    return 0;
}
