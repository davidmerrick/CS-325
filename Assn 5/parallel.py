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
import threading 

class NearestNeighbor(threading.Thread):

	Point = namedtuple('Point', 'index x y')
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
					return pointlist[j+1]
				if j == len(pointlist)-1:
					return pointlist[j-1]
				above = abs(int(pointlist[j+1].x)) - abs(int(pointlist[j].x))
				below = abs(int(pointlist[j].x)) - abs(int(pointlist[j-1].x))
				if abs(above) < abs(below):
					return pointlist[j+1]
				else:
					return pointlist[j-1]
				j+=1

	def get_nextclosest_y(pointlist, point):
#returns a point corresponding to the next closest unvisited X point
		pointlist = sorted(pointlist, key=attrgetter('y'))
        #Loop through the array until we find our current point
		j = 0
		for i in pointlist:
			if i.index == point.index:
				if j == 0: 
					return pointlist[j+1]
				if j == len(pointlist)-1:
					return pointlist[j-1]
				above = abs(int(pointlist[j+1].y)) - abs(int(pointlist[j].y))
				below = abs(int(pointlist[j].y)) - abs(int(pointlist[j-1].y))
				if abs(above) < abs(below):
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
			pointlist.append(Point(row[0], row[1], row[2]));

#Initialize visited array
	visited = []

#Visit the first node
	#random = randint(0,len(pointlist)-1)
	random = 0
	current_point = pointlist[random]

#Visit the rest of the nodes
	while(len(pointlist) > 1):
		previous_point = current_point
		visited.append(previous_point)
		closest_x = get_nextclosest_x(pointlist, previous_point)
		closest_y = get_nextclosest_y(pointlist, previous_point)
		distance_x = find_distance(previous_point, closest_x)
		distance_y = find_distance(previous_point, closest_y)
		if(distance_x < distance_y):
			current_point = closest_x
		else:
			current_point = closest_y
		pointlist.remove(previous_point)

# Add the last point to pointlist
		visited.append(pointlist.pop())

#Calculate the tour distance
	total_distance = 0
	for i in range(0, len(visited)-1):
		total_distance += find_distance(visited[i], visited[i+1])

#add on the distance from last visited point back to beginning
	total_distance += find_distance(visited[0], visited[len(visited)-1])

	print "Total distance is " + str(total_distance)
	print visited




thread1 = NearestNeighbor()
thread2 = NearestNeighbor()

thread1.start()
thread2.start()

thread1.join()
thread2.join()
