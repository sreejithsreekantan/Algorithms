/*
    Author      :       Sreejith Sreekantan
    Description :       Bellman Ford algorithm
*/

#ifndef __BELLMANFORDALGORITHM_H__
#define __BELLMANFORDALGORITHM_H__

#include "EdgeWeightedDigraph.h"
#include <limits>

#include <iostream>
using namespace std;

namespace graph
{

class BellmanFordAlgorithm
{
public:
    BellmanFordAlgorithm(EdgeWeightedDigraph &g, int src);

private:
    EdgeWeightedDigraph &g_;
    int src_;
    int v_;
    double *weight_;
    bool *visited_;
    int *parent_; 

    void relax(int v);
    double weight(int src, int dest) const;
};

BellmanFordAlgorithm::BellmanFordAlgorithm(EdgeWeightedDigraph &g, int src):
g_(g), src_(src), v_(g.V()), weight_(new double[v_]), parent_(new int[v_]), visited_(new bool[v_])
{
	std::for_each(weight_, weight_+v_, [](double& val) {val = std::numeric_limits<double>::max();});
	std::for_each(visited_, visited_+v_, [](bool& val) {val = false;});
	std::for_each(parent_, parent_+v_, [](int& val) {val = -1;});

	weight_[src_] = 0;
	for (int i = 0; i < v_; ++i)
	{
		for (int j = 0; j < v_; ++j)
		{
			relax(j);
		}
	}
	int x;
	x=0; cout << "weight_ : ";std::for_each(weight_, weight_+v_, [&](double& val) {cout << x++ << "(" << val << ")";});
	cout << endl;x=0; cout << "visited_ : ";std::for_each(visited_, visited_+v_, [&](bool& val) {cout << x++ << "(" << val << ")";});
	cout << endl;x=0; cout << "parent_ : ";std::for_each(parent_, parent_+v_, [&](int& val) {cout << x++ << "(" << val << ")";});
}

void BellmanFordAlgorithm::relax(int v)
{
	int to;
	for (auto neigh : g_.edgesOf(v))
	{
		to = neigh->to();
		if (*(weight_+to) > *(weight_+v)+weight(v,to))
		{
			*(weight_+to) = *(weight_+v)+weight(v,to);
			parent_[to] = v;
		}
	}
}

double BellmanFordAlgorithm::weight(int src, int dest) const
{
	for (auto neigh : g_.edgesOf(src))
	{
		if (neigh->from()==src && neigh->to()==dest)
		{
			return neigh->weight();
		}
	}
	return std::numeric_limits<double>::max();
}

} // namespace graph

#endif // __BELLMANFORDALGORITHM_H__