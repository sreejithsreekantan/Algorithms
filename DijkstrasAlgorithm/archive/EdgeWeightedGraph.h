/*
    Author      :       Sreejith Sreekantan

*/

#ifndef __EDGEWEIGHTEDGRAPH_H__
#define __EDGEWEIGHTEDGRAPH_H__

#include "Edge.h"
#include <memory>

namespace graph
{

class EdgeWeightedGraph
{
public:
	EdgeWeightedGraph(int v):v_(v), e_(0), edges_(v_) {}
	bool addEdge(int u, int v, double weight);
	int V() const { return v_; }
	int E() const { return e_; }
	const std::vector< std::shared_ptr<Edge> >& edgesOf(int u) const { return edges_[u]; }

private:
	int v_;
	int e_;
	std::vector<std::vector< std::shared_ptr<Edge> > > edges_;

};

bool EdgeWeightedGraph::addEdge(int u, int v, double weight)
{
	std::shared_ptr<Edge> edge(new Edge(u, v, weight));
	// since its undirected graph, add this edges to both vertices' list
	edges_[u].push_back(edge);
	edges_[v].push_back(edge);
	++e_;
	return true;
}

} // namespace graph

#endif // __EDGEWEIGHTEDGRAPH_H__