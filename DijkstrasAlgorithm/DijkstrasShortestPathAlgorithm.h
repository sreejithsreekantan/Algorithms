/*
    Author          :           Sreejith Sreekantan
    Description     :           Dijkstra's shortest path algorithm
*/

#ifndef __DIJKSTRASSHORTESTPATHALGORITHM_H__
#define __DIJKSTRASSHORTESTPATHALGORITHM_H__

#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include "EdgeWeightedDigraph.h"

namespace graph
{

class DijkstrasShortestPathAlgorithm
{
public:
    DijkstrasShortestPathAlgorithm(std::shared_ptr<EdgeWeightedDigraph> g_sh_ptr, int src);
    const std::vector<double>& weight() const;
    double weight(int a) const;

private:
    std::shared_ptr<EdgeWeightedDigraph> graph_sh_ptr_;
    int v_;
    int src_;
    std::vector<double> weight_;
    std::vector<bool> visited_;
    std::vector<int> parent_;

    double weight(int a, int b);
};

class Compare
{
public:
    Compare(std::vector<double> &weight): weight_(weight) {}
    bool operator()(int &a, int &b)
    {
        return weight_[a] > weight_[b];
    }
private:
    std::vector<double> &weight_;
};

DijkstrasShortestPathAlgorithm::DijkstrasShortestPathAlgorithm(std::shared_ptr<EdgeWeightedDigraph> g_sh_ptr, int src):
    graph_sh_ptr_(g_sh_ptr), v_(graph_sh_ptr_->V()), src_(src), weight_(v_, std::numeric_limits<double>::max()), visited_(v_, false), parent_(v_, -1)
{
    weight_[src_] = 0;
    std::vector<int> toVisit;
    toVisit.push_back(src_);

    while (!toVisit.empty())
    {
        Compare compare(weight_);
        std::make_heap(toVisit.begin(), toVisit.end(), compare );
        int nearest = toVisit.front();
        std::pop_heap(toVisit.begin(), toVisit.end(), compare );
        toVisit.pop_back();

        if (visited_[nearest])
        {
            continue;
        }

        visited_[nearest] = true;
        for (std::shared_ptr<const Edge> edge_ptr : graph_sh_ptr_->edgesOf(nearest))
        {
            int to = edge_ptr->to();
            if (weight_[to] > weight_[nearest] + weight(nearest, to) )
            {
                weight_[to] = weight_[nearest] + weight(nearest, to);
                parent_[to] = nearest;
            }
            if (!visited_[to])
            {
                toVisit.push_back(to);
            }
        }

    }
}

double DijkstrasShortestPathAlgorithm::weight(int a, int b)
{
    for (std::shared_ptr<const Edge> edge_ptr : graph_sh_ptr_->edgesOf(a))
    {
        if (edge_ptr->from() == a && edge_ptr->to() == b)
        {
            return edge_ptr->weight();
        }
    }
    return std::numeric_limits<double>::max();
}

const std::vector<double>& DijkstrasShortestPathAlgorithm::weight() const
{
	return weight_;
}

double DijkstrasShortestPathAlgorithm::weight(int a) const
{
	return weight_[a];
}

} // namespace graph

#endif // __DIJKSTRASSHORTESTPATHALGORITHM_H__