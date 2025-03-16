#include <iostream>
#include "dijkstras.h"
using namespace std;

int main()
{
    Graph G;
    file_to_graph("src/small.txt", G);
    int source = 0;
    vector<int> prev;
    vector<int> distances = dijkstra_shortest_path(G, source, prev);
    for (int i = 0; i < G.numVertices; i++)
    {
        vector<int> path = extract_shortest_path(distances, prev, i);
        print_path(path, distances[i]);
    }
    return 0;
}