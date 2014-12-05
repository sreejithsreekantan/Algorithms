/*
	Author			:		Sreejith Sreekantan
	Description		:		EdgeWeightedDigraph
*/


#ifndef __EDGEWEIGHTEDDIGRAPH_H__
#define __EDGEWEIGHTEDDIGRAPH_H__

#include <vector>
#include <memory>
#include "Edge.h"	


namespace graph
{

class EdgeWeightedDigraph
{
public:
	EdgeWeightedDigraph(int v);
	bool addEdge(int from, int to, double weight);
	int V() const;
	int E() const;
	const std::vector< std::shared_ptr<const Edge> >& edgesOf(int from) const;

private:
	int v_;	// num of vertices
	int e_; // num of edges
	std::vector< std::vector< std::shared_ptr<const Edge> > > edgesOf_;
};

EdgeWeightedDigraph::EdgeWeightedDigraph(int v):
v_(v), e_(0), edgesOf_(v_)
{

}

bool EdgeWeightedDigraph::addEdge(int from, int to, double weight)
{
	std::shared_ptr<const Edge> graph_sh_ptr(new Edge(from, to, weight));
	edgesOf_[from].push_back(graph_sh_ptr);
	++e_;
	return true;
}

int EdgeWeightedDigraph::V() const
{
	return v_;
}

int EdgeWeightedDigraph::E() const
{
	return e_;
}

const std::vector< std::shared_ptr<const Edge> >& EdgeWeightedDigraph::edgesOf(int from) const
{
	return edgesOf_[from];
}

} // namespace graph


#endif // __EDGEWEIGHTEDDIGRAPH_H__