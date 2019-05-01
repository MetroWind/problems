# Suppose the numbers are x_N, x_{N-1}, x_{N-2}, ... x_{1}.
#
# 1. First find the smallest i =: k, such that x_k < x_1 (m = 1). If none, jump to step 6.
# 2. Swap x_k and x_1.
# 3. swap x_{k-1} and x_1
# 4. Swap x_{k-2} and x_2
# 5. ...
# 5.5 End
# 6. First find the smallest i =: k, such that x_k < x_2 (m = 2).
# 7. Jump to step 2.
# 8. ...

# NOTE: The above is incomplete.

def swap(xs, i, j):
    # print("Swap", i, j)
    xs[i], xs[j] = xs[j], xs[i]

def findOrderedPair(xs, m, k_max):
    if m >= k_max:
        return None
    for k in range(m+1, k_max + 1):
        # print("Comparing", -m, -k)
        if xs[-m] > xs[-k]:
            Pair = findOrderedPair(xs, m+1, k-1)
            # print(Pair)
            if Pair:
                return Pair
            else:
                return m, k
    return findOrderedPair(xs, m+1, k_max)

class Solution(object):
    def nextPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """

        Size = len(nums)
        m = 1
        Done = False
        Pair = findOrderedPair(nums, m, len(nums))
        if Pair:
            m, k = Pair
            # print(m, k)
            swap(nums, -m, -k)
            for j in range(1, k//2+1):
                swap(nums, j-k, -j)
        else:
            for j in range(1, Size//2+1):
                swap(nums, j-Size-1, -j)
