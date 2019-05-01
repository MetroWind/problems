#!/usr/bin/env pypy

from __future__ import print_function

def grouper(xs, n):
    Size = len(xs)
    Remain = Size % n
    GroupSize = Size // n
    Idx = 0
    for i in xrange(n):
        if Remain > 0:
            yield xs[Idx:GroupSize + 1 + Idx]
            Remain -= 1
            Idx += GroupSize + 1
        else:
            yield xs[Idx:GroupSize + Idx]
            Idx += GroupSize

def prettyLine(words, textwidth):
    Size = len(words)
    if Size == 1:
        return words[0] + ' '*(textwidth - len(words[0]))
    TotalWidth = 0
    for Word in words:
        TotalWidth += len(Word)
    NSpaces = textwidth - TotalWidth
    SpaceGroup = list(grouper(' ' * NSpaces, Size - 1))
    Line = [words[0],]
    for i in xrange(Size - 1):
        Line.append(SpaceGroup[i])
        Line.append(words[i+1])
    return ''.join(Line)

def justify(words, width):
    TotalWidth = 0
    LineWords = []
    Lines = []
    i = 0
    Case = 0
    while i < len(words):
        Word = words[i]
        TotalWidth += len(Word)
        if TotalWidth > width:
            # Finish the currentline and recurse
            TotalWidth -= len(Word)
            Lines.append(prettyLine(LineWords, width))
            TotalWidth = 0
            LineWords = []
            Case = 1
        elif TotalWidth == width:
            LineWords.append(Word)
            Lines.append(' '.join(LineWords))
            TotalWidth = 0
            LineWords = []
            i += 1
            Case = 2
        else:
            LineWords.append(Word)
            TotalWidth += 1
            i += 1
            Case = 3

    # At this point case 1 is impossible.
    if Case == 3:
        Lines.append(' '.join(LineWords))
        if len(Lines[-1]) < width:
            Lines[-1] = Lines[-1] + ' ' * (width - len(Lines[-1]))
    return Lines

if __name__ == "__main__":
    for Line in justify(["Listen","to","many,","speak","to","a","few."], 6):
        print('|', Line, '|')
