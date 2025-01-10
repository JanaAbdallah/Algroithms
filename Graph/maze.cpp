#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

struct Array {
    int size;
    int num_current_elem;
    int *arr;

    void Arr_Init() {
        size = 10;
        arr = new int[size];
        num_current_elem = 0;
    }

    void AddLast(int n) {
        if (num_current_elem == size) {
            int newSize = size * 2;
            int *newarray = new int[newSize]; // Allocate new array

            for (int i = 0; i < size; i++) {
                newarray[i] = arr[i]; // Copy old elements
            }
            delete[] arr; // Free old array
            arr = newarray; // Point to new array
            size = newSize; // Update size
        }
        arr[num_current_elem] = n; // Add new element
        num_current_elem++;
    }

    void Destroy() {
        delete[] arr; // Free allocated memory
    }
};

struct Node {
    int value;
    Array neighbors; // Neighbors array of each node

    void Node_Init(int v) {
        value = v; // Initialize node value
        neighbors.Arr_Init(); // Initialize neighbors
    }

    void AddNodeNeighbor(int v) {
        neighbors.AddLast(v); // Add neighbor to this node
    }

    void PrintNeighbors() {
        cout << "Neighbors of " << value << ": ";
        for (int i = 0; i < neighbors.num_current_elem; i++) {
            cout << neighbors.arr[i] << " "; // Print each neighbor
        }
        cout << endl;
    }
};

struct Graph {
    Node *GraphNodes; // Pointer to an array of nodes
    int size; // Current size of the graph
    int capacity; // Capacity of the graph

    Graph() {
        size = 0; // Initialize size
        capacity = 10; // Initial capacity
        GraphNodes = new Node[capacity]; // Allocate array of nodes
    }

    ~Graph() {
        for (int i = 0; i < size; i++) {
            GraphNodes[i].neighbors.Destroy(); // Destroy neighbors of each node
        }
        delete[] GraphNodes; // Free the array of nodes
    }

    void AddNode(int value) {
        if (size == capacity) {
            capacity *= 2; // Double the capacity
            Node *newArr = new Node[capacity]; // Allocate new array
            for (int i = 0; i < size; i++) {
                newArr[i] = GraphNodes[i]; // Copy old nodes
            }
            delete[] GraphNodes; // Delete old array
            GraphNodes = newArr; // Point to new array
        }
        GraphNodes[size].Node_Init(value); // Initialize new node
        size++; // Increase size
    }

    void AddEdge(int fromValue, int toValue) {
        for (int i = 0; i < size; i++) {
            if (GraphNodes[i].value == fromValue) {
                GraphNodes[i].AddNodeNeighbor(toValue); // Add neighbor
                break;
            }
        }
    }

    void PrintGraph() {
        for (int i = 0; i < size; i++) {
            GraphNodes[i].PrintNeighbors(); // Print neighbors for each node
        }
    };
  class MazeSolver {
public:
    int ShortestPath(int startX, int startY, int endX, int endY, vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Directions: right, down, left, up
        vector<pair<int, int>> directions = make_vector_pair(0, 1, 1, 0, 0, -1, -1, 0);

        queue<pair<int, int>> q;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        q.push(make_pair(startX, startY));
        visited[startX][startY] = true;

        int pathLength = 0;

        while (!q.empty()) {
            int qSize = q.size();
            for (int i = 0; i < qSize; i++) {
                auto current = q.front();
                q.pop();
                int x = current.first;
                int y = current.second;

                if (x == endX && y == endY) {
                    return pathLength; // Return the length of the path
                }

                for (int j = 0; j < directions.size(); j++) {
                    int newX = x + directions[j].first;
                    int newY = y + directions[j].second;

                    // Check bounds and whether the cell is walkable
                    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && 
                        grid[newX][newY] == 0 && !visited[newX][newY]) {
                        q.push(make_pair(newX, newY)); // Add new position to the queue
                        visited[newX][newY] = true; // Mark as visited
                    }
                }
            }
            pathLength++;
        }

        return -1; // Return -1 if there is no path
    }

    // Helper function to create a vector of pairs
    vector<pair<int, int>> make_vector_pair(int a1, int a2, int b1, int b2, int c1, int c2, int d1, int d2) {
        return { {a1, a2}, {b1, b2}, {c1, c2}, {d1, d2} };
    }
};

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0}
    };

    MazeSolver solver;
    int startX = 0, startY = 0;
    int endX = 4, endY = 4;

    int result = solver.ShortestPath(startX, startY, endX, endY, grid);
    cout << "Shortest Path Length: " << result << endl;

    return 0;
}