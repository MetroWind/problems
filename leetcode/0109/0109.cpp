/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    TreeNode* buildLevel(unsigned int level, std::list<TreeNode*>& nodes)
    {
        if(level == 0)
        {
            return nullptr;
        }

        if(level == 1)
        {
            auto* node = *(std::begin(nodes));
            nodes.pop_front();
            return node;
        }

        auto* left = buildLevel(level - 1, nodes);
        auto* root = *(std::begin(nodes));
        nodes.pop_front();
        auto* right = buildLevel(level - 1, nodes);
        root -> left = left;
        root -> right = right;

        return root;
    }

    TreeNode* sortedListToBST(ListNode* head)
    {
        unsigned int Size = 0;
        ListNode* Cursor = head;
        while(Cursor != nullptr)
        {
            Size++;
            Cursor = head -> next;
        }

        unsigned int i = 0;
        unsigned int Exp = 0;

    }
};
