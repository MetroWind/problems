#!/usr/bin/env pypy

class JumpNode(object):
    def __init__(self, loc=0):
        self.Loc = loc
        self.Dest = set()
        self.MinDepth = 0

    def addDest(self, dest):
        if dest.MinDepth > 0:
            if dest.MinDepth > self.MinDepth + 1:
                dest.MinDepth = self.MinDepth + 1
        else:
            dest.MinDepth = self.MinDepth + 1
        self.Dest.add(dest)
        return self

    def __hash__(self):
        return self.Loc

AllDests = dict()

def hopper(jumps, start_node):
    StartNode = start_node
    Loc = StartNode.Loc
    Path = [[Loc, 0],]
    while True:
        # print Path
        Jump = jumps[Loc] - Path[-1][-1]
        if Loc == len(jumps)-1:
            # print "aaa"
            return StartNode.MinDepth
        if Jump == 0:
            del Path[-1]
            Path[-1][-1] += 1
            Loc = Path[-1][0]
            StartNode = AllDests[Loc]
            continue

        DestLoc = Loc + Jump
        if DestLoc in AllDests:
            Dest = AllDests[DestLoc]
        else:
            Dest = JumpNode(DestLoc)
            AllDests[DestLoc] = Dest

        AllDests[Loc].addDest(Dest)
        if Loc + Jump >= len(jumps) - 1:
            # print "bbb"
            # print Loc, Jump, StartNode.MinDepth + 1
            return StartNode.MinDepth + 1

        Loc = DestLoc
        StartNode = Dest
        Path.append([Loc, 0])

def calcJump(jumps):
    if len(jumps) <= 1:
        return 0

    JumpTable = JumpNode()
    MinDepth = len(jumps)

    ThisNode = JumpNode(0)
    AllDests[0] = ThisNode
    Hops = hopper(jumps, ThisNode)
    return Hops
    for i in xrange(len(jumps)):
        CurrentLoc = i
        Jump = jumps[i]
        if i in AllDests:
            continue
        ThisNode = JumpNode(i)
        AllDests[i] = ThisNode
        Hops = hopper(jumps, ThisNode)
        if Hops <= 0:
            continue
        if Hops < MinDepth:
            MinDepth = Hops
    return MinDepth

if __name__ == "__main__":
    import json
    with open("input-045.txt", 'r') as File:
        Data = json.load(File)
    Data = [1,1,1,1]
    print "Length:", len(Data)
    print calcJump(Data)
