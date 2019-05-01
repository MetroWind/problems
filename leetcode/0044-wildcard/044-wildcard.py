#!/usr/bin/env python

def searchSimplePattern(s, ptn, start):
    """Search for a "simple pattern" in `s`, starting from `i`th char.  A
    simple pattern is a pattern that only contains alphabets and `?`
    """
    # print ' ', s, ptn, start
    if ptn == '':
        # print ' ', "Found due to empty pattern"
        return start

    if len(s) - start < len(ptn) or start < 0:
        # print ' ', "Fail due to large start or negative start"
        return -1

    # Deal with leading '?'
    Prefix = -1
    for i in range(0, len(ptn)):
        if ptn[i] != '?':
            Prefix = i
            break
    if Prefix == -1:
        # print ' ', "Found due to all ? pattern"
        return start

    if Prefix > 0:
        Match = searchSimplePattern(s, ptn[Prefix:], start + Prefix)
        if Match == -1:
            return -1
        else:
            return Match - Prefix

    PartsRaw = ptn.split('?')
    Parts = iter(PartsRaw)
    SubStr = next(Parts)
    Loc = s.find(SubStr, start)
    if Loc == -1:
        # print ' ', "Fail due to substring searching"
        return -1
    i = Loc + len(SubStr)

    while True:
        try:
            SubStr = next(Parts)
        except StopIteration:
            break
        i += 1
        if len(s) - i < len(SubStr):
            # print ' ', "Failed due to exhauted string"
            return -1
        if s[i:].startswith(SubStr):
            i += len(SubStr)
        else:
            # print ' ', "Failed due to nonmatching substring"
            return -1
    # print ' ', "Canonical return"
    return Loc

def matchPatternKernel(s, ptn, start=0, strict=False):
    # print s, ptn, start
    i = start
    Parts = ptn.split('*')
    iPart = 0
    while not Parts[iPart]:
        iPart += 1
        strict=False
        if iPart >= len(Parts):
            # print "True due to all *"
            return True

    # If this is the last parts, we require the tail of s matches it.
    if len(Parts) -1 == iPart:
        if len(s) - start < len(Parts[iPart]):
            # print "False due to tail non-match"
            return False
        Match = searchSimplePattern(s, Parts[iPart], len(s) - len(Parts[iPart]))
        # print "Result due to tail matching ({})".format(Match)
        return Match != -1

    Match = searchSimplePattern(s, Parts[iPart], i)
    if Match == -1 or (strict and Match != start):
        # print "False due to sub pattern non-matching ({})".format(Match)
        return False
    else:
        RemainPtn = '*'.join(Parts[iPart+1:])
        return matchPatternKernel(s, RemainPtn, Match + len(Parts[iPart]))

def matchPattern(s, ptn):
    if ptn == '*':
        return True
    if ptn.find('*') == -1:
        return len(s) == len(ptn) and searchSimplePattern(s, ptn, 0) != -1
    else:
        return matchPatternKernel(s, ptn, 0, True)

if __name__ == "__main__":
    # print(searchSimplePattern("ab", 'a', 1))
    Match = matchPattern("baabba", "?*?a??")
    print(Match)
