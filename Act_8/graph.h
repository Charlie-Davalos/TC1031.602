#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Graph {
private:
    vector<vector<int>> adj_matrix;
    vector<vector<int>> adj_list;
    int nu_vertices;

public:
    Graph() {}

    // Loading functions
    void loadGraphMat(string input, int vertices, int edges);
    void loadGraphList(string input, int vertices);

    // Printing functions
    string printAdjMat();
    string printAdjList();

    // Search algorithms
    string DFS(int init_vertex, int target_vertex);
    string BFS(int init_vertex, int target_vertex);

    // Helper functions
    string print_vector(const vector<int>& vec);
};

string Graph::print_vector(const vector<int>& vec) {
    string result = "";
    for (int i : vec) {
        result += to_string(i) + " ";
    }
    return result;
}

void Graph::loadGraphMat(string input, int vertices, int edges) {
    nu_vertices = vertices;
    // Create adjacency matrix
    adj_matrix = vector<vector<int>>(vertices, vector<int>(vertices, 0));

    size_t pos = 0;
    string token;
    while ((pos = input.find(' ')) != string::npos) {
        token = input.substr(0, pos);
        int init_vertex, end_vertex;
        sscanf(token.c_str(), "(%d,%d)", &init_vertex, &end_vertex);
        adj_matrix[init_vertex][end_vertex] = 1;
        adj_matrix[end_vertex][init_vertex] = 1;
        input.erase(0, pos + 1);
    }
}

void Graph::loadGraphList(string input, int vertices) {
    nu_vertices = vertices;
    // Create adjacency list
    adj_list = vector<vector<int>>(vertices);

    size_t pos = 0;
    string token;
    while ((pos = input.find(' ')) != string::npos) {
        token = input.substr(0, pos);
        int init_vertex, end_vertex;
        sscanf(token.c_str(), "(%d,%d)", &init_vertex, &end_vertex);
        adj_list[init_vertex].push_back(end_vertex);
        adj_list[end_vertex].push_back(init_vertex);
        input.erase(0, pos + 1);
    }
}

string Graph::printAdjMat() {
    string result = "";
    for (const vector<int>& row : adj_matrix) {
        for (int val : row) {
            result += to_string(val) + " ";
        }
        result += '\n';
    }
    return result;
}

string Graph::printAdjList() {
    string result = "";
    for (int i = 0; i < adj_list.size(); i++) {
        result += "vertex " + to_string(i) + " : ";
        sort(adj_list[i].begin(), adj_list[i].end());
        for (int j : adj_list[i]) {
            result += to_string(j) + " ";
        }
        result += '\n';
    }
    return result;
}

string Graph::DFS(int init_vertex, int target_vertex) {
    // Init vars
    vector<int> stack;
    vector<int> visited;
    int current = init_vertex;

    while (!(visited.size() >= nu_vertices)) {
        // Check if the current is already in visited
        bool already_visited = find(visited.begin(), visited.end(), current) != visited.end();

        // Add to visited
        if (!already_visited) visited.push_back(current);

        // Check if target found
        if (current == target_vertex) break;

        // Remove already visited values
        adj_list[current].erase(remove_if(adj_list[current].begin(), adj_list[current].end(),
                                          [&visited](int v) { return find(visited.begin(), visited.end(), v) != visited.end(); }),
                                adj_list[current].end());

        if (!adj_list[current].empty()) {
            stack.push_back(current);
            // Check for last child of the current node
            int temp_index = current;
            current = adj_list[current].back();
            adj_list[temp_index].pop_back();
        } else {
            // If you hit a wall
            current = stack.back();
            stack.pop_back();
        }
    }

    // Add to the stack the found value to complete the path
    stack.push_back(current);

    // Convert list to string
    string visited_str = print_vector(visited);
    string path_str = print_vector(stack);
    string result = "visited: " + visited_str + "path: " + path_str;
    result = result.substr(0, result.size() - 1);
    return result;
}

string Graph::BFS(int init_vertex, int target_vertex) {
    vector<vector<int>> queue;
    vector<vector<int>> visited;
    int current = init_vertex;
    int parent = -1;

    while (true) {
        // Add to visited
        vector<int> temp_visited({parent, current});
        visited.push_back(temp_visited);
        // Check if found
        if (current == target_vertex) break;
        // Push children to the queue if not visited
        for (int val : adj_list[current]) {
            bool already_visited = find_if(visited.begin(), visited.end(),
                                           [val](const vector<int>& v) { return v[1] == val; }) != visited.end();
            vector<int> temp_queue({current, val});
            if (!already_visited) queue.push_back(temp_queue);
        }
        // Take from the queue
        parent = queue[0][0];
        current = queue[0][1];
        queue.erase(queue.begin());
    }

    // Get the path
    vector<int> path;
    int find = target_vertex;
    do {
        for (const vector<int>& v : visited) {
            if (v[1] == find) {
                path.insert(path.begin(), find);
                find = v[0];
            }
        }
    } while (find != -1);

    // Convert visited into a single array
    vector<int> converted_visited;
    for (const vector<int>& v : visited) {
        converted_visited.push_back(v[1]);
    }

    // Convert list to string
    string visited_str = print_vector(converted_visited);
    string path_str = print_vector(path);
    string result = "visited: " + visited_str + "path: " + path_str;
    result = result.substr(0, result.size() - 1);
    return result;
}

