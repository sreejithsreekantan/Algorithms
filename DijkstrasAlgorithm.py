#!/usr/bin/python

import heapq

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
        self.graph = WeightedDirectedGraph
        self.source = source
        self.heap = []
        self.weighttonode = {}
        self.parent = {}
        self._run()
        print self.parent
        print self.weighttonode


    def _run(self):
        heapq.heappush(self.heap, (0, self.source))
        self.weighttonode[self.source] = 0
        self.parent[self.source] = self.source
        while self.heap:
            nearestweightandnode = heapq.heappop(self.heap)
            nearestnode = nearestweightandnode[1]
            self._relaxneighboursof(nearestnode)
            
    def _relaxneighboursof(self, nearestnode):

        nearestweight = self.weighttonode[nearestnode]
        for neighbournodeandweight  in self.graph.neighboursOf(nearestnode):
            neighbour = neighbournodeandweight[0]
            weight = neighbournodeandweight[1]
            weighttoneighbour = nearestweight + weight
            prevweighttoneighbour = self.weighttonode.get(neighbour, -1)
            
            if prevweighttoneighbour != -1 and weighttoneighbour < prevweighttoneighbour:
                index = self._indexinheap(neighbour)
                self.heap[index] = self.heap[-1]
                self.heap.pop()
                # heapq._siftup(self.heap, index)
                heapq.heapify(self.heap)
                  
            if prevweighttoneighbour == -1 or weighttoneighbour < prevweighttoneighbour:
                heapq.heappush(self.heap, (weighttoneighbour, neighbour))   
                self.weighttonode[neighbour] = weighttoneighbour
                self.parent[neighbour] = nearestnode 
    
    def _indexinheap(self, node):
        index = -1
        for weightandnode in self.heap:
            index += 1
            if weightandnode[1] == node:
                print len(self.heap),weightandnode, index 
                return index    
        assert(index!=-1)        
        return index                

    def weightto(self, node):
        return self.weighttonode[node]   
    
    def pathto(self, node):
        path = []
        self._pathto(node, path)
        return path

    def _pathto(self, node, path):
        if self.parent[node]==node:
            path.append(node)
            return
        self.pathto(self.parent[node], path)
        path.append(node)
        



# g = WeightedDirectedGraph("dijinp1.txt")
g = WeightedDirectedGraph("dijkstraData.txt")
# g.display()

d = DijkstrasAlgorithm(g, 1)
print "Weight to travel from node 1 to node 27 is ", d.weightto(27)
