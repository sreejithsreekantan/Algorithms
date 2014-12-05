#ifndef __TOPOLOGICALSORTSHORTESTPATH_H__
#define __TOPOLOGICALSORTSHORTESTPATH_H__

#include "EdgeWeightedDigraph.h"
#include <limits>
#include <vector>
#include <stack>

#include <iostream>
using namespace std;

namespace graph
{

class TopologicalSortShortestPathAlgorithm
{
public:
    TopologicalSortShortestPathAlgorithm(graph::EdgeWeightedDigraph &g, int src);



private:
    graph::EdgeWeightedDigraph &g_;
    int src_;
    int v_;
    double *weight_;
    bool *visited_;
    int *parent_;
    vector<int> topologicalOrder;
    stack<int> reversePostOrder;

    void readyTopologicalOrder();
    void readyTopologicalOrder(int vert);
    double weight(int src, int dest);
};

TopologicalSortShortestPathAlgorithm::TopologicalSortShortestPathAlgorithm(graph::EdgeWeightedDigraph &g, int src):
    g_(g), src_(src), v_(g.V()), weight_(new double[v_]), visited_(new bool[v_]), parent_(new int[v_])
{
    readyTopologicalOrder();
    for_each(visited_, visited_ + v_, [](bool & val)
    {
        val = false;
    });
    for_each(weight_, weight_ + v_, [](double & val)
    {
        val = std::numeric_limits<double>::max();
    });
    for_each(parent_, parent_ + v_, [](int &val)
    {
        val = -1;
    });

    *(weight_+ src_) = 0;
    for (int vert : topologicalOrder)
    {
    	cout << vert << endl;
        for (auto neigh : g_.edgesOf(vert))
        {
        	int to = neigh->to();
            if (*(weight_ + to) > *(weight_ + vert) + weight(vert,to) )
            {
                *(weight_ + to) = *(weight_ + vert) + weight(vert,to);
                parent_[to] = vert;
            }
        }

    }

    int x;
    x = 0; cout << "visited_ : ";
    for_each(visited_, visited_ + v_, [&](bool & val)
    {
        cout << x++ << "(" << val << ") ";
    });
    cout << endl;
    x = 0; cout << "weight_ : ";
    for_each(weight_, weight_ + v_, [&](double & val)
    {
        cout << x++ << "(" << val << ") ";
    });
    cout << endl;
    x = 0; cout << "parent_ : ";
    for_each(parent_, parent_ + v_, [&](int &val)
    {
        cout << x++ << "(" << val << ") ";
    });
    cout << endl;
}

double TopologicalSortShortestPathAlgorithm::weight(int src, int dest)
{	
	for (auto neigh : g_.edgesOf(src))
    {
    	if (neigh->from()==src && neigh->to()==dest)
    	{
    		return neigh->weight();
    	}
    }
    return numeric_limits<double>::max();
}

void TopologicalSortShortestPathAlgorithm::readyTopologicalOrder()
{
    for_each(visited_, visited_ + v_, [](bool & val)
    {
        val = false;
    });
    for (int i = 0; i < v_; ++i)
    {
        if (!*(visited_ + i))
        {
            readyTopologicalOrder(i);
        }
    }
    while (!reversePostOrder.empty())
    {
        topologicalOrder.push_back(reversePostOrder.top());
        reversePostOrder.pop();
    }
}

void TopologicalSortShortestPathAlgorithm::readyTopologicalOrder(int vert)
{
    *(visited_ + vert) = true;
    for (auto neigh : g_.edgesOf(vert))
    {
        int to = neigh->to();
        if (!*(visited_ + to))
        {
            readyTopologicalOrder(to);
        }
    }
    reversePostOrder.push(vert);
}

} // namespace graph

#endif // __TOPOLOGICALSORTSHORTESTPATH_H__