/*
	Author		:		Sreejith Sreekantan
	Description	:		TopoShortestPathAlgorithm
*/

#ifndef __TOPOSHORTESTPATHALGORITHM_H__
#define __TOPOSHORTESTPATHALGORITHM_H__

#include <vector>
#include <memory>
#include <limits>
#include "EdgeWeightedDigraph.h"
#include "Edge.h"
#include "TopologicalSort.h"

namespace graph
{

class TopoShortestPathAlgorithm
{
public:
	TopoShortestPathAlgorithm(std::shared_ptr<EdgeWeightedDigraph> edgeWeightedDigraphPtr, int src);
	double weight(int x) const;
	const std::vector<double> weight() const;
private:
	std::shared_ptr<EdgeWeightedDigraph> edgeWeightedDigraphPtr_;
	int v_;
	int src_;
	std::vector<int> parent_;
	std::vector<double> weight_;
	TopologicalSort topologicalSort;
	double weight(int from, int to);
};

TopoShortestPathAlgorithm::TopoShortestPathAlgorithm(std::shared_ptr<EdgeWeightedDigraph> edgeWeightedDigraphPtr, int src):
edgeWeightedDigraphPtr_(edgeWeightedDigraphPtr), v_(edgeWeightedDigraphPtr_->V()), src_(src), 
parent_(v_,-1), weight_(v_,std::numeric_limits<double>::max()), 
topologicalSort(edgeWeightedDigraphPtr)
{
	weight_[src_] = 0;
	for (int i : topologicalSort.order())
	{	
		for (std::shared_ptr<const Edge> edgePtr: edgeWeightedDigraphPtr_->edgesOf(i))
		{
			int to = edgePtr->to();
			if (weight_[to] > weight_[i]+weight(i,to))
			{
				weight_[to] = weight_[i]+weight(i,to);
				parent_[to] = i;
			}
		}
	}
}

double TopoShortestPathAlgorithm::weight(int from, int to)
{
	for (std::shared_ptr<const Edge> edgePtr: edgeWeightedDigraphPtr_->edgesOf(from))
	{
		if (edgePtr->from()==from && edgePtr->to()==to)
		{
			return edgePtr->weight();
		}
	}
	return std::numeric_limits<double>::max();
}

double TopoShortestPathAlgorithm::weight(int x) const
{
	return weight_[x];
}

const std::vector<double> TopoShortestPathAlgorithm::weight() const
{
	return weight_;
}

} // namespace graph

#endif // __TOPOSHORTESTPATHALGORITHM_H__