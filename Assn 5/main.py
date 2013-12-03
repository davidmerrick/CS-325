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

def get_nextclosest_x(pointlist, point):
	print "point index = " + str(point.index)
	#returns a point corresponding to the next closest unvisited X point
	pointlist = sorted(pointlist, key=attrgetter('x'))
	#Loop through the array until we find our current point
	for i in pointlist:
		#To do: not sure how to compare these namedtuple objects
		if i.index == point.index:
			break
	return i


with open('example-input-1.txt', 'rb') as f:
	reader = csv.reader(f, delimiter=' ')
	for row in reader:
		pointlist.append(Point(row[0], row[1], row[2], 0));
 
print "Original point is " + str(pointlist[5])
print "point that it found is " + str(get_nextclosest_x(pointlist, pointlist[5]))