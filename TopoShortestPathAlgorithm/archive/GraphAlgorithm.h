/*
    Author      :       Sreejith Sreekantan

*/

#ifndef __GRAPHALGORITHM_H__
#define __GRAPHALGORITHM_H__

#include "Graph.h"
#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDigraph.h"
#include <boost/dynamic_bitset.hpp>
#include <set>
#include <algorithm>

#include <iostream>

namespace graph
{

class DoNothing
{
public:
    void operator()(int i) {}
    void operator()() {}
};
DoNothing doNothing;

template<typename Func>
void dfs(Graph &graph, int i, boost::dynamic_bitset<> &visited, Func &func)
{
    visited.set(i);
    for (std::set<int>::iterator iter = graph.edgesOf(i).begin(); iter != graph.edgesOf(i).end(); ++iter)
    {
        if (!visited[*iter])
        {
            dfs(graph, *iter, visited, func);
        }
    }
    func(i);
}

template<typename Func>
void dfs(Graph &graph, Func &func = doNothing)
{
    boost::dynamic_bitset<> visited(graph.V(), 0);
    for (int i = 0; i < graph.V(); ++i)
    {
        if (!visited[i])
        {
            func();
            dfs(graph, i, visited, func);
        }
    }
}

template<typename Func>
void dfs(Graph &graph, std::vector<int> &order, Func &func = doNothing)
{
    boost::dynamic_bitset<> visited(graph.V(), 0);
    for (std::vector<int>::iterator i = order.begin(); i != order.end(); ++i)
    {
        if (!visited[*i])
        {
            func();
            dfs(graph, *i, visited, func);
        }

    }
}

class TopologicalOrderFunctor
{
public:
    TopologicalOrderFunctor(std::stack<int> &reversePostOrder): reversePostOrder_(reversePostOrder) {   }
    void operator()(int i)
    {
        reversePostOrder_.push(i);
    }
    void operator()()
    {
    }
private:
    std::stack<int> &reversePostOrder_;
};

std::unique_ptr<std::vector<int> > TopologicalOrder(Graph &graph)
{
    std::stack<int> reversePostOrder;
    TopologicalOrderFunctor topologicalOrderFunctor(reversePostOrder);
    dfs(graph, topologicalOrderFunctor);
    std::unique_ptr<std::vector<int> > topologicalOrder(new std::vector<int>());
    while (!reversePostOrder.empty())
    {
        topologicalOrder->push_back(reversePostOrder.top());
        reversePostOrder.pop();
    }
    return topologicalOrder;
}



std::unique_ptr<Graph> getGraphFromIStream(std::istream &in)
{
    int tmp;
    std::clog << "Enter input:\n";
    in >> tmp; // no of vertices
    std::unique_ptr<Graph> graph( new Graph(tmp) );
    in >> tmp; // no of edges
    int src, dest;
    for (int i = 0; i < tmp; ++i)
    {
        in >> src >> dest;
        if (!graph->addEdge(src, dest))
        {
            std::clog << "Error adding edge (" << src << " -> " << dest << ")\n";
        }
    }
    return graph;
}

std::unique_ptr<EdgeWeightedDigraph> getEdgeWeightedDigraphFromIStream(std::istream &in)
{
    int tmp;
    std::clog << "Enter input:\n";
    in >> tmp; // no of vertices
    std::unique_ptr<EdgeWeightedDigraph> graph( new EdgeWeightedDigraph(tmp) );
    in >> tmp; // no of edges
    int src, dest;
    double weight;
    for (int i = 0; i < tmp; ++i)
    {
        in >> src >> dest >> weight;
        if (!graph->addEdge(src, dest, weight))
        {
            std::clog << "Error adding edge (" << src << " -> " << dest << ")\n";
        }
    }
    return graph;
}

std::unique_ptr<EdgeWeightedGraph> getEdgeWeightedGraphFromIStream(std::istream &in)
{
    int tmp;
    std::clog << "Enter input:\n";
    in >> tmp; // no of vertices
    std::unique_ptr<EdgeWeightedGraph> graph( new EdgeWeightedGraph(tmp) );
    in >> tmp; // no of edges
    int src, dest;
    double weight;
    for (int i = 0; i < tmp; ++i)
    {
        in >> src >> dest >> weight;
        if (!graph->addEdge(src, dest, weight))
        {
            std::clog << "Error adding edge (" << src << " -> " << dest << ")\n";
        }
    }
    return graph;
}

std::unique_ptr<Graph> getUndirectedGraphFromIStream(std::istream &in)
{
    int tmp;
    std::clog << "Enter input:\n";
    in >> tmp; // no of vertices
    std::unique_ptr<Graph> graph( new Graph(tmp) );
    in >> tmp; // no of edges
    int src, dest;
    for (int i = 0; i < tmp; ++i)
    {
        in >> src >> dest;
        if (!graph->addEdge(src, dest) || !graph->addEdge(dest, src))
        {
            std::clog << "Error adding edge (" << src << " -> " << dest << ")\n";
        }
    }
    return graph;
}

void putGraphToOStream(const EdgeWeightedDigraph &edgeWeightedDigraph, std::ostream &out = std::cout)
{
    int tmp = edgeWeightedDigraph.V();
    out << tmp << std::endl;
    out << edgeWeightedDigraph.E() << std::endl;

    for (int i = 0; i < tmp; ++i)
    {
        // for_each(
        //     edgeWeightedDigraph.edgesOf(i).begin(),
        //     edgeWeightedDigraph.edgesOf(i).end(),
        //     [&](const std::shared_ptr<const DirectedEdge>& edge)
        //     {
        //         out << edge->from() << " " << edge->to() << " " << edge->weight() << std::endl;
        //     }
        // );
        for (auto edge : edgeWeightedDigraph.edgesOf(i))
        {
            out << edge->from() << " " << edge->to() << " " << edge->weight() << std::endl;
        }

    }
}


void putGraphToOStream(const EdgeWeightedGraph &edgeWeightedGraph, std::ostream &out = std::cout)
{
    int tmp = edgeWeightedGraph.V();
    out << tmp << std::endl;
    out << edgeWeightedGraph.E() << std::endl;

    // const std::vector< std::shared_ptr<Edge> >::iterator begin, end;
    for (int i = 0; i < tmp; ++i)
    {
        for_each(
            edgeWeightedGraph.edgesOf(i).begin(),
            edgeWeightedGraph.edgesOf(i).end(),
            [&](const std::shared_ptr<Edge> &edge)
        {
            out << i << " " << edge->other(i) << " " << edge->weight() << std::endl;
        }
        );

    }
}


void putGraphToOStream(const Graph &graph, std::ostream &out = std::cout)
{
    int tmp = graph.V();
    out << tmp << std::endl;
    out << graph.E() << std::endl;

    std::set<int>::iterator begin, end;
    for (int i = 0; i < tmp; ++i)
    {
        begin = graph.edgesOf(i).begin();
        end = graph.edgesOf(i).end();
        for (auto j = begin; j != end; ++j)
        {
            out << i << " " << *j << std::endl;
        }
    }
}

std::unique_ptr<Graph> reverse(const Graph &graph)
{
    std::unique_ptr<Graph> reversedGraph(new Graph(graph.V()));
    for (int i = 0; i < graph.V(); ++i)
    {
        for (std::set<int>::iterator iter = graph.edgesOf(i).begin(); iter != graph.edgesOf(i).end(); ++iter)
        {
            reversedGraph->addEdge(*iter, i);
        }
    }
    return reversedGraph;
}



//compute the degree of v

// compute maximum degree

// compute average degree

// count self-loops

}

#endif // __GRAPHALGORITHM_H__