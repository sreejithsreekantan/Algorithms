/*
	Author		:		Sreejith Sreekantan
	Description	:		Directed edge
						represents a weighted edge between two vertices
*/
#ifndef __DIRECTEDEDGE_H__
#define __DIRECTEDEDGE_H__

namespace graph
{

class DirectedEdge
{
public:
	DirectedEdge(int from, int to, double weight): from_(from), to_(to), weight_(weight) {}
	int from() const { return from_; }
	int to() const { return to_; }
	double weight() const { return weight_; }

private:
	int from_, 		// vertex from where the edge starts
		to_;		// vertex where edge ends
	double weight_;	// weight of the edge
};

}

#endif // __DIRECTEDEDGE_H__