#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"

using namespace std;

// btw i didn't mean to submit this lat ei thoguht it was due ON sunday
// but i found out like 12 horus ago that i have a family gathering today
// so guess who's staiyn gup (me its me)

// OK THINGS I SHOULD KNOW
// PRINT PATH FROM START VERTEX (0) TO EVERY OTHER NODE (0 - N-1) 
// PRINTS COST OF EVERY PATH

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    // n is the number of vertices
    int n = G.size();

    // vectors to store shortest distance and visited nodes
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);

    // tracking the shortest path so we can reconstruct later
    previous.assign(n, -1);

    // creating the pq
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // distance from source (starts as 0), push source into pq
    distance[source] = 0;
    pq.push({0, source});

    // traverse through the queue
    while (!pq.empty())
    {
        // get the vertex to work on
        int u = pq.top().second;
        pq.pop();

        // if she's old news we skip her. (already traversed through this vertex)
        if (visited[u]) continue;

        // we need to mark the vertex as visited
        visited[u] = true;

        // for each adjacent node
        for (const Edge& neighbor : G[u])
        {
            // v is destination, weight is the edge weight of u to v
            int v = neighbor.dst;
            int weight = neighbor.weight;

            // if the path from v to u is shorter than the distance we currently have we update
            if (!visited[v] && distance[u] + weight < distance[v])
            {
                // updating distance
                distance[v] = distance[u] + weight;
                // updating path to go to v
                previous[v] = u;
                // pushing distance to pq
                pq.push({distance[v], v});
            }
        }
    }
    // return shortest distance
    return distance;


    /*    
    n = graph.adjacencyList.size()
    graph.distance.resize(n, INT_MAX)
    graph.previous.resize(n, -1)
    graph.visited.resize(n, false)
    priorityQueue pq
    pq.push(Node(source, 0))
    graph.distance[source] = 0
    while !pq.empty():
        current = pq.pop_top()
        u = current.vertex
        if graph.visited[u]:
            continue
        graph.visited[u] = true
        for each neighbor in graph.adjacencyList[u]:
            v = neighbor.vertex
            weight = neighbor.weight
            if !graph.visited[v] and graph.distance[u] + weight < graph.distance[v]:
                graph.distance[v] = graph.distance[u] + weight
                graph.previous[v] = u
                pq.push(Node(v, graph.distance[v]))
    */
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{
    vector<int> shortest_path;

    if (destination == 0) return {0};

    // if destination isn't reached, return empty
    if (previous[destination] == -1) return {};

    // backtracking!
    int curr = destination;
    while (curr != -1)
    {
        // store the current node, then move to previous
        shortest_path.push_back(curr);
        curr = previous[curr];
    }

    // reverse to backtrack correctly
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

void print_path(const vector<int>& v, int total)
{
    // if there's nothing in v we can't print a path
    if (v.empty())
    {
        cout << "Empty Path" << endl;
        return;
    }

    // for every path print the vertices and the total cost
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i];

        if (i < v.size() - 1) { cout << " ";}
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}

/*
Here is pseudocode for Disjkstra’s algorithm:
    struct Node:
        int vertex
        int weight
    struct Graph:
        list adjacencyList
        list distance
        list previous
        list visited
    function dijkstra(source, graph):
        n = graph.adjacencyList.size()
        graph.distance.resize(n, INT_MAX)
        graph.previous.resize(n, -1)
        graph.visited.resize(n, false)
        priorityQueue pq
        pq.push(Node(source, 0))
        graph.distance[source] = 0
        while !pq.empty():
            current = pq.pop_top()
            u = current.vertex
            if graph.visited[u]:
                continue
            graph.visited[u] = true
            for each neighbor in graph.adjacencyList[u]:
                v = neighbor.vertex
                weight = neighbor.weight
                if !graph.visited[v] and graph.distance[u] + weight < graph.distance[v]:
                    graph.distance[v] = graph.distance[u] + weight
                    graph.previous[v] = u
                    pq.push(Node(v, graph.distance[v]))
    end function
*/