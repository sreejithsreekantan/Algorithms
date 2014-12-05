/*
	Author		:		Sreejith Sreekantan
	Description	:		Directed edge
						represents a weighted edge between two vertices
*/
#ifndef __EDGEWEIGHTEDDIGRAPH_H__
#define __EDGEWEIGHTEDDIGRAPH_H__

#include <vector>
#include <memory>
#include <atomic>						
#include "DirectedEdge.h"						

namespace graph
{

class EdgeWeightedDigraph
{
public:
	EdgeWeightedDigraph(int v): v_(v), e_(0), edges_(v_) {}

	// setters
	bool addEdge(int u, int v, double weight);

	// getters
	int V() const { return v_; }
	int E() const { return e_; }
	const std::vector< std::shared_ptr< const DirectedEdge > >& edgesOf(int x) const { return edges_[x]; }

private:
	int v_;
	std::atomic<int> e_;
	std::vector< std::vector< std::shared_ptr< const DirectedEdge > > > edges_;
};

bool EdgeWeightedDigraph::addEdge(int u, int v, double weight)
{
	std::shared_ptr< const DirectedEdge > edge(new DirectedEdge(u, v, weight));
	edges_[u].push_back(edge);
	++e_;
	return true;
}

}

#endif // __EDGEWEIGHTEDDIGRAPH_H__