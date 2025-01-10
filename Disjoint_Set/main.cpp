#include <iostream>
using namespace std;

struct DisjointSets {
    int n;          // number of citizens
    int* parent;    
    int* num_nodes; 

    void Initialize(int _n) {
        n = _n;
        parent = new int[n + 1];  
        num_nodes = new int[n + 1]; 
        for (int i = 1; i <= n; i++) {
            parent[i] = i;   
            num_nodes[i] = 1;
        }
    }


    void Destroy() {
        delete[] parent;
        delete[] num_nodes;
    }

   
    int Find(int i) {
        if (parent[i] != i)
            parent[i] = Find(parent[i]); 
        return parent[i];
    }

    
    bool Union(int i, int j) {
        int rootI = Find(i);
        int rootJ = Find(j);

        if (rootI == rootJ) return false;

        if (num_nodes[rootI] < num_nodes[rootJ]) {
            parent[rootI] = rootJ;
            num_nodes[rootJ] += num_nodes[rootI]; 
        } else {
            parent[rootJ] = rootI;
            num_nodes[rootI] += num_nodes[rootJ]; 
        }

        return true;
    }

   
    int getSize(int i) {
        return num_nodes[Find(i)];
    }
};


void solve() {
    int T;  //number of test cases 
    cin >> T;

    while (T--) {
        int N, M; // N -> number of citizens / M -> num of pairs
        cin >> N >> M;

        DisjointSets ds;
        ds.Initialize(N);

        for (int i = 0; i < M; i++) {
            int A, B; 
            cin >> A >> B;
            ds.Union(A, B); 
        }

        int largestGroup = 0;
        for (int i = 1; i <= N; i++) {
            largestGroup = (ds.getSize(i) > largestGroup) ? ds.getSize(i) : largestGroup;
        }

        cout << largestGroup << endl;

        ds.Destroy(); 
    }
}

int main() {
    solve();
    return 0;
}
