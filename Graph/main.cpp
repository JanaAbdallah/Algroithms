#include <iostream>
using namespace std ;

struct Array{
	int numofElem;
	int size ;
    int *arr;

	void Init(){
		numofElem=0;
		size =1 ;
		arr=new int[size];
	}

	void Destroy(){
		delete [] arr;
	}

	void AddLast(int n){
    if(numofElem == size){
        size = size * 2;
        int* newarr = new int[size];
        for(int i = 0; i < numofElem; i++){
            newarr[i] = arr[i];
        }
        delete [] arr;
        arr = newarr;
    }
    arr[numofElem++] = n; // Add the new element regardless of the array's capacity
}

void RemoveLast(){
    numofElem--;
}

 int& operator[](int i) {
        return arr[i];  // return reference to element at index i
    }
};

struct Node {
	Array Node_Neighbors ;

	 void Node_Init(){
	 	Node_Neighbors.Init();
	 }

	 void Node_Destroy(){
        Node_Neighbors.Destroy();
	 }
};

class Graph{
	public : 
	  Node *nodes;
	  int NumOfVertices;

	  void Graph_Init(int n){
	  	NumOfVertices=n;
	  	nodes=new Node[NumOfVertices];

	  	for(int i = 0 ; i<NumOfVertices;i++){
	  		nodes[i].Node_Init();
	  	}

	  }

	  void Graph_Destroy(){
	  	for(int i = 0 ;i<NumOfVertices ;i++){
	  		nodes[i].Node_Destroy();
	  	}
	  	delete nodes;
	  }

	  void AddEgde(int src , int dest){
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

class Queue{
public:
	int front ;
	int rear;
	int size;
	int *Elem;

	void Queue_Init(int s){
       front=-1;
       rear=-1;
       size=s;
       Elem=new int[size];
	}
    
	void Destroy(){
       delete [] Elem;
	}
	
	void Add(int elem){
		if(front==-1){
			Elem[0]=elem;
			front++;
			rear=front;
		}
		else{
			Elem[rear+1]=elem;
			rear++;
		}
	}

	int Pop(){
		int FirstElem;
		FirstElem=Elem[front];
		front++;
		return FirstElem;
	}

	int Peek(){
		return Elem[front];
	}

	int Num(){
		return rear-front+1;
	}

};

// Breadth-First Search (BFS) on the Graph
void BFS_Graph(Graph &G, int StartingVt) {
    Queue VtQ;
    VtQ.Queue_Init(G.NumOfVertices);
    bool *Visited = new bool[G.NumOfVertices];
    for (int i = 0; i < G.NumOfVertices; i++) {
        Visited[i] = false;  // Initially mark all nodes as unvisited
    }

    VtQ.Add(StartingVt);  // Start BFS from the starting vertex
    Visited[StartingVt] = true;

    while (VtQ.Num() > 0) {
        int current = VtQ.Pop();  // Get the front element in the queue
        cout << "Visited node: " << current << endl;

        // Explore all neighbors of the current node
        for (int i = 0; i < G.nodes[current].Node_Neighbors.numofElem; i++) {
            int neighbor = G.nodes[current].Node_Neighbors[i];
            if (!Visited[neighbor]) {
                VtQ.Add(neighbor);  // Add neighbor to the queue
                Visited[neighbor] = true;  // Mark the neighbor as visited
            }
        }
    }

    VtQ.Destroy();  // Clean up the queue
    delete[] Visited;  // Free the visited array
}
int main (){
     Graph G1;
     G1.Graph_Init(4); // give him the num of vertices
     G1.AddEgde(0,1);
     G1.AddEgde(0,2);
     G1.AddEgde(1,3);
     G1.AddEgde(2,3);
     G1.PrintGraph();


    cout << "BFS starting from node 0:" << endl;
    BFS_Graph(G1, 3);  // Perform BFS starting from node 0

    G1.Graph_Destroy();  // Clean up the graph


}