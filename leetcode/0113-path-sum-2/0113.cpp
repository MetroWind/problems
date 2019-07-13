/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void pathSumIter(TreeNode* root, int sum, vector<int>& path, vector<vector<int>>& result)
    {
        path.push_back(root -> val);

        if(root -> left == nullptr && root -> right == nullptr)
        {
            if(sum == root -> val)
            {
                result.push_back(path);
            }
        }
        else
        {
            if(root -> left != nullptr)
            {
                pathSumIter(root -> left, sum - root -> val, path, result);
            }

            if(root -> right != nullptr)
            {
                pathSumIter(root -> right, sum - root -> val, path, result);
            }
        }

        path.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int sum)
    {
        vector<vector<int>> Result;

        if(root == nullptr)
        {
            return Result;
        }

        vector<int> Path;

        pathSumIter(root, sum, Path, Result);
        return Result;
    }
};
