#include <iostream>
using namespace std;

template <typename T>
struct Array {
    int numofElem;
    int size;
    T* arr;

    void Init() {
        numofElem = 0;
        size = 1;
        arr = new T[size];
    }

    void Destroy() {
        delete[] arr;
    }

    void AddLast(T n) {
        if (numofElem == size) {
            size = size * 2;
            T* newarr = new T[size];
            for (int i = 0; i < numofElem; i++) {
                newarr[i] = arr[i];
            }
            delete[] arr;
            arr = newarr;
        }
        arr[numofElem++] = n;
    }

    void RemoveLast() {
        if (numofElem > 0) {
            numofElem--;
        }
    }

    T& operator[](int i) {
        return arr[i]; 
    }
};

template <typename T>
struct Node {
    Array<T> Node_Neighbors;

    void Node_Init() {
        Node_Neighbors.Init();
    }

    void Node_Destroy() {
        Node_Neighbors.Destroy();
    }
};

template <typename T>
class Graph {
public:
    Node<T>* nodes;
    int NumOfVertices;

    void Graph_Init(int n) {
        NumOfVertices = n;
        nodes = new Node<T>[NumOfVertices];

        for (int i = 0; i < NumOfVertices; i++) {
            nodes[i].Node_Init();
        }
    }

    void Graph_Destroy() {
        for (int i = 0; i < NumOfVertices; i++) {
            nodes[i].Node_Destroy();
        }
        delete[] nodes;
    }

    void AddEdge(int src, int dest) {    // undirected_graph
        nodes[src].Node_Neighbors.AddLast(dest);
        nodes[dest].Node_Neighbors.AddLast(src);
    }

    void PrintGraph() {
        for (int i = 0; i < NumOfVertices; i++) {
            cout << "Node " << i << " has neighbors: ";
            for (int j = 0; j < nodes[i].Node_Neighbors.numofElem; j++) {
                cout << nodes[i].Node_Neighbors[j] << " ";
            }
            cout << endl;
        }
    }
};

class Queue {
public:
    int front;
    int rear;
    int size;
    int* Elem;

    void Queue_Init(int s) {
        front = -1;
        rear = -1;
        size = s;
        Elem = new int[size];
    }

    void Destroy() {
        delete[] Elem;
    }

    void Add(int elem) {
        if (front == -1) {
            Elem[0] = elem;
            front++;
            rear = front;
        } else {
            Elem[rear + 1] = elem;
            rear++;
        }
    }

    int Pop() {
        int FirstElem = Elem[front];
        front++;
        return FirstElem;
    }

    bool IsEmpty() {
        return front > rear; 
    }

    int Num() {
        return rear - front + 1;
    }
};

void BFS(Graph<int>& G, int source) {
    // Initialize the queue for BFS
    Queue Q;
    Q.Queue_Init(G.NumOfVertices);

    // Dynamic arrays to keep track of visited employees, the day they heard the news, and boom sizes
    bool* visited = new bool[G.NumOfVertices];
    int* day = new int[G.NumOfVertices];
    int* boom_size = new int[G.NumOfVertices];

    // Initialize arrays
    for (int i = 0; i < G.NumOfVertices; i++) {
        visited[i] = false;    // No employees visited initially
        day[i] = -1;           // Set initial day to -1 (not informed)
        boom_size[i] = 0;      // Initialize boom size to 0 for all employees
    }

    // Start BFS with the source employee
    Q.Add(source);              // Enqueue the source employee
    visited[source] = true;     // Mark the source as visited
    day[source] = 0;            // Set the day of the source employee to 0

    int max_boom_size = 0;      // To track the maximum boom size
    int first_boom_day = 0;     // To track the first day of the maximum boom

    // Main BFS loop
    while (!Q.IsEmpty()) {
        int current = Q.Pop();   // Dequeue the current employee
        int current_day = day[current];  // Get the day the current employee heard the news

        // Check all friends (neighbors) of the current employee
        for (int i = 0; i < G.nodes[current].Node_Neighbors.numofElem; i++) {
            int neighbor = G.nodes[current].Node_Neighbors[i]; // Get a friend
            // If the friend has not been informed yet
            if (!visited[neighbor]) {
                visited[neighbor] = true; // Mark as visited
                day[neighbor] = current_day + 1; // Set the day they heard the news
                boom_size[day[neighbor]]++; // Increment the boom size for that day

                // Update max boom size and first boom day if necessary
                if (boom_size[day[neighbor]] > max_boom_size) {
                    max_boom_size = boom_size[day[neighbor]];
                    first_boom_day = day[neighbor];
                }

                // Enqueue the neighbor for further processing
                Q.Add(neighbor);
            }
        }
    }

    // Output the results
    if (max_boom_size == 0) {
        cout << "0" << endl; // If no other employees heard the news
    }
    else {
        cout << max_boom_size << " " << first_boom_day << endl; // Output M and D
    }

    // Cleanup
    delete[] visited;
    delete[] day;
    delete[] boom_size;
}

int main() {
    Graph<int> G;
    G.Graph_Init(5);

    G.AddEdge(0, 1);
    G.AddEdge(0, 2);
    G.AddEdge(1, 3);
    G.AddEdge(1, 4);

    G.PrintGraph(); 

    BFS(G, 0); 

    G.Graph_Destroy(); 
    return 0;
}
