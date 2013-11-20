from pulp import *

xs = [1, 2, 3, 5, 7, 8, 10]
ys = [3, 5, 7, 11, 14, 15, 19]

#Initialize LpProblem
prob = LpProblem("Best Fit Line Problem", LpMinimize)

#Set constraints of decision variables
a = LpVariable("a",0,0)
b = LpVariable("b",0)
Z = LpVariable("Z",0)

#Want to minimize this
prob+=Z

#Want to get the maximum deviation
for i in range(0,n):
	prob += Z >= -(a * xs[i] + b - ys[i])
	prob += Z >= (a * xs[i] + b - ys[i])

status = prob.solve()
print value(prob.objective)
print "value of a: " + str(value(a))
print "value of b: " + str(value(b))