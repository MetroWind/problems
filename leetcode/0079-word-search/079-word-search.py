#!/usr/bin/env python

def findNeibors(grid, start):
    if start[1] > 0:
        yield (start[0], start[1]-1)
    if start[0] > 0:
        yield (start[0]-1, start[1])
    if start[1] < len(grid[0]) - 1:
        yield (start[0], start[1] + 1)
    if start[0] < len(grid) - 1:
        yield (start[0]+1, start[1])

def findWord(grid, word, path=[], start=None):
    if not word:
        return True
    if not start:
        for Row in xrange(len(grid)):
            for Col in xrange(len(grid[0])):
                if grid[Row][Col] == word[0]:
                    Result = findWord(grid, word[1:], path + [(Row, Col),], (Row, Col))
                    if Result:
                        return True

    else:
        for Neighbor in findNeibors(grid, start):
            if grid[Neighbor[0]][Neighbor[1]] == word[0] and (not Neighbor in path):
                Result = findWord(grid, word[1:], path + [Neighbor,], Neighbor)
                if Result:
                    return True
    return False

if __name__ == "__main__":
    print findWord([
        ['A','B','C','E'],
        ['S','F','C','S'],
        ['A','D','E','E']
    ], list("SEE"))
