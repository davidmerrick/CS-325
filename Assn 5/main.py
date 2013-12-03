#!/usr/bin/env python 

# Notes: 
#
# Could we compute the nearest neighbor dynamically?
# Idea: keep a list of x and y coordinates of points and whether or not we've visited them.
# At each point, compute distance to point at nearest unvisited X coordinate point. Compare this to nearest unvisited Y coordinate point.
# Visit the one with the lower value.
#
# I decided to use a list of named tuples to track the cities.
# How to sort list by x value
# print(sorted(pointlist, key=attrgetter('x')))

import csv
from collections import namedtuple
from operator import attrgetter

Point = namedtuple('Point', 'index x y visited')
pointlist = [] #create named tuple to store points and their coordinates

def find_distance(x1, y1, x2, y2):
	return ((x2-x1)**2 + (y2-y1)**2)**(.5)

def mark_visited(pointlist, point):
	#Marks a point as visited
	j = 0
	for i in pointlist:
		if i.index == point.index:
			pointlist[j] = pointlist[j]._replace(visited = 1)
			break
		j+=1
	return pointlist

def visited(point):
	#A boolean that returns true if point has been visited
	if point.visited == 0:
		return false
	return true

def get_nextclosest_x(pointlist, point):
	#returns a point corresponding to the next closest unvisited X point
	pointlist = sorted(pointlist, key=attrgetter('x'))
	#Loop through the array until we find our current point
	for i in pointlist:
		if i.index == point.index:
			break
	return i

with open('example-input-1.txt', 'rb') as f:
	reader = csv.reader(f, delimiter=' ')
	for row in reader:
		pointlist.append(Point(row[0], row[1], row[2], 0));
 
pointlist = mark_visited(pointlist, pointlist[0])
print pointlist 