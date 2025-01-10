#include <cstdio>
#include <cmath>

const double INF = 1e9;  // Large constant to represent "infinity"

template<class Value>
struct Array {
    int n, sz;
    Value* arr;

    void Initialize() {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(Value v) {
        if (n == sz) {  
            sz *= 2;
            Value* newArr = new Value[sz];
            for (int i = 0; i < n; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[n++] = v;
    }

    Value& operator[](int i) {
        return arr[i];
    }
};

struct Edge {
    int v;     
    double w;  
};

struct Node {
    int x, y; 
    Array<Edge> adj;

    void Initialize() {
        adj.Initialize();
    }

    void Destroy() {
        adj.Destroy();
    }
};

struct Graph {
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i].Initialize();
        }
    }

    void Destroy() {
        for (int i = 0; i < n; i++) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

double Sqrt(double v, int n=100) {
    if (v < 0) return -1;
    double x = v;
    for (int i = 0; i < n; i++) {
        x = 0.5 * (x + v / x);
    }
    return x;
}

double EuclideanDistance(int x1, int y1, int x2, int y2) {
    return Sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Prim(Graph& g) {
    double maxEdgeInPath[200];
    bool visited[200] = {false};

    for (int i = 0; i < g.n; i++) {
        maxEdgeInPath[i] = INF;
    }
    maxEdgeInPath[0] = 0;

    for (int _ = 0; _ < g.n; _++) {
        int u = -1;
        double minEdge = INF;

        for (int i = 0; i < g.n; i++) {
            if (!visited[i] && maxEdgeInPath[i] < minEdge) {
                minEdge = maxEdgeInPath[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int i = 0; i < g.nodes[u].adj.n; i++) {
            Edge& edge = g.nodes[u].adj[i];
            int v = edge.v;
            double weight = edge.w;
            double maxEdgeInPathThroughU = (maxEdgeInPath[u] > weight) ? maxEdgeInPath[u] : weight;

            if (maxEdgeInPathThroughU < maxEdgeInPath[v]) {
                maxEdgeInPath[v] = maxEdgeInPathThroughU;
            }
        }
    }
    return maxEdgeInPath[1];
}

int main() {
    int scenario = 1;
    while (true) {
        int n;
        std::scanf("%d", &n);
        if (n == 0) break;

        Graph g;
        g.Initialize(n);

        for (int i = 0; i < n; i++) {
            std::scanf("%d %d", &g.nodes[i].x, &g.nodes[i].y);
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dist = EuclideanDistance(g.nodes[i].x, g.nodes[i].y, g.nodes[j].x, g.nodes[j].y);
                Edge edge1 = {j, dist};
                Edge edge2 = {i, dist};
                g.nodes[i].adj.AddLast(edge1);
                g.nodes[j].adj.AddLast(edge2);
            }
        }

        double frogDistance = Prim(g);
        printf("Scenario #%d\n", scenario++);
        printf("Frog Distance = %.3f\n\n", frogDistance);

        g.Destroy();
    }

    return 0;
}
