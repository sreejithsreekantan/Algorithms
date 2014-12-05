#include <iostream>
#include <set>
#include <memory>
#include <sstream>
#include <boost/dynamic_bitset.hpp>
#include <stack>

#include "Graph.h"
#include "GraphAlgorithm.h"

using namespace std;


boost::dynamic_bitset<> visited(50, 0);
std::stack<int> reverseTopo;
void dfs(Graph &graph, int i)
{
    visited.set(i);
    for (std::set<int>::iterator iter = graph.edgesOf(i).begin(); iter != graph.edgesOf(i).end(); ++iter)
    {
    	if (!visited[*iter])
    	{
    		dfs(graph, *iter);
    	}
    }
    reverseTopo.push(i);
}

int main(int argc, char const *argv[])
{

    istringstream ss;
    ss.str("		7		\
				11		\
				0 1 	\
				0 2 	\
				0 5 	\
				1 4 	\
				3 2 	\
				3 4 	\
				3 5 	\
				3 6 	\
				5 2 	\
				6 0		\
				6 4 	\
			"
          );
    // one of the correct topological order : 3 6 0 5 2 1 4
    unique_ptr<Graph> graph(getGraphFromIStream(ss));
    putGraphToOStream(*graph, cout);

    for (int i = 0; i < graph->V(); ++i)
    {
        if (!visited[i])
        {
            dfs(*graph, i );
        }
    }

    cout << "\nTopological order :";
    while (!reverseTopo.empty())
    {
        cout << reverseTopo.top() << " ";
        reverseTopo.pop();
    }
    cout << endl;

    return 0;
}
