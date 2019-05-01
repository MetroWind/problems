#!/usr/bin/env pypy

def maxSubArray(xs):
    Size = len(xs)
    if Size == 0:
        return xs, 0

    Mid = Size // 2
    Left, LeftSum = maxSubArray(xs[:Mid])
    Right, RightSum = maxSubArray(xs[Mid + 1:])

    RightMax = xs[Mid]
    Sum = xs[Mid]
    RightBound = Mid
    for i in xrange(Mid+1, len(xs)):
        Sum += xs[i]
        if Sum >= RightMax:
            RightBound = i
            RightMax = Sum

    LeftMax = RightMax
    Sum = RightMax
    LeftBound = Mid
    for i in xrange(Mid-1, -1, -1):
        Sum += xs[i]
        if Sum >= LeftMax:
            LeftBound = i
            LeftMax = Sum

    Sum = LeftMax
    if Sum > LeftSum:
        if Sum > RightSum:
            return xs[LeftBound:RightBound+1], Sum
        else:
            return Right, RightSum
    elif LeftSum > RightSum:
        return Left, LeftSum
    else:
        return Right, RightSum

if __name__ == "__main__":
    print maxSubArray([-2,1,-3,4,-1,2,1,-5,4])
