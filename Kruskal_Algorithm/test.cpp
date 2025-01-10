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

        if (rootN != rootH) {
            Parent.arr[rootN] = rootH;
        }
    }
};

// Edge structure
struct Edge {
    int u, v, w;
};

bool IsBeforeEdge(Edge& a, Edge& b) {
    return a.w < b.w;
}

// Merge function for MergeSort
template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    int mid = n / 2;
    int i = 0, j = mid, k = 0;
    Type* temp = new Type[n];

    while (i < mid && j < n) {
        if (IsBefore(a[i], a[j])) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i < mid) temp[k++] = a[i++];
    while (j < n) temp[k++] = a[j++];

    for (i = 0; i < n; i++) {
        a[i] = temp[i];
    }
    delete[] temp;
}

// MergeSort function to sort array of edges
template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    if (n <= 1) return;
    int mid = n / 2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, n - mid, IsBefore);
    Merge(a, n, IsBefore);
}

int KruskalMST(Edge* edges, int numEdges, int numNodes) {
    MergeSort(edges, numEdges, IsBeforeEdge);

    Disjoint_Set ds(numNodes);
    int mstWeight = 0;
    int edgesInMST = 0;

    for (int i = 0; i < numEdges && edgesInMST < numNodes - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (ds.Find(u) != ds.Find(v)) {
            ds.Union(u, v);
            mstWeight += w;
            edgesInMST++;
        }
    }

    return mstWeight;
}

int main() {
    int m, n;

    while (true) {
        cout << "Enter the number of junctions (nodes) and roads (edges): ";
        cin >> m >> n;
        
        if (m == 0 && n == 0) {
            cout << "Terminating program." << endl;
            break;
        }

        Edge* edges = new Edge[n];
        int totalCost = 0;

        cout << "Enter each road with its two endpoints and length (u v w):" << endl;
        for (int i = 0; i < n; i++) {
            cout << "Road " << i + 1 << ": ";
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            totalCost += edges[i].w;
        }

        int mstWeight = KruskalMST(edges, n, m);
        int maxSavings = totalCost - mstWeight;
        cout << "Maximum daily savings: " << maxSavings << " Bytelandian Dollars" << endl << endl;

        delete[] edges;
    }

    return 0;
}
