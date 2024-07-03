#include <iostream>
#include <list>
#include <queue>
using namespace std;

void DFS(vector<vector<int>> friends, int *visited, int v) {
    for (int i = 0; i < friends[v].size(); i++) {
        if (!visited[friends[v][i]]) {
            visited[friends[v][i]] = 1;
            DFS(friends, visited, friends[v][i]);
        }
    }
}

int numberOfFriendGroups(vector<vector<int>>& friends) {
    // STUDENT ANSWER
    int n = friends.size();
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;
    int numGroup = 0; 
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            DFS(friends, visited, i);
            numGroup++;
        }
    }
    return numGroup;
    
}
class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const &i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const &i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx) 
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}
	
	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	
	Adjacency *BFS(int v)
    {
        // v is a vertex we start BFS
        Adjacency *newAdj = new Adjacency(V);
        queue<int> q;
        q.push(v);
        newAdj->push(v);
        int arr[V];
        for (int i=0;i<V;i++) arr[i]=0;
        arr[v]=1;
        while (!q.empty()){
        for (int j=0;j<this->adj[q.front()].getSize();j++)
            if (arr[this->adj[q.front()].getElement(j)]==0) {
                q.push(this->adj[q.front()].getElement(j)); 
                arr[this->adj[q.front()].getElement(j)]=1;
                newAdj->push(this->adj[q.front()].getElement(j));
            }
        q.pop();   
    }
        return newAdj;
	}
};
int main() {
vector<vector<int>> graph {
	{1},
	{0, 2},
	{1},
	{4},
	{3},
	{}
};
cout << numberOfFriendGroups(graph);
}
