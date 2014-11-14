class DirectedGraph(object):
    """
    DirectedGraph
        Graph with directed edges using adjacency list for internal implementation
    """

    def __init__(self, filename = None):
        super(DirectedGraph, self).__init__()
        self.adjacencylist = {}
        if filename is not None: 
            self.filename = filename
            self.inputtext = open(self.filename).readlines()
            for line in self.inputtext:
                nodes = [int(x) for x in line.split()]
                if nodes[0] not in self.adjacencylist:
                    self.adjacencylist[nodes[0]] = []
                [self.addedge(nodes[0], x) for x in nodes[1:]]

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
    
    def addedge(self, fromn, to):
        self.addnode(fromn)
        self.addnode(to)
        self.adjacencylist[fromn].append(to)                    
