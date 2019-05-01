# https://www.hackerrank.com/challenges/computing-the-correlation

import sys
import math

def correlation(xs, ys, x_sum, y_sum, x2_sum, y2_sum):
    n = len(xs)
    Num = n * sum((p[0] * p[1] for p in zip(xs, ys))) - x_sum * y_sum
    Den = math.sqrt(n * x2_sum - x_sum * x_sum) * \
          math.sqrt(n * y2_sum - y_sum * y_sum)
    return Num / Den

sys.stdin.readline()

ms = []
ps = []
cs = []

for Line in sys.stdin:
    Eles = [int(x) for x in Line.split()]
    ms.append(Eles[0])
    ps.append(Eles[1])
    cs.append(Eles[2])

# Sums
M = sum(ms)
P = sum(ps)
C = sum(cs)

M2 = sum((x*x for x in ms))
P2 = sum((x*x for x in ps))
C2 = sum((x*x for x in cs))

print("{:.2}".format(correlation(ms, ps, M, P, M2, P2)))
print("{:.2}".format(correlation(ps, cs, P, C, P2, C2)))
print("{:.2}".format(correlation(cs, ms, C, M, C2, M2)))
