import itertools

# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

def mergeListOfList(a, b):
    Result = []
    for Pair in itertools.zip_longest(a, b, fillvalue=[]):
        Result.append(Pair[0] + Pair[1])
    return Result

def levelOrderTop(root):
    """
    :type root: TreeNode
    :rtype: List[List[int]]
    """
    # if isinstance(root, int):
    #     return [root,]

    if root is None:
        return []

    Result = [[root.val,]]
    ResultLeft = []
    ResultRight = []
    if root.left is not None:
        ResultLeft = levelOrderTop(root.left)
    if root.right is not None:
        ResultRight = levelOrderTop(root.right)

    if ResultLeft and ResultRight:
        Result += mergeListOfList(ResultLeft, ResultRight)
    else:
        if ResultLeft != []:
            Result += ResultLeft
        if ResultRight != []:
            Result += ResultRight

    return Result

class Solution:

    def levelOrderBottom(self, root):
        return list(reversed(levelOrderTop(root)))
