#!/usr/bin/env python3

import sys, os

def isOfValidLen(num, n):
    return n <= len(num) <= n*3

def restore(num, n):
    if n == 0:
        return [list(),]
    ips = []
    if not isOfValidLen(num, n):
        return ips

    if n == 1:
        if int(num) == 0:
            if len(num) == 1:
                return [[num,],]
            else:
                return ips
        if 0 <= int(num) <= 255:
            return [[num,],]
        else:
            return ips

    # The 1st section can be 1 digits?
    for ip in restore(num[1:], n-1):
        ips.append([num[0],] + ip)

    if num[0] == '0':
        return ips

    # The 1st section can be 2 digits?
    if len(num) >= 2:
        for ip in restore(num[2:], n-1):
            ips.append([num[:2],] + ip)

    # The 1st section can be 3 digits?
    if num[0] in "12" and len(num) >= 3 and 0 <= int(num[:3]) <= 255:
        for ip in restore(num[3:], n-1):
            ips.append([num[:3],] + ip)

    return ips

for ip in restore("25525511135", 4):
    print('.'.join(ip))
