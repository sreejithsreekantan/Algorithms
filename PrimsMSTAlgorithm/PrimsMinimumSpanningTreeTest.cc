#include <iostream>
#include <set>
#include <memory>
#include <sstream>
#include <boost/dynamic_bitset.hpp>
#include <stack>

#include "EdgeWeightedGraph.h"
#include "GraphAlgorithm.h"
#include "PrimsMinimumSpanningTree.h"


using namespace std;



int main(int argc, char const *argv[])
{

    istringstream ss;
    ss.str("	8		    \
				16		    \
				4 5 0.35  	\
				4 7 0.37 	\
				5 7 0.28 	\
                0 7 0.16    \
				1 5 0.32 	\
                0 4 0.38    \
                2 3 0.17    \
                1 7 0.19    \
                0 2 0.26    \
                1 2 0.36    \
                1 3 0.29    \
                2 7 0.34    \
                6 2 0.40    \
                3 6 0.52    \
                6 0 0.58    \
                6 4 0.93    \
			"
          );
    unique_ptr<graph::EdgeWeightedGraph> e(graph::getEdgeWeightedGraphFromIStream(ss));


    cout << "\nEdge weighted Graph :\n";
    graph::putGraphToOStream(*e);
    graph::PrimsMinimumSpanningTree minimumSpanningTree(*e);
    cout << "\nMST edges: \n";
    for (auto i = minimumSpanningTree.edges().begin(); i != minimumSpanningTree.edges().end(); ++i)
    {
        
        cout << "\n" << (*i)->either() << " " << (*i)->other((*i)->either()) << " " << (*i)->weight();
    }
    cout << " the end..." << endl;
    return 0;
}
