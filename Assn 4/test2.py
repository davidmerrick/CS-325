from pulp import *

#Function definitions
def find_slope(x1, y1, x2, y2):
                return ((y2-y1)/(x2-x1))

xs = [1, 2, 3, 5, 7, 8, 10]
ys = [3, 5, 7, 11, 14, 15, 19]

#Find max and min slopes to put a bound on a
min_slope = max_slope = find_slope(xs[0], ys[0], xs[1], ys[1])
n = len(xs)
for i in range(1, n):
        for j in range(i+1, n):
                slope = find_slope(xs[i], ys[i], xs[j], ys[j])
                if(slope < min_slope):
                        min_slope = slope
                if(slope > max_slope):
                        max_slope = slope


#Initialize LpProblem
prob = LpProblem("Best Fit Line Problem", LpMinimize)

#Set constraints of decision variables
a = LpVariable("a",min_slope,max_slope)
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
