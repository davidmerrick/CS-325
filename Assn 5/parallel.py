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
#
# How this progam works:
# 1. Parses input file into list.
# 2. Chooses random point to pull from array.
# 3. Pop this point out of array into separate array of visited nodes.
# 4. Keep visiting the next closest place while you haven't visited all the nodes.
# 5. Finally, use the visited array to calculate total tour

import csv
from collections import namedtuple
from operator import attrgetter
import random
import threading 
import linecache

Point = namedtuple('Point', 'index x y')
Path = namedtuple('Path', 'length points')
result_array = []

def find_distance(point1, point2):
        distance = ((int(point2.x)-int(point1.x))**2 + (int(point2.y)-int(point1.y))**2)**(.5)
	#round to nearest integer
	return round(distance)

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

def nearest_neighbor(pointlist, starting_point):
        global result_array
        visited = []

        pathstring = "" + starting_point.index

        #Visit the first node
        current_point = starting_point

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
                pathstring += " " + current_point.index
                pointlist.remove(previous_point)

        # Add the last point to pointlist
        last_point = pointlist.pop()
        visited.append(last_point)

        #to do: keep track of total distance within the loop that calculates the next point.
        #Calculate the tour distance
        total_distance = 0
        for i in range(0, len(visited)-1):
                total_distance += find_distance(visited[i], visited[i+1])

        #add on the distance from last visited point back to beginning
        total_distance += find_distance(visited[0], visited[len(visited)-1])

        #append results to array
        result_array.append(Path(total_distance, pathstring))

class FuncThread(threading.Thread):
    def __init__(self, target, *args):
        self._target = target
        self._args = args
        threading.Thread.__init__(self)
 
    def run(self):
        self._target(*self._args)



# Parse the input file
pointlist = [] #create named tuple to store points and their coordinates
inputfile = 'example-input-1.txt'

#with open(inputfile, 'rb') as f:
#        reader = csv.reader(f, delimiter=' ')
#        for row in reader:
#                pointlist.append(Point(row[0], row[1], row[2]))

f = open(inputfile)
for row in f:
	row = row.strip().split()
	pointlist.append(Point(row[0], row[1], row[2]))
f.close()

        
# Generate a list of unique random starting points
n_range = (len(pointlist)-1)/2 # Number of threads we want. Must be less than len(pointlist) - 1

for i in range(n_range):
    starting_points = random.sample(pointlist, len(pointlist)-1);

#Spawn the threads
threads = []
for i in range(n_range):
    thread = FuncThread(nearest_neighbor, list(pointlist), starting_points[i])
    thread.start()
    threads.append(thread)

for i in range(n_range):
    threads[i].join()

result_array = sorted(result_array, key=attrgetter('length'))

print "shortest path:"
print result_array[0]


#write results to output file
output = open('output.txt','w')
output.write(str(int(result_array[0].length))+'\n')

for i in result_array[0].points.strip().split():
	#output.write(linecache.getline(inputfile, int(i)+1))

	#actually just need city identifier #
	output.write(i+'\n')

output.close()
