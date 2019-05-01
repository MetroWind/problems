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
        Combs = [[candidates[0],] + comb for comb in combSum(candidates, target - candidates[0])]
    # Second kind
    Combs += combSum(candidates[1:], target)
    return Combs

class Solution(object):
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        return combSum(sorted(candidates), target)
