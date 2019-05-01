#!/usr/bin/env python

def removeLeadingZero(s):
    for i, c in zip(range(len(s)), s):
        if c != '0':
            return s[i:]
    return '0'

def add(x, y):
    IterX = iter(reversed(x))
    IterY = iter(reversed(y))

    StepUp = 0
    Result = []
    End = ''
    StopX = False
    StopY = False
    while True:
        try:
            X = int(next(IterX))
        except StopIteration:
            X = 0
            StopX = True
        try:
            Y = int(next(IterY))
        except StopIteration:
            Y = 0
            StopY = True

        if StopX and StopY:
            break

        Digit = X+Y + StepUp
        if Digit >= 10:
            StepUp = 1
        else:
            StepUp = 0
        Result.append(str(Digit % 10))

    if StepUp > 0:
        Result.append(str(StepUp))
    return ''.join(reversed(Result))

def multiplyDigit(x, y):
    """x has 1 digit."""
    X = int(x)
    Factor = 0
    Results = []
    for n in reversed(y):
        Digit = X * int(n) + Factor
        Factor = Digit // 10
        Results.append(str(Digit % 10))
    if Factor > 0:
        Results.append(str(Factor))

    return removeLeadingZero(''.join(reversed(Results)))

def multiply(x, y):
    if len(x) < len(y):
        Lower = x
        Upper = y
    else:
        Upper = x
        Lower = y

    Cache = dict()
    Sum = '0'
    for i, digit in zip(range(len(Lower)), reversed(Lower)):
        if digit in Cache:
            Result = Cache[digit]
        else:
            Result = multiplyDigit(digit, Upper)
            Cache[digit] = Result
        Result += '0' * i
        Sum = add(Sum, Result)
    return Sum

if __name__ == "__main__":
    print(multiplyDigit("0", "12344"))
