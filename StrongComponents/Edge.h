/*
    Author      :       Sreejith Sreekantan

*/

#ifndef __EDGE_H__
#define __EDGE_H__

namespace graph
{

class Edge
{
public:
	Edge(int u, int v, double weight): u_(u), v_(v), weight_(weight) {}
	int either() const { return u_; }
	int other(int x) const { return (x==u_?v_:u_); }
	double weight() const { return weight_; }
private:
	int u_,v_;
	double weight_;
};

} // namespace graph
#endif // __EDGE_H__