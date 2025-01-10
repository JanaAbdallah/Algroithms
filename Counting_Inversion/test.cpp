#include <iostream>
using namespace std;

class Counting_inversion {
public:
    int INVC;

    Counting_inversion() {
        INVC = 0;
    }

    int INVC_func(int *arr, int size) {
        INVC = 0;  // Reset INVC to 0 at the start of each call to avoid accumulation
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (arr[i] > arr[j] && i < j) {
                    INVC++;
                }
            }
        }
        return INVC;
    }
};

int main() {
    int size = 10;
    int *arr = new int[size];
    cout << "Enter array elements:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    Counting_inversion C;
    cout << "Number of inversions: " << C.INVC_func(arr, size) << endl;

    delete[] arr;  // Free dynamically allocated memory
    return 0;
}
