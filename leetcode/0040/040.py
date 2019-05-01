def find1stDiff(xs):
    """Find 1st element in xs that is not equal to xs[0]."""
    for i in range(1, len(xs)):
        if xs[i] != xs[0]:
            return i
    return 0

def combSum(candidates, target):
    # There are 2 kinds of combinations: those contains candidates[0], and those do not.
    if (not candidates) or candidates[0] > target:
        return []

    if candidates[0] == target:
        return [[candidates[0],]]

    Combs = []
    # First kind
    First = combSum(candidates, target - candidates[0])
    if First:
        Combs = [[candidates[0],] + comb for comb in combSum(candidates[1:], target - candidates[0])]
    # Second kind
    # Skip all elements that are equal to candidates[0].
    i = find1stDiff(candidates)
    if i == 0:
        return Combs
    else:
        Combs += combSum(candidates[i:], target)
    return Combs

class Solution(object):
    def combinationSum2(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        return combSum(sorted(candidates), target)
