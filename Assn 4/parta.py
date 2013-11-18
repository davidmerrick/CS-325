#!/usr/bin/env python 

#from pulp import *

def find_slope(x1, y1, x2, y2):
		return ((y2-y1)/(x2-x1))

xs = [1, 2, 3, 5, 7, 8, 10]
ys = [3, 5, 7, 11, 14, 15, 19]

n = len(xs)
min_slope = max_slope = find_slope(xs[0], ys[0], xs[1], ys[1])
for i in range(1, n):
	for j in range(i+1, n):
		slope = find_slope(xs[i], ys[i], xs[j], ys[j])
		if(slope < min_slope):
			min_slope = slope
		if(slope > max_slope):
			max_slope = slope


print "min slope is " + str(min_slope)
print "max slope is " + str(max_slope)
