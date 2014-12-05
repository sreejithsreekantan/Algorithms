#ifndef __CONNECTEDCOMPONENTS_H__
#define __CONNECTEDCOMPONENTS_H__

#include "Graph.h"
#include <stack>
#include <boost/dynamic_bitset.hpp>
#include <algorithm>
#include <cassert>

namespace graph
{

class ConnectedComponents
{
public:
    ConnectedComponents(Graph &graph);
    int connectedComponentsCount()
    {
        return count_;
    }
    int componentID(int i)
    {
        assert(i >= 0 && i < v_.size());
        return v_[i];
    }

private:
    std::vector<int> v_;
    int count_; // connected components count
};


ConnectedComponents::ConnectedComponents(Graph &graph): v_(graph.V(), -1), count_(0)
{

    boost::dynamic_bitset<> visited(graph.V());
    visited.reset();
    std::stack<int> neighbours;
    int tmp;
    for (int i = 0; i < graph.V(); ++i)
    {
        if (!visited[i])
        {
            ++count_;
            neighbours.push(i);
            while (!neighbours.empty())
            {
                tmp = neighbours.top();
                neighbours.pop();
                v_[tmp] = count_;
                visited.set(tmp);
                for (auto iter = std::begin(graph.edgesOf(tmp)); iter != std::end(graph.edgesOf(tmp)); iter++)
                {
                    if (!visited[*iter])
                    {
                        neighbours.push(*iter);
                    }
                }
            }
        }
    }
}
}
#endif // __CONNECTEDCOMPONENTS_H__