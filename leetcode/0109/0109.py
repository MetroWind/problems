#!/usr/bin/env python

import typing

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def buildLevel(self, size: int, nodes: typing.Iterator[TreeNode]) -> TreeNode:
        if size == 0:
            return None
        if size == 1:
            return next(nodes)

        HalfSize = size // 2
        Left = self.buildLevel(HalfSize, nodes)

        Root = next(nodes)

        Right = self.buildLevel(size - HalfSize - 1, nodes)

        Root.left = Left
        Root.right = Right
        return Root

    def sortedListToBST(self, head: ListNode) -> TreeNode:
        Size = 0
        Cursor = head

        while Cursor is not None:
            Size += 1
            Cursor = Cursor.next

        if Size == 0:
            return None

        Nodes = tuple(TreeNode(0) for i in range(Size))
        Cursor = head

        for Node in Nodes:
            Node.val = Cursor.val
            Cursor = Cursor.next

        Root = self.buildLevel(Size, iter(Nodes))
        return Root
