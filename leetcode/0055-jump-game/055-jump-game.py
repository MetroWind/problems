class Solution(object):
    def canJump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        Farest = 0
        for i in xrange(len(nums)):
            if i > Farest:
                return False
            Jump = nums[i]
            if i + Jump > Farest:
                Farest = i + Jump
        return True
