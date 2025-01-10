#include <iostream>
#include <vector>
#include <Queue>
using namespace std;
/*
// A way to represent a directed graph
struct Graph {
    int size;
    vector<vector<int>> adjacencyList;

    void Init(int graphSize) {
        size = graphSize;
        adjacencyList.resize(size);
    }

    // Add neighbors to a node
    void AddNodeNeighbors(int Node_data, vector<int> neighbors) {
        adjacencyList[Node_data] = neighbors;
    }

    // Print neighbors of a node
    void NodeNeighbors(int NodeParent) {
        if (NodeParent >= 0 && NodeParent < size) {
            cout << "Neighbors of node " << NodeParent << ": ";
            for (int neighbor : adjacencyList[NodeParent]) {
                cout << neighbor << " ";
            }
            cout << endl;
        } else {
            cout << "Invalid node!" << endl;
        }
    }
};

int main() {
    Graph G;
    G.Init(10);  // Initialize graph with 10 nodes
    
    // Add neighbors for node 1
    G.AddNodeNeighbors(1, {2, 3, 4, 5});
    
    // Print neighbors of node 1
    G.NodeNeighbors(1);

    return 0;
}
*/

const int MAX_NODES = 10;
const int MAX_NEIGHBORS = 5;

class Graph {
public:
    int adjacencyList[MAX_NODES][MAX_NEIGHBORS + 1];  // +1 to store the sentinel value (-1)

    // Constructor
    Graph() {
        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NEIGHBORS + 1; j++) {
                adjacencyList[i][j] = -1;  // Initialize all nodes with no neighbors
            }
        }
    }

    // Add neighbors to a node
    void AddNodeNeighbors(int node, int neighbors[], int numOfNeighbors) {
        for (int i = 0; i < numOfNeighbors; i++) {
            adjacencyList[node][i] = neighbors[i];
        }
        adjacencyList[node][numOfNeighbors] = -1;  // Sentinel to mark the end of neighbors
    }

    // Print neighbors of a node
    void PrintNodeNeighbors(int node) {
        cout << "Neighbors of node " << node << ": ";
        for (int i = 0; adjacencyList[node][i] != -1; i++) {
            cout << adjacencyList[node][i] << " ";
        }
        cout << endl;
    }

    // BFS implementation
    void BFS(int startNode) {
        bool visited[MAX_NODES] = {false};  // Keep track of visited nodes
        int queue[MAX_NODES];  // Simple array-based queue
        int front = -1, rear = -1;  // Initialize front and rear to -1

        // Start BFS from the starting node
        rear++;  // Increment rear to add the first node
        queue[rear] = startNode;
        front++;  // Increment front to indicate that we have dequeued one element
        visited[startNode] = true;

        while (front <= rear) {
            int currentNode = queue[front++];  // Dequeue
            cout << "Visited node: " << currentNode << endl;

            // Traverse the neighbors of the current node
            for (int i = 0; adjacencyList[currentNode][i] != -1; i++) {
                int neighbor = adjacencyList[currentNode][i];
                if (!visited[neighbor]) {
                    queue[++rear] = neighbor;  // Enqueue the neighbor
                    visited[neighbor] = true;
                }
            }
        }
    }
};

int main() {
    Graph G;

    // Example: Add neighbors for node 1
    int neighbors[] = {2, 3, 4, 5};
    G.AddNodeNeighbors(1, neighbors, 4);

    // Print neighbors for node 1
    G.PrintNodeNeighbors(1);

    // Perform BFS starting from node 1
    cout << "BFS traversal starting from node 1:" << endl;
    G.BFS(1);

    return 0;
}
