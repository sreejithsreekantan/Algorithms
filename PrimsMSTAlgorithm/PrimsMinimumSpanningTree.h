/*
    Author      :       Sreejith Sreekantan
    Description :       Prim's Algorithm Implementation
*/

#ifndef __MINIMUMSPANNINGTREE_H__
#define __MINIMUMSPANNINGTREE_H__

#include <vector>
#include <queue>
#include "EdgeWeightedGraph.h"
#include <boost/dynamic_bitset.hpp>


#include <iostream>
using namespace std;


namespace graph
{
class PrimsMinimumSpanningTree
{
public:
    PrimsMinimumSpanningTree(EdgeWeightedGraph &edgeWeightedGraph);
    const std::vector< std::shared_ptr<const Edge> > &edges();
private:
    std::vector< std::shared_ptr<const Edge> > edges_;
};

bool operator<(const std::shared_ptr<const Edge> &sptr_e1, const std::shared_ptr<const Edge> &sptr_e2)
{
    return sptr_e1->weight() > sptr_e2->weight();
}

PrimsMinimumSpanningTree::PrimsMinimumSpanningTree(EdgeWeightedGraph &edgeWeightedGraph)
{
    std::priority_queue< std::shared_ptr<const Edge> > pq, pqtmp;
    boost::dynamic_bitset<> addedToMST( edgeWeightedGraph.V() );
    addedToMST.reset();
    // adding all edges starting from zero
    for_each(
        edgeWeightedGraph.edgesOf(0).begin(),
        edgeWeightedGraph.edgesOf(0).end(),
        [&](const std::shared_ptr<Edge> &edge)
    {
        pq.push(edge);
    }
    );
    addedToMST.set(0);

    int u, v, tmp;


    while ( edgeWeightedGraph.V() > addedToMST.count() )
    {
        std::shared_ptr< const Edge > top = pq.top();
        u = top->either();
        v = top->other(u);
        pq.pop();


        tmp = -1;
        if (!addedToMST[u])
        {
            tmp = u;
        }
        else if (!addedToMST[v])
        {
            tmp = v;
        }
        if (tmp != -1)
        {
            for_each(
                edgeWeightedGraph.edgesOf(tmp).begin(),
                edgeWeightedGraph.edgesOf(tmp).end(),
                [&](const std::shared_ptr<Edge> &edge)
            {

                if (!addedToMST[edge->other(tmp)])
                {
                    pq.push(edge);
                }
            }
            );
            edges_.push_back(top);
            addedToMST.set(tmp);
        }
        

        pqtmp = pq;
        while (!pqtmp.empty())
        {
            pqtmp.pop();
        }
    }
}

const std::vector< std::shared_ptr<const Edge> > &PrimsMinimumSpanningTree::edges()
{
    return edges_;
}

} // namespace graph
#endif // __MINIMUMSPANNINGTREE_H__