/*
	Author			:		Sreejith Sreekantan
	Description		:		Edge
*/


#ifndef __EDGE_H__
#define __EDGE_H__

namespace graph
{

class Edge
{
public:
	Edge(int from, int to, double weight);
	double weight() const;
	int from() const;
	int to() const;

private:
	int from_, to_;
	double weight_;
};

Edge::Edge(int from, int to, double weight):
from_(from), to_(to), weight_(weight)
{
}

double Edge::weight() const
{
	return weight_;
}

int Edge::from() const
{
	return from_;
}

int Edge::to() const
{
	return to_;
}

} // namespace graph

#endif // __EDGE_H__