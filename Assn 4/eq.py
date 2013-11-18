#!/usr/bin/env python 

#from pulp import *

xs = [1, 2, 3, 5, 7, 8, 10]
ys = [3, 5, 7, 11, 14, 15, 19]

n = len(xs)

for i in range (1, n):
	print "a" + str(xs[i]) + " + b - " + str(ys[i])
