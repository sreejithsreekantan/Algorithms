#!/usr/bin/python

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

def reverse(directedgraph):
	reversedgraph = DirectedGraph()
	for node in directedgraph.nodes():
		for neighbour in directedgraph.neighboursOf(node):
			reversedgraph.addedge(neighbour, node)
	return reversedgraph		


class TopologicalOrder(object):
	"""
	TopologicalOrder
	topological order from the graph
	"""
	def __init__(self, graph):
		super(TopologicalOrder, self).__init__()
		self.graph = graph
		self.visited = {}
		self.order = [] 
		for node in self.graph.nodes():
			self.visited[node] = False
		for node in self.graph.nodes():
			if not self.visited[node]:	
				self.getorderfrom(node)
		self.order.reverse()		
	
	'''
	 recursive version
	'''  	
	# def getorderfrom(self, node):
	# 	self.visited[node] = True
		
	# 	for neighbour in self.graph.neighboursOf(node):
	# 		if not self.visited[neighbour]:
	# 			self.getorderfrom(neighbour)
		
	# 	self.order.append(node)	

	'''
	 iterative version to avoid the below error:
	 RuntimeError: maximum recursion depth exceeded	
	'''
	def getorderfrom(self, node):
		self.visited[node] = True
		stack = []
		toremove = []
		stack.append(node)
		while stack:
			top = stack[len(stack)-1]
			if top in toremove:
				self.order.append(top)
				toremove.remove(top)
				stack.pop()
				continue
			else:	
				toremove.append(top)
			for neighbour in self.graph.neighboursOf(top):
				if not self.visited[neighbour]:
					self.visited[neighbour]=True
					stack.append(neighbour)


		
		
	
	def topologicalorder(self):
		return self.order
					
	
class KosarajuAlgorithm(object):
	"""docstring for KosarajuAlgorithm"""
	def __init__(self, graph):
		super(KosarajuAlgorithm, self).__init__()
		self.graph = graph
		self.reversedgraph = reverse(graph)
		self.visited = {}
		self.stronggroups = []
		for node in self.graph.nodes():
			self.visited[node] = False
		order = (TopologicalOrder(self.reversedgraph)).topologicalorder()
		for node in order:
			if not self.visited[node]:
				self.stronggroups.append([])
				self.visitallreachablefrom(node)
	'''
	recursive version
	'''							
	# def visitallreachablefrom(self, node):
	# 	self.visited[node] = True
	# 	latestgroup = len(self.stronggroups) - 1
	# 	self.stronggroups[latestgroup].append(node)
	# 	for neighbour in self.graph.neighboursOf(node):
	# 		if not self.visited[neighbour]:
	# 			self.visitallreachablefrom(neighbour)

	'''
	iterative version
	'''			
	def visitallreachablefrom(self, node):
		latestgroup = len(self.stronggroups) - 1
		stack = []
		stack.append(node)
		self.visited[node] = True
		while stack:
			top = stack.pop()
			
			self.stronggroups[latestgroup].append(top)
			for neighbour in self.graph.neighboursOf(top):
				if not self.visited[neighbour]:
					self.visited[neighbour] = True
					stack.append(neighbour)


	def groups(self):
		return self.stronggroups			

g = DirectedGraph("inp.txt")

g.display()
t = TopologicalOrder(g)
print t.topologicalorder() 
print reverse(g).display()
groups =  KosarajuAlgorithm(g).groups()
print groups
