#!/usr/bin/env python

class Range(object):
    def __init__(self, left=0, right=0):
        self.Left = left
        self.Right = right

    def contains(self, x):
        return x >= self.Left and x <= self.Right

    def __str__(self):
        return "[{}, {}]".format(self.Left, self.Right)

    def __repr__(self):
        return "Range({}, {})".format(self.Left, self.Right)

def addToKey(x, dic, key):
    if key in dic:
        dic[key].append(x)
    else:
        dic[key] = [x,]

def calcWaterStupid(levels):
    Levels = dict()
    for l, i in zip(levels, range(len(levels))):
        if l == 0:
            continue
        addToKey(i, Levels, l)

    Heights = sorted(Levels.keys(), reverse=True)
    Volumn = 0
    UpperPools = [Range(-1, len(levels)),]
    Pools = []
    UpperPoolsIter = iter(UpperPools)

    for Level, ilvl in zip(Heights, range(len(Heights))):
        # print "Level", Level, "============================================================>"
        UpperPool = next(UpperPoolsIter)
        Left = UpperPool.Left
        if ilvl < len(Heights) - 1:
            NextLevel = Heights[ilvl+1]
        else:
            NextLevel = 0
        # print "Next level:", NextLevel
        # print "Upper pools:", UpperPools

        for i in range(len(Levels[Level])):
            x = Levels[Level][i]
            # print "Analysing", x, "..."
            while not UpperPool.contains(x):
                # print "Went out of pool.  Left is", Left
                if UpperPool.Right - Left > 1:
                    # print "Need to finish previous pool, adding Range(Left, UpperPool.Right)."
                    Pools.append(Range(Left, UpperPool.Right))
                    if UpperPool.Right < len(levels) and Left > -1:
                        Volumn += (UpperPool.Right - Left - 1) * (Level - NextLevel)
                    try:
                        UpperPool = next(UpperPoolsIter)
                    except StopIteration:
                        break
                    # print "Looking into next pool:", UpperPool
                    Left = UpperPool.Left
                else:
                    try:
                        UpperPool = next(UpperPoolsIter)
                    except StopIteration:
                        break
                    # print "Looking into next pool:", UpperPool
                    Left = UpperPool.Left


            Started = True
            if x > Left+1:
                Pools.append(Range(Left, x))
                if Left > -1:
                    Volumn += (x - Left - 1) * (Level - NextLevel)
            Left = x

        if UpperPool.Right > x +1:
            Pools.append(Range(x, UpperPool.Right))
            if UpperPool.Right < len(levels):
                Volumn += (UpperPool.Right - x -1) * (Level - NextLevel)

        # Add all remaining upper pools
        while True:
            try:
                UpperPool = next(UpperPoolsIter)
            except StopIteration:
                break
            if UpperPool.Right  < len(levels):
                Volumn += (UpperPool.Right - UpperPool.Left - 1) * (Level - NextLevel)
            # print "Add a remaining pool"
            Pools.append(UpperPool)

        # print "Pools:", Pools
        UpperPools = Pools
        Pools = []
        UpperPoolsIter = iter(UpperPools)

    return Volumn

def calcWater(levels, left, right):
    if right - left <= 1:
        return 0
    # If the region is open
    if left == -1 or right == len(levels):
        # Find the highest point in the region
        PoleX = (right + left) // 2
        for x in range(left+1, right):
            if levels[x] > levels[PoleX]:
                PoleX = x
        # Split the region by the highest point
        Area = 0
        Area += calcWater(levels, left, PoleX)
        Area += calcWater(levels, PoleX, right)
        return Area
    else:
        # This region should form a pool.
        PoolHeight = levels[left if levels[left] < levels[right] else right]
        Area = 0
        for i in range(left+1, right):
            Area += PoolHeight - levels[i]
        return Area

def plotLevels(levels, f):
    for x, y in zip(range(len(levels)), levels):
        f.write("{} {}\n".format(x, y))

if __name__ == "__main__":
    import sys
    import json
    TestLevel = json.load(sys.stdin)
    with open("/tmp/test.txt", 'w') as File:
        plotLevels(TestLevel, File)
    print "Level file: /tmp/test.txt"
    print(calcWater(TestLevel, -1, len(TestLevel)))
