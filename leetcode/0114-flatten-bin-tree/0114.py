# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def flattenIter(self, root: TreeNode):
        if root is None:
            return None

        Left = root.left
        Right = root.right

        if Left is None and Right is None:
            return root

        if Left is not None:
            End = self.flattenIter(Left)
            root.right = Left
            End.right = Right
            root.left = None

        if Right is None:
            return End
        else:
            End = self.flattenIter(Right)
            return End


    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        self.flattenIter(root)
