#!/usr/bin/env python 

import csv
from collections import namedtuple
from operator import attrgetter


def find_distance(x1, y1, x2, y2):
	return ((x2-x1)**2 + (y2-y1)**2)**(.5)


Point = namedtuple('Point', 'index x y visited')
pointlist = [] #create named tuple to store points and their coordinates

with open('example-input-1.txt', 'rb') as f:
	reader = csv.reader(f, delimiter=' ')
	for row in reader:
		pointlist.append(Point(row[0], row[1], row[2], 0));
 
print pointlist




#Notes: 

# sort list by x value
# print(sorted(pointlist, key=attrgetter('x')))


#Could we compute the nearest neighbor dynamically?
# Idea: keep a list of x and y coordinates of points and whether or not we've visited them.
# At each point, compute distance to point at nearest unvisited X coordinate point. Compare this to nearest unvisited Y coordinate point.
# Visit the one with the lower value.
