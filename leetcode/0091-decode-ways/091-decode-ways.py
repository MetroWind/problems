#!/usr/bin/env python3

def ways(code):
    if not code:
        return 1
    if code[0] == '0':
        return 0

    Size = len(code)
    Ways = 0

    if code[0] == '1':
        # 1 is independent
        Ways += ways(code[1:])
        if Size > 1:
            # 1 is with the next digit
            Ways += ways(code[2:])
    elif code[0] == '2':
        # 2 is independent
        Ways += ways(code[1:])
        if Size > 1 and int(code[1]) <= 6:
            Ways += ways(code[2:])
    else:
        Ways += ways(code[1:])
    return Ways

print(ways("4757562545844617494555774581341211511296816786586787755257741178599337186486723247528324612117156948"))
