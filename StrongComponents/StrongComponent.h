#ifndef __STRONGCOMPONENT_H__
#define __STRONGCOMPONENT_H__

#include "Graph.h"
#include "GraphAlgorithm.h"
#include <memory>
#include <vector>

namespace graph
{

class SetComponentIDFunctor
{
public:
    SetComponentIDFunctor(std::vector<int> &strongCompID, int ID = -1): strongCompID_(strongCompID), ID_(ID) { }
    void operator()(int vertex)
    {
        strongCompID_[vertex] = ID_;
    }
    void operator()()
    {
        incrementID();
    }
    void incrementID(int ID = 1) { ID_+=ID; }
    int getID() { return ID_; }
private:
    int ID_;
    std::vector<int> &strongCompID_;
};

class StrongComponent
{
public:
    StrongComponent(Graph &graph);
    const std::vector<int>& getComponentIDSet();
private:
    int numOfStrongComponents_;
    std::vector<int> strongCompID_;
};



StrongComponent::StrongComponent(Graph &graph): strongCompID_(graph.V(), -1), numOfStrongComponents_(-1)
{
    std::unique_ptr<Graph> reversedGraph(graph::reverse(graph));
    std::unique_ptr<std::vector<int> > topolOrderOfReversedGraph( graph::TopologicalOrder(*reversedGraph) );

    SetComponentIDFunctor setComponentIDFunctor(strongCompID_);

    graph::dfs(graph, *topolOrderOfReversedGraph, setComponentIDFunctor);

    numOfStrongComponents_ = setComponentIDFunctor.getID()+1;

}

const std::vector<int>& StrongComponent::getComponentIDSet()
{
	return strongCompID_;
}

}
#endif // __STRONGCOMPONENT_H__