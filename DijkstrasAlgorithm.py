#!/usr/bin/python

class WeightedDirectedGraph(object):
    """
    DirectedGraph
        Graph with directed edges using adjacency list for internal implementation
    """

    def __init__(self, filename = None):
        super(WeightedDirectedGraph, self).__init__()
        self.adjacencylist = {}
        if filename is not None: 
            self.filename = filename
            self.inputtext = open(self.filename).readlines()
            for line in self.inputtext:
                nodes = [x for x in line.split()]
                fromnode = int(nodes[0])
                tonodes = nodes[1:]
                self.addnode(fromnode)
                [self.addedge(fromnode, int(x.split(',')[0]), int(x.split(',')[1])) for x in tonodes]

    def display(self):
        print self.adjacencylist         

    def nodes(self):
        return self.adjacencylist.keys()

    def neighboursOf(self, node):
        if node in self.adjacencylist:
            return self.adjacencylist[node] 
        return []
    
    def addnode(self, node):
        if node not in self.adjacencylist:
            self.adjacencylist[node] = []
    
    def addedge(self, fromn, to, weight):
        self.addnode(fromn)
        self.addnode(to)
        self.adjacencylist[fromn].append([to,weight])                    


class DijkstrasAlgorithm(object):
    """
    DijkstrasAlgorithm to find single-source-shortest-path.
    """
    def __init__(self, WeightedDirectedGraph, source):
        super(DijkstrasAlgorithm, self).__init__()
        self.directedweightedgraph = WeightedDirectedGraph
        self.source = source
        self.heap = []
        self.run()

    def run(self):
        for weightededge in graph.neighboursOf(source):
            heapq.heappush(self.heap, (weightededge[1], weightededge[0]))
        self.dijkstraalgo()

    def dijkstraalgo(self):
        while self.heap:
            weightededge = heapq.heappop(self.heap)
            currentweight = weightededge[0]
            currentnode = weightededge[1]
            self.relaxneighboursof(currentnode, currentweight)
            pass
    def relaxneighboursof(node, weighttillnode):
        for weightededge in graph.neighboursOf(source):
        


g = WeightedDirectedGraph("inp1.txt")
# g = WeightedDirectedGraph("dijkstraData.txt")


g.display()

