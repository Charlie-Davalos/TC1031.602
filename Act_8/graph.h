#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
    int nodes;
    vector<vector<int>> adjList;
    vector<int> adjMatrix;

public:
    Graph();
    Graph(int);
    ~Graph() = default;

    void loadGraphList(const string&, int);
    void loadGraphMat(const string&, int, int);
    void addEdgeAdjList(int, int);
    void addEdgeAdjMatrix(int, int);
    string printAdjList();
    string printAdjMat();
    string DFS(int, int);
    string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
    string BFS(int, int);
    string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
    string print_visited(list<int>);
    string print_path(const vector<vector<int>>&, int, int);
    bool contains(const list<int>&, int);
    void sortAdjList();
};

Graph::Graph() {
    nodes = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList.resize(nodes);
    adjMatrix.assign(nodes * nodes, 0);
}

void Graph::loadGraphList(const string& line, int numberVert) {
    nodes = numberVert;
    adjList.resize(nodes);

    int u, v;
    char ch;

    stringstream ss(line);
    while (ss >> ch) {
        if (ss >> u >> ch >> v >> ch) {
            addEdgeAdjList(u, v);
        } else {
            cerr << "Error: Malformed input format." << endl;
            // Puedes lanzar una excepción o manejar el error de otra manera aquí.
        }
    }

    sortAdjList();
}

void Graph::loadGraphMat(const string& line, int a, int b) {
    nodes = a;
    adjMatrix.assign(a * b, 0);

    int u, v;
    char ch;

    stringstream ss(line);
    while (ss >> ch) {
        if (ss >> u >> ch >> v >> ch) {
            addEdgeAdjMatrix(u, v);
        } else {
            cerr << "Error: Malformed input format." << endl;
            // Puedes lanzar una excepción o manejar el error de otra manera aquí.
        }
    }
}

void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
}

string Graph::printAdjList() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        aux << "vertex " << i << " :";
        for (int j = 0; j < adjList[i].size(); j++) {
            aux << " " << adjList[i][j];
        }
        aux << " ";
    }
    return aux.str();
}

string Graph::printAdjMat() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            aux << adjMatrix[i * nodes + j] << " ";
        }
    }
    return aux.str();
}

string Graph::DFS(int start, int goal) {
    if (start < 0 || start >= nodes || goal < 0 || goal >= nodes) {
        return "Invalid start or goal node.";
    }

    stack<int> auxStack;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, 0));
    auxStack.push(start);

    stringstream ss;
    ss << depthHelper(start, goal, auxStack, visited, paths) << print_path(paths, start, goal);
    return ss.str();
}

string Graph::depthHelper(int current, int goal, stack<int>& auxStack, list<int>& visited, vector<vector<int>>& paths) {
    if (current == goal) {
        return print_visited(visited);
    } else if (auxStack.empty()) {
        return " node not found";
    } else {
        current = auxStack.top();
        auxStack.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                auxStack.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
            }
        }
        return depthHelper(current, goal, auxStack, visited, paths);
    }
}

string Graph::BFS(int start, int goal) {
    if (start < 0 || start >= nodes || goal < 0 || goal >= nodes) {
        return "Invalid start or goal node.";
    }

    queue<int> auxQueue;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, 0));
    auxQueue.push(start);
    visited.push_back(start);

    stringstream ss;
    ss << breadthHelper(start, goal, auxQueue, visited, paths) << print_path(paths, start, goal);
    return ss.str();
}

string Graph::breadthHelper(int current, int goal, queue<int>& auxQueue, list<int>& visited, vector<vector<int>>& paths) {
    if (current == goal) {
        return print_visited(visited);
    } else if (!auxQueue.empty()) {
        current = auxQueue.front();
        auxQueue.pop();
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                auxQueue.push(adjList[current][i]);
                visited.push_back(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
                if (adjList[current][i] == goal) {
                    return print_visited(visited);
                }
            }
        }
        return breadthHelper(current, goal, auxQueue, visited, paths);
    }

    return " node not found";
}

string Graph::print_visited(list<int> q) {
    stringstream aux;
    aux << "visited: ";
    while (!q.empty()) {
        aux << q.front() << " ";
        q.pop_front();
    }
    return aux.str();
}

string Graph::print_path(const vector<vector<int>>& path, int start, int goal) {
    int node = path[goal][0];
    stack<int> reverse;
    reverse.push(goal);
    stringstream aux;
    aux << "path:";

    while (node != start) {
        reverse.push(node);
        node = path[node][0];
    }

    reverse.push(start);
    while (!reverse.empty()) {
        aux << " " << reverse.top();
        reverse.pop();
    }

    return aux.str();
}

bool Graph::contains(const list<int>& ls, int node) {
    return find(ls.begin(), ls.end(), node) != ls.end();
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i++) {
        sort(adjList[i].begin(), adjList[i].end());
    }
}

#endif /* Graph_H_ */
