#!/usr/bin/env python

def addAccurance(c, d):
    if c in d:
        d[c] += 1
    else:
        d[c] = 1
    return d

def accurance(s, t=None):
    Result = dict()
    for c in s:
        if c in Result:
            Result[c] += 1
        elif t:
            if c in t:
                Result[c] = 1
        else:
            Result[c] = 1

    return Result

def isWindowDict(sd, t):
    for c in t:
        if (not c in sd) or sd[c] < t[c]:
            return False
    return True

def isWindow(s, t):
    """t is a dict."""
    Dict = accurance(s, t)
    return isWindowDict(Dict, t)

def shrinkWindowLeft(s, left, right, t, current_dict):
    Left = left
    Right = right
    while Left < Right:
        Boundary = s[Left]
        if Boundary in t:
            if current_dict[Boundary] - t[Boundary] <= 0:
                return Left
            else:
                current_dict[Boundary] -= 1
        Left += 1
    return Left

def findMinWindow(s, t):
    ss = list(s)
    Chars = accurance(t)
    CurrentChars = dict()
    Windows = []

    Left = 0
    Right = 0
    # Find 1st window
    while Right <= len(ss):
        if Right == len(ss):
            if isWindow(ss, Chars):
                break
            else:
                return None
        if ss[Right] in Chars:
            addAccurance(ss[Right], CurrentChars)
            if isWindowDict(CurrentChars, Chars):
                Right += 1
                break
        Right += 1

    # At this step we have found the 1st window.  Now try to shrink
    # it.  `Right` now is at most len(s).
    Left = shrinkWindowLeft(ss, Left, Right, Chars, CurrentChars)
    Windows.append((Left, Right))

    # At this point ss[Left:Right] is the 1st window.
    while Right < len(ss):
        if ss[Right] in Chars:
            addAccurance(ss[Right], CurrentChars)
        if ss[Left] in Chars:
            if CurrentChars[ss[Left]] == 1:
                del CurrentChars[ss[Left]]
            else:
                CurrentChars[ss[Left]] -= 1
        Right += 1
        Left += 1
        if isWindowDict(CurrentChars, Chars):
            Left = shrinkWindowLeft(ss, Left, Right, Chars, CurrentChars)
            Windows.append((Left, Right))

    return Windows

if __name__ == "__main__":
    import json
    with open("input-076.json", 'r') as File:
        Data = json.load(File)
    # s = "ADOBECODEBANC"
    # t = "ABC"
    s = Data[0]
    t = Data[1]
    Answer = Data[2]
    Window = findMinWindow(s, t)[-1]
    Result = s[Window[0]:Window[1]]
    print len(Result), len(Answer)
    print Result[:10], Answer[:10]
