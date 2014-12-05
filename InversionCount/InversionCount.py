#!/usr/bin/python

# Author: Sreejith Sreekantan

import math

def replace(begin,tmp_l):
	for x in xrange(0, len(tmp_l)):
		l[begin+x] = tmp_l[x]

def NumberOfInversions(begin, end):
	ret = 0
	if begin>= end:
		return ret
	if begin+1==end:
		if l[begin]>l[end]:
			ret = ret + 1
			tmp = l[begin]
			l[begin] = l[end]
			l[end] = tmp
		return ret
	else:
		middle = int(math.floor(((begin + end)/2)))

		ret = ret + NumberOfInversions(begin, middle)
		ret = ret + NumberOfInversions(middle+1, end)
		index1 = begin
		index2 = middle+1
		tmp_l = []
		while index1 <= middle and index2 <= end:
			if l[index1] <= l[index2]:
				tmp_l.append(l[index1])
				index1 = index1 + 1
			else:
				tmp_l.append(l[index2])
				index2 = index2 + 1
				ret = ret + (middle-index1) + 1
		while index1 <= middle:
			tmp_l.append(l[index1])
			index1 = index1 + 1
		while index2 <= end:
			tmp_l.append(l[index2])
			index2 = index2 + 1
		replace(begin,tmp_l)
		return ret

f = raw_input("file name: ")


l = [int(x) for x in file(f).read().split()]
n = NumberOfInversions(0, len(l)-1)
print n
