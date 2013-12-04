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
from random import randint
import threading 

class FuncThread(threading.Thread):
    def __init__(self, target, *args):
        self._target = target
        self._args = args
        threading.Thread.__init__(self)
 
    def run(self):
        self._target(*self._args)
 
# Example usage
def someOtherFunc(data, key):
    print "someOtherFunc was called : data=%s; key=%s" % (str(data), str(key))
 
t1 = FuncThread(someOtherFunc, [1,2], 6)
t2 = FuncThread(someOtherFunc, [1,2], 6)
t2.start()
t1.start()
t1.join()
t1.join()