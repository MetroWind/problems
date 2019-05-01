class Solution(object):
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 1

        # This function tries to put number x to the (x-1)th place in
        # `num`, by swapping.

        # Scan all numbers
        for i in range(len(nums)):
            # Skip numbers that are too large.
            if nums[i] > len(nums):
                continue
            x = nums[i]

            # If the ith number, x, is not i+1, swap it to it's
            # correct place (which is (x-1)th slot in the list).
            # Repeatedly doing so until the ith number is i+1, or is
            # invalid (too big or non-positive).
            while x > 0 and x != i+1 and x <= len(nums) and x != nums[x-1]:
                nums[i], nums[x-1] = nums[x-1], x
                x = nums[i]

        for i, x in zip(range(len(nums)), nums):
            if i != x-1:
                return i+1
        return nums[-1]+1
