from pulp import *

#Function definitions
def find_slope(x1, y1, x2, y2):
                return ((y2-y1)/(x2-x1))

xs = [1, 2, 3, 5, 7, 8, 10]
ys = [3, 5, 7, 11, 14, 15, 19]

#Initialize LpProblem stuff
prob = LpProblem("Best Fit Line Problem", LpMaximize)
a = LpVariable("a",0)
#b = LpVariable("b",0)
b = 1;
Z = LpVariable("Z",0)
c = LpVariable("c",0)

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
x = 0
y = 0

for i in range (1, n):
	x += xs[i]
	y += ys[i]

prob += (a * x + b - y) 

for i in range (1, n):
	#prob += (a * xs[i] + b - ys[i]) 

	prob += a*xs[i]+b*ys[i]-c <= Z
	prob += a*xs[i]+b*ys[i]-c >= -Z

prob += a <= max_slope
prob += a >= min_slope



status = prob.solve()


print "Min possible slope: " + str(min_slope)
print "Max possible slope: " + str(max_slope)
print "value of a: " + str(value(a))
print "value of b: " + str(value(b))
print "value of c: " + str(value(c))


