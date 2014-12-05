/*
    Author      :       Sreejith Sreekantan

*/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <cassert>
#include <sstream>

namespace graph
{

class Graph
{
public:
    int V() const
    {
        return v_;
    }
    int E() const
    {
        return e_;
    }
    Graph(int v = 0): v_(v), e_(0), edges_(v_, std::set<int>() ) {}
    bool addEdge(int u, int v);
    bool removeEdge(int u, int v);
    const std::set<int> &edgesOf(int u) const ;
private:
    int v_;
    int e_;
    std::vector<std::set<int>> edges_;
};

bool Graph::addEdge(int u, int v)
{
    if (u >= 0 && u < v_ && v >= 0 && v < v_)
    {
        edges_[u].insert(v);
        ++e_;
        return true;
    }
    return false;
}

bool Graph::removeEdge(int u, int v)
{
    if (u >= 0 && u < v_ && v >= 0 && v < v_)
    {
        edges_[u].erase(v);
        --e_;
        return true;
    }
    return false;
}
const std::set<int> &Graph::edgesOf(int u) const
{
    assert(u >= 0 && u < v_);
    return edges_[u];
}

}

#endif // __GRAPH_H__