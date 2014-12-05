/*
	Author			:			Sreejith Sreekantan
	Discription		:			Test program for Dijkstras algorithm

	Correct Answer:
	visited_ : 0(1) 1(1) 2(1) 3(1) 4(1) 5(1) 6(1) 7(1) 
	weight_ : 0(0) 1(5) 2(14) 3(17) 4(9) 5(13) 6(25) 7(8) 
	parent_ : 0(0) 1(0) 2(5) 3(2) 4(0) 5(4) 6(2) 7(0) 
*/

#include "TopologicalSort.h"
#include "TopoShortestPathAlgorithm.h"
#include "EdgeWeightedDigraph.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{

	istringstream in;
	in.str("\
		8\
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
		");

	int x,y,z;
	double w;
	in >> x;
	std::shared_ptr<graph::EdgeWeightedDigraph> edgeWeightedDigraphPtr(new graph::EdgeWeightedDigraph(x));
	in >> x;
	for (int i = 0; i < x; ++i)
	{
		in >> y >> z >> w;
		edgeWeightedDigraphPtr->addEdge(y, z, w);
	}

	// graph::TopologicalSort topologicalSort(edgeWeightedDigraphPtr);
	// cout << "\nOrder : ";
	// for (int i : topologicalSort.order())
	// {
	// 	cout << i << " ";
	// }
	// cout << endl;

	graph::TopoShortestPathAlgorithm topoShortestPathAlgorithm(edgeWeightedDigraphPtr, 0); 
	for (int i = 0; i < edgeWeightedDigraphPtr->V(); ++i)
	{
		cout << i << " " << topoShortestPathAlgorithm.weight(i) << endl;
	}

}