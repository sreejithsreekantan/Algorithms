/*
    Author      :       Sreejith Sreekantan
    Description :       Dijkstras' algorithm

*/

#ifndef __DIJKSTRASALGORITHM_H__
#define __DIJKSTRASALGORITHM_H__

#include "EdgeWeightedDigraph.h"
#include <algorithm>
#include <limits>
#include <queue>

#include <iostream>
using namespace std;

namespace graph
{

class DijkstrasAlgorithm
{
public:
    DijkstrasAlgorithm(EdgeWeightedDigraph &g, const int src);
    void dij_recursive(int vert);
private:
    int src_;
    int v_;
    int *parent_;
    bool *visited_;
    double *weight_;
};

class Compare
{
public:
    Compare(double *weight): weight_(weight) {}
    bool operator()(const int &a, const int &b)
    {
        return weight_[a] > weight_[b];
    }
private:
    double *weight_;
};

double weight(EdgeWeightedDigraph &g, int src, int dest)
{
    for (auto neigh : g.edgesOf(src))
    {
        if (neigh->from() == src && neigh->to() == dest)
        {
            return neigh->weight();
        }
    }
    return std::numeric_limits<double>::max();
}

DijkstrasAlgorithm::DijkstrasAlgorithm(EdgeWeightedDigraph &g, int src):
    src_(src), v_(g.V()), parent_(new int[v_]), visited_(new bool[v_]), weight_(new double[v_])
{
    std::for_each(visited_, visited_ + v_, [](bool & i)
    {
        i = false;
    } );
    std::for_each(weight_, weight_ + v_, [](double & i)
    {
        i = std::numeric_limits<double>::max();
    } );

    std::vector<int> vertToVisit;
    vertToVisit.push_back(src_);
    weight_[src_] = 0;

    while (!vertToVisit.empty())
    {
        Compare compare(weight_);
        std::make_heap(vertToVisit.begin(), vertToVisit.end(), compare);
        int vert = vertToVisit.front();
        std::pop_heap(vertToVisit.begin(), vertToVisit.end(), compare);
        vertToVisit.pop_back();
        if (*(visited_ + vert))
        {
            continue;
        }
        // cout << "vertToVisit.size() : " << vertToVisit.size() << endl;
        // cout << "vertToVisit.front() : " << vertToVisit.front() << endl;
        visited_[vert] = true;


        for (auto neigh : g.edgesOf(vert))
        {
            int to = neigh->to();
            if (!*(visited_ + to))
            {
                vertToVisit.push_back(to);
                if (*(weight_ + to) > *(weight_ + vert) + weight(g, vert, to) )
                {
                    *(weight_ + to) = *(weight_ + vert) + weight(g, vert, to);
                    *(parent_ + to) = vert;
                }
            }
        }
    }

    int x;
    x = 0;
    cout << "visited_ : ";
    std::for_each(visited_, visited_ + v_, [&](bool & i)
    {
        cout << x++ << "(" << i << ") ";
    } );
    cout << endl;
    x = 0;
    cout.precision(20);
    cout << "weight_ : ";
    std::for_each(weight_, weight_ + v_, [&](double & i)
    {
        cout << x++ << "(" << i << ") ";
    } );
    cout << endl;
    x = 0;
    cout << "parent_ : ";
    std::for_each(parent_, parent_ + v_, [&](int &i)
    {
        cout << x++ << "(" << i << ") ";
    } );
    cout << endl;
}


} // namespace graph
#endif // __DIJKSTRASALGORITHM_H__