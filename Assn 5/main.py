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
from random import randint

Point = namedtuple('Point', 'index x y visited')
pointlist = [] #create named tuple to store points and their coordinates

def find_distance(point1, point2):
	return ((int(point2.x)-int(point1.x))**2 + (int(point2.y)-int(point1.y))**2)**(.5)

def visited(point):
	#A boolean that returns true if point has been visited
	if point.visited == 0:
		return false
	return true

def get_nextclosest_x(pointlist, point):
        #returns a point corresponding to the next closest unvisited X point
        pointlist = sorted(pointlist, key=attrgetter('x'))
        #Loop through the array until we find our current point
        j = 0
        for i in pointlist:
                if i.index == point.index:
                        if j == 0: 
                                if(pointlist[j+1] is None):
                                        print "j == 0 and pointlist[j+1] is None"
                                return pointlist[j+1]
                        if j == len(pointlist):
                                if(pointlist[j-1] is None):
                                        print "j == len(pointlist) and pointlist[j-1] is None"
                                return pointlist[j-1]
                        above = int(pointlist[j+1].x) - int(pointlist[j].x)
                        below = int(pointlist[j].x) - int(pointlist[j-1].x)
                        print "Above = " + above
                        print "Below = " + below
                        if above < below:
                                if(pointlist[j+1] is None):
                                        print "above < below and pointlist[j+1] is None"
                                return pointlist[j+1]
                        else:
                                if(pointlist[j-1] is None):
                                        print "above <= below and pointlist[j+1] is None"
                                return pointlist[j-1]
                j+=1

def get_nextclosest_y(pointlist, point):
        #returns a point corresponding to the next closest unvisited X point
        pointlist = sorted(pointlist, key=attrgetter('y'))
        #Loop through the array until we find our current point
        j = 0
        for i in pointlist:
                if i.index == point.index:
                        above = int(pointlist[j+1].y) - int(pointlist[j].y)
                        below = int(pointlist[j].y) - int(pointlist[j-1].y)
                        if above < below:
                                return pointlist[j+1]
                        else:
                                return pointlist[j-1]
                j+=1

# How this main loop works:
# 1. Parses input file into list.
# 2. Chooses random point to pull from array.
# 3. Pop this point out of array into separate array of visited nodes.
# 4. Keep visiting the next closest place while you haven't visited all the nodes.
# 5. Finally, use the visited array to calculate total tour

# Parse the input file

with open('example-input-1-short.txt', 'rb') as f:
	reader = csv.reader(f, delimiter=' ')
	for row in reader:
		pointlist.append(Point(row[0], row[1], row[2], 0));

#Initialize visited array
visited = []

#Visit the first node
random = randint(0,len(pointlist)-1)
visited.append(pointlist[random])
pointlist.pop(random)

#Visit the rest of the nodes
while(len(pointlist) > 1):
	#Choose where to go next based on the last point
	previous_point = visited[len(visited)-1]
	if(previous_point is None): #catches it
                print "previous point is null"
        closest_x = get_nextclosest_x(pointlist, previous_point)
	#closest_y = get_nextclosest_y(pointlist, previous_point)
	if(closest_x is None):
                print "closest_x is null"
                break
        else:
                print "closest x: " + closest_x
                break
        #distance_x = find_distance(previous_point, closest_x) #problem is here
	#distance_y = find_distance(previous_point, closest_y)
	#if(distance_x < distance_y):
	#	next_point = closest_x
	#else:
	#	next_point = closest_x
	#visited.append(next_point)
	#pointlist.remove(next_point)

# Add the last point to pointlist
visited.append(pointlist.pop())

#Calculate the tour distance
total_distance = 0
for i in range(0, len(visited)-2):
	total_distance += find_distance(visited[i], visited[i+1])

#add on the distance from last visited point back to beginning
total_distance += find_distance(visited[0], visited[len(visited)-1])