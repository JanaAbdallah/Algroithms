#include <iostream>
using namespace std;

struct Array {
    int NumOfCurrentElement;
    int size;
    int *arr;

    void Arr_Init(int s) {
        size = s;
        NumOfCurrentElement = 0;
        arr = new int[size];
    }

    void Destroy() {
        if (arr != nullptr) {
            delete[] arr;
            arr = nullptr;
            NumOfCurrentElement = 0;
        }
    }

    void Resize() {
        if (NumOfCurrentElement == size) {
            int newSize = size * 2;
            int *newArr = new int[newSize];
            for (int i = 0; i < NumOfCurrentElement; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            size = newSize;
        }
    }

    void Addtolast(int v) {
        if (NumOfCurrentElement == size) {
            Resize();
        }
        arr[NumOfCurrentElement++] = v;
    }
};

class Disjoint_Set {
public:
    int numofnodes;
    Array Parent;

    Disjoint_Set(int NumOfNodes) {
        numofnodes = NumOfNodes;
        Parent.Arr_Init(numofnodes);
        for (int i = 0; i < numofnodes; i++) {
            Parent.arr[i] = -1;
        }
    }

    ~Disjoint_Set() {
        Parent.Destroy();
    }

    int getParent(int v) {
        return Parent.arr[v];
    }

    int Find(int v) {
        if (getParent(v) == -1) {
            return v;
        }
        return Parent.arr[v] = Find(getParent(v)); // Path compression
    }

    void Union(int n, int h) {
        int rootN = Find(n);
        int rootH = Find(h);

        if (rootN == rootH) {
            cout << "They are in the same set" << endl;
        } else {
            Parent.arr[rootN] = rootH; // Attach one root to the other
        }
    }
};

int main() {
    // Example usage
    Disjoint_Set ds(5);
    ds.Union(0, 1);
    ds.Union(3, 2);
    ds.Union(3, 1);
    ds.Union(1, 4);
    cout << "Root of 1: " << ds.getParent(1) << endl;
    cout << "Root of 0: " << ds.getParent(0) << endl;

    return 0;
}
