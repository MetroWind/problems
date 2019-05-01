import copy

class Solution(object):
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        if not nums:
            return []
        if len(nums) == 1:
            return [nums,]

        AllPerms = []
        Perms = self.permute(nums[1:])
        for i in xrange(len(nums)):
            for p in Perms:
                Perm = copy.copy(p)
                Perm.insert(i, nums[0])
                AllPerms.append(Perm)
        return AllPerms
