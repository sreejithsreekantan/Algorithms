#include <iostream>
#include <set>
#include <memory>
#include <sstream>
#include <boost/dynamic_bitset.hpp>
#include <stack>
#include <algorithm>

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDigraph.h"
#include "GraphAlgorithm.h"
#include "PrimsMinimumSpanningTree.h"
#include "Graph.h"
#include "DijkstrasAlgorithm.h"
#include "TopologicalSortShortestPathAlgorithm.h"
#include "BellmanFordAlgorithm.h"


using namespace std;



int main(int argc, char const *argv[])
{

    istringstream ss;
    ss.str("	8\
				16\
				0 1 5.0\
                0 4 9.0\
                0 7 8.0\
                1 2 12.0\
                1 3 15.0\
                1 7 4.0\
                2 3 3.0\
                2 6 11.0\
                3 6 9.0\
                4 5 4.0\
                4 6 20.0\
                4 7 5.0\
                5 2 1.0\
                5 6 13.0\
                7 5 6.0\
                7 2 7.0\
			"
          );
    unique_ptr<graph::EdgeWeightedDigraph> e(graph::getEdgeWeightedDigraphFromIStream(ss));
    // graph::putGraphToOStream(*e);

    graph::BellmanFordAlgorithm bellmanFordAlgorithm(*e, 0);

    cout << " the end..." << endl;
    return 0;
}


