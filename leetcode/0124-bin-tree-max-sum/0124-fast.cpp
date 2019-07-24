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
    template <class SeqType>
    void printSeq(const SeqType& xs)
    {
        for(auto& x: xs)
        {
            cout << x << ' ';
        }
        cout << endl;
    }

    int maxPathSumOf(TreeNode* root)
    {
        // cout << "Looking at " << root -> val << "..." << endl;
        int Left = 0;
        int Right = 0;
        int LeftBranch = 0;
        int RightBranch = 0;
        int Path = 0;
        int Max = root -> val;

        if(root -> left != nullptr)
        {
            // Case 2: Max path involves left, but not root.
            LeftBranch = maxPathSumOf(root -> left);
            if(LeftBranch > Max)
            {
                Max = LeftBranch;
            }

            // Case 1: Max path starts at root, and goes to the left.
            Left = root -> left -> val;
            if(Left + root -> val > Max)
            {
                Max = Left + root -> val;
            }
        }

        if(root -> right != nullptr)
        {
            // Case 4: Max path involves right, but not root.
            RightBranch = maxPathSumOf(root -> right);
            if(RightBranch > Max)
            {
                Max = RightBranch;
            }

            // Case 3: Max path starts at root, and goes to the left.
            Right = root -> right -> val;
            if(Right + root -> val > Max)
            {
                Max = Right + root -> val;
            }
        }

        // Case 5: Max path goes thought left, root, and right.
        Path = Left + Right + root -> val;
        if(Path > Max)
        {
            Max = Path;
        }

        if(Left > 0)
        {
            if(Left > Right)
            {
                root -> val += Left;
            }
            else
            {
                root -> val += Right;
            }
        }
        else
        {
            if(Right > 0)
            {
                root -> val += Right;
            }
        }

        // cout << root -> val << " --> " << Max << endl;
        return Max;
    }

    int maxPathSum(TreeNode* root)
    {
        return maxPathSumOf(root);
    }
};

// [1,-2,3]
// [2,-1]
// [5,4,8,11,null,13,4,7,2,null,null,null,1]
// [9,6,-3,null,null,-6,2,null,null,2,null,-6,-6,-6]
