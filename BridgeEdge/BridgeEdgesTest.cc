#include <iostream>
#include <set>
#include <memory>
#include <sstream>
#include <boost/dynamic_bitset.hpp>
#include <stack>
#include <algorithm>

#include "EdgeWeightedGraph.h"
#include "GraphAlgorithm.h"
#include "PrimsMinimumSpanningTree.h"
#include "Graph.h"


using namespace std;

void dfs(unique_ptr<graph::Graph> &e, bool visited[], int parent[], int discoveredTime[], int vertex)
{
    static int time = 0;
    clog << "---------------------- " << vertex << " ---------------------- \n";
    discoveredTime[vertex] = ++time;
    clog << "discoveredTime[" << vertex << "]=" <<  discoveredTime[vertex] << "init" << endl;
    visited[vertex] = true;

    for (int i : e->edgesOf(vertex))
    {
        clog << "visited[" << i << "]" << visited[i] << endl;
     
        if (!visited[i])
        {
            parent[i] = vertex;
            clog << "parent[" << i << "] = " << vertex << endl; 
            dfs(e, visited, parent, discoveredTime, i);

            discoveredTime[vertex] = std::min(discoveredTime[i], discoveredTime[vertex]);
            clog << "discoveredTime[" << vertex << "]=" <<  discoveredTime[vertex] << endl;

            if (discoveredTime[vertex] < discoveredTime[i])
            {
                cout << "\n%%%%%%%%%%%%%" << vertex << " " << i << endl;
            }
        }
        else if (i != parent[vertex])
        {
            clog << vertex << " != parent[" << i << "]" << endl;
            discoveredTime[vertex] = std::min(discoveredTime[vertex], discoveredTime[i]);
            clog << "discoveredTime[" << vertex << "]=" <<  discoveredTime[vertex] << endl;
        }

    }


}


int main(int argc, char const *argv[])
{

    istringstream ss;
    ss.str("	5\
				5\
				0 1\
                0 2\
                1 2\
                1 3\
                3 4\
			"
          );
    unique_ptr<graph::Graph> e(graph::getUndirectedGraphFromIStream(ss));
    // graph::putGraphToOStream(*e);

    int v = e->V();

    bool visited[v];
    int parent[v];
    int discoveredTime[v];
    for_each(visited, visited + v , [](bool & x)
    {
        x = false;
    } );

    dfs(e, visited, parent, discoveredTime, 0);

    cout << " the end..." << endl;
    return 0;
}


