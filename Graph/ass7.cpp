#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
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
			for (int i = 0; i < n; ++i)
				newArr[i] = arr[i];
			delete[] arr;
			arr = newArr;
		}
		arr[n++] = v;
	}

	void RemoveLast() {
		if (n > 0) n--;
	}

	Value& operator[](int i) {
		return arr[i];
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int v;
	int w;
};

struct Node
{
	Array<Edge> adj;

	void Initialize() {
		adj.Initialize();
	}

	void Destroy() {
		adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n) {
		n = _n;
		nodes = new Node[n];
		for (int i = 0; i < n; ++i)
			nodes[i].Initialize();
	}

	void Destroy() {
		for (int i = 0; i < n; ++i)
			nodes[i].Destroy();
		delete[] nodes;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PriorityQueue {
    Array<pair<int, int> > a; // pair<distance, node> with space between > >

    void Initialize() {
        a.Initialize();
    }

    void Destroy() {
        a.Destroy();
    }

    void Add(pair<int, int> p) {
        a.AddLast(p);
        MoveUp(a.n - 1);
    }

    bool IsEmpty() {
        return a.n == 0;
    }

    pair<int, int> GetFirst() {
        return a[0];
    }

    void RemoveFirst() {
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
    }

private:
    void MoveUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (a[parent].first <= a[index].first)
                break;
            swap(a[parent], a[index]);
            index = parent;
        }
    }

    void MoveDown(int index) {
        int leftChild, rightChild, smallest;
        while (true) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            smallest = index;

            if (leftChild < a.n && a[leftChild].first < a[smallest].first)
                smallest = leftChild;
            if (rightChild < a.n && a[rightChild].first < a[smallest].first)
                smallest = rightChild;

            if (smallest != index) {
                swap(a[index], a[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int INF = 1000000000; // Large number to represent infinity

int Dijkstra(Graph& graph, int S, int T) {
	Array<int> dist;
	dist.Initialize();
	for (int i = 0; i < graph.n; ++i) {
		dist.AddLast(INF);
	}
	dist[S] = 0;

	PriorityQueue pq;
	pq.Initialize();
	pq.Add(make_pair(0, S));

	while (!pq.IsEmpty()) {
		pair<int, int> current = pq.GetFirst(); // No structured binding
		int d = current.first;
		int u = current.second;
		pq.RemoveFirst();

		if (u == T) {
			pq.Destroy();
			dist.Destroy();
			return d;
		}

		if (d > dist[u]) continue;

		for (int i = 0; i < graph.nodes[u].adj.n; ++i) {
			Edge& edge = graph.nodes[u].adj[i];
			int v = edge.v, w = edge.w;

			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.Add(make_pair(dist[v], v));
			}
		}
	}

	pq.Destroy();
	int result = dist[T] == INF ? -1 : dist[T];
	dist.Destroy();
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	int N;
	cin >> N;
	for (int case_num = 1; case_num <= N; ++case_num) {
		int n, m, S, T;
		cin >> n >> m >> S >> T;

		Graph graph;
		graph.Initialize(n);

		for (int i = 0; i < m; ++i) {
			int u, v, w;
			cin >> u >> v >> w;

			Edge edge1 = {v, w};
			Edge edge2 = {u, w};
			graph.nodes[u].adj.AddLast(edge1);
			graph.nodes[v].adj.AddLast(edge2);
		}

		int shortest_path = Dijkstra(graph, S, T);
		cout << "Case #" << case_num << ": ";
		if (shortest_path == -1)
			cout << "unreachable" << endl;
		else
			cout << shortest_path << endl;

		graph.Destroy();
	}

	return 0;
}
