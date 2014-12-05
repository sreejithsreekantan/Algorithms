#include <iostream>
#include <set>
#include <memory>
#include <sstream>

#include "Graph.h"
#include "GraphAlgorithm.h"
#include "ConnectedComponents.h"

using namespace std;

int main(int argc, char const *argv[])
{
	istringstream in;
	in.str(
			"	13		\
				13		\
				0 5 	\
				4 3 	\
				0 1 	\
				9 12 	\
				6 4 	\
				5 4 	\
				0 2 	\
				11 12 	\
				9 10 	\
				0 6 	\
				7 8 	\
				9 11 	\
				5 3 	\
			" // 3 connected components
		);
	// in.str(
	// 		"	13		\
	// 			14		\
	// 			0 5 	\
	// 			4 3 	\
	// 			0 1 	\
	// 			9 12 	\
	// 			6 4 	\
	// 			4 7		\
	// 			5 4 	\
	// 			0 2 	\
	// 			11 12 	\
	// 			9 10 	\
	// 			0 6 	\
	// 			7 8 	\
	// 			9 11 	\
	// 			5 3 	\
	// 		" // 2 connected components
	// 	);
	unique_ptr<Graph> graph(getGraphFromIStream(in));
	// putGraphToOStream(*graph, cout);

	ConnectedComponents cc(*graph);
	cout << "Number of connected components : " << cc.connectedComponentsCount() << endl;

	for (int i = 0; i < graph->V(); ++i)
	{
		cout << i << "\t" << cc.componentID(i) << endl;
	}

	return 0;
}
