#!/usr/bin/env python3

def findSubsets(nums):
    Subs = set()
    if not nums:
        return Subs
    Subs.add((nums[0],))
    SubSubs = findSubsets(nums[1:])
    Subs |= SubSubs
    for SubSub in SubSubs:
        Subs.add(tuple([nums[0],] + list(SubSub)))
    return Subs

print(findSubsets([1,2,2]))
