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

// Merge function used by MergeSort
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

struct Edge {
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge& a, Edge& b) {
    return a.w < b.w;
}

int KruskalMST(Edge* edges, int numEdges, int numNodes) {
    // Sort edges by weight
    MergeSort(edges, numEdges, IsBeforeEdge);

    Disjoint_Set ds(numNodes);
    int mstWeight = 0;
    int edgesInMST = 0;

    for (int i = 0; i < numEdges && edgesInMST < numNodes - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        // Check if u and v are in the same set
        if (ds.Find(u) != ds.Find(v)) {
            // If not, add edge to MST
            ds.Union(u, v);
            mstWeight += w;
            edgesInMST++;
            cout << "Edge (" << u << ", " << v << ") with weight " << w << " added to MST." << endl;
        }
    }

    return mstWeight;
}

int main() {
    int numNodes, numEdges;

    cout << "Enter the number of nodes and edges: ";
    cin >> numNodes >> numEdges;

    Edge* edges = new Edge[numEdges];

    cout << "Enter the edges (u v w):" << endl;
    for (int i = 0; i < numEdges; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int mstWeight = KruskalMST(edges, numEdges, numNodes);
    cout << "Total weight of MST: " << mstWeight << endl;

    delete[] edges;
    return 0;
}
