from matplotlib import pyplot as plt
import math
# a = [10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000]

a = [100, 1000, 10000, 100000, 1000000]
b = [256, 2418, 19992, 246301, 55183862]
c = [6, 70, 754, 48218, 4978520]
x = list(range(len(a)))
y = []
for i, j in zip(a, b):
    y.append( j / (i * math.log(i)))
    
plt.plot(x, y)
plt.show()