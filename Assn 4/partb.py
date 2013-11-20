from pulp import *

import math

import csv

d = [] #days
T = [] #average temps


with open('Corvallis.csv', 'rb') as f:
    reader = csv.reader(f, delimiter=';')
    for row in reader:
            avg = row[7].strip()
            if(not avg.isalpha()):
                    T.append(float(avg))
            day = row[8].strip()
            if(not day.isalpha()):
                    d.append(float(day))

n = len(d)

#Initialize LpProblem
prob = LpProblem("Best Fit Line Problem", LpMinimize)

#Set decision variables
Z = LpVariable("Z",0)

x0 = LpVariable("x0", 0)
x1 = LpVariable("x1", 0)
x2 = LpVariable("x2", 0)
x3 = LpVariable("x3", 0)
x4 = LpVariable("x4", 0)
x5 = LpVariable("x5", 0)

#the different parts of the equation
lin=0
seas=0
sol=0

#Want to minimize this
prob+=Z

#Want to get the maximum deviation
for i in range(0,n):
	lin = (x0 + x1 * d[i])
	seas = (x2 * math.cos(2*math.pi * d[i]/364.25) + x3 * math.sin(2*math.pi * d[i]/364.25))
	sol = (x4 * math.cos(2*math.pi * d[i]/(364.25*10.7)) + x5 * math.sin(2*math.pi*d[i]/(364.25 * 10.7)))

	prob += Z >= (lin + seas + sol - T[i])
	prob += Z >= -(lin + seas + sol - T[i])


status = prob.solve()
print value(prob.objective)
print "value of x0: " + str(value(x0))
print "value of x1: " + str(value(x1))
print "value of x2: " + str(value(x2))
print "value of x3: " + str(value(x3))
print "value of x4: " + str(value(x4))
print "value of x5: " + str(value(x5))
