#include <iostream>
#include <set>
#include <memory>
#include <sstream>
#include <boost/dynamic_bitset.hpp>
#include <stack>

#include "Graph.h"
#include "GraphAlgorithm.h"
#include "StrongComponent.h"

using namespace std;

int main(int argc, char const *argv[])
{

    istringstream ss;
    ss.str("	13		\
				22		\
				0 1 	\
				0 5 	\
				2 0 	\
                2 3     \
				3 2 	\
                3 5     \
                4 2     \
                4 3     \
                5 4     \
                6 0     \
                6 4     \
                6 8     \
                6 9     \
                7 6     \
                7 9     \
                8 6     \
                9 10    \
                9 11    \
                10 12   \
                11 4    \
                11 12   \
                12 9    \
			"
          );
    // one of the correct topological order : 3 6 0 5 2 1 4
    unique_ptr<graph::Graph> graph(graph::getGraphFromIStream(ss));
    putGraphToOStream(*graph, cout);

    std::unique_ptr<std::vector<int> > topologicalOrder( graph::TopologicalOrder(*graph) );

    graph::StrongComponent strongComponent(*graph);

    cout << "\nStrong Components :\n";
    std::vector<int> v = strongComponent.getComponentIDSet();
    int u = 0;
    for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i, ++u)
    {
        cout << u << " " << *i << endl;
    }

    cout << " the end..." << endl;
    return 0;
}