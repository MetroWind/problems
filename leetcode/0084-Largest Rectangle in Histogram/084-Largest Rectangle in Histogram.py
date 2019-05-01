#!/usr/bin/env python

def findObviousArea(heights):
    Min = min(heights)
    Idx = heights.index(Min)
    return (Min * len(heights), Idx)

def findMaxArea(heights):
    """Elegent recursive solution, but have stack depth limitation..."""
    Size = len(heights)
    if Size == 1:
        return heights[0]
    elif Size == 0:
        return 0

    Area, idx = findObviousArea(heights)
    AreaLeft = findMaxArea(heights[0:idx])
    AreaRight = findMaxArea(heights[idx + 1 : Size])

    return max(Area, AreaLeft, AreaRight)

# ========== The ugly method ========================================>

def findAreaWithWalls(level, i, walls):
    Idx = findWall(i, walls)
    return level * (walls[Idx] - walls[Idx-1] - 1)

def findWallIter(wall, walls, left, right):
    if right - left == 1:
        if wall > walls[left]:
            return left + 1
        else:
            return left - 1
    elif right == left:
        return left

    Size = right - left
    Mid = (right + left) // 2
    if wall > walls[Mid]:
        return findWallIter(wall, walls, Mid, right)
    else:
        return findWallIter(wall, walls, left, Mid)

def findWall(wall, walls):
    return findWallIter(wall, walls, 0, len(walls))
def insertWall(wall, walls):
    walls.insert(findWallIter(wall, walls, 0, len(walls)), wall)

def findMaxAreaUgly(heights):
    HeightDict = dict()
    for i in xrange(len(heights)):
        h = heights[i]
        if h in HeightDict:
            HeightDict[h].append(i)
        else:
            HeightDict[h] = [i,]

    Heights = sorted(HeightDict)

    Size = len(heights)
    Walls = [-1, Size,]

    MaxArea = 0
    for Height in Heights:
        for i in HeightDict[Height]:
            Area = findAreaWithWalls(Height, i, Walls)
            if Area > MaxArea:
                MaxArea = Area
        for i in HeightDict[Height]:
            insertWall(i, Walls)
    return MaxArea

if __name__ == "__main__":
    import json
    with open("input-084.json", 'r') as File:
        Input = json.load(File)
    print findMaxAreaUgly(Input)
