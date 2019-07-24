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
        int Path = 0;
        std::list<int> Group;

        if(root -> left != nullptr)
        {
            // Case 1: Max path starts at root, and goes to the left.
            Left = maxMonoPathSum(root -> left);
            // cout << "Left is " << Left << ", pushing " << Left + root -> val << "..." << endl;
            Group.push_back(Left + root -> val);
            // Case 2: Max path involves left, but not root.
            Group.push_back(maxPathSumOf(root -> left));
        }

        if(root -> right != nullptr)
        {
            // Case 3: Max path starts at root, and goes to the right.
            Right = maxMonoPathSum(root -> right);
            // cout << "Right is " << Right << endl;
            Group.push_back(Right + root -> val);
            // Case 4: Max path involves right, but not root.
            Group.push_back(maxPathSumOf(root -> right));
        }

        // Case 5: Max path goes thought left, root, and right.
        Group.push_back(Left + Right + root -> val);
        Group.push_back(root -> val);

        // printSeq(Group);
        int Max = *(std::max_element(std::begin(Group), std::end(Group)));
        // cout << root -> val << " --> " << Max << endl;
        return Max;
    }

    // The max sum for any path starting at root.
    int maxMonoPathSum(TreeNode* root)
    {
        int Left = 0;
        int Right = 0;
        std::list<int> Group;
        if(root -> left != nullptr)
        {
            Left = maxMonoPathSum(root -> left) + root -> val;
            Group.push_back(Left);
        }

        if(root -> right != nullptr)
        {
            Right = maxMonoPathSum(root -> right) + root -> val;
            Group.push_back(Right);
        }

        Group.push_back(root -> val);
        return *(std::max_element(std::begin(Group), std::end(Group)));
    }

    int maxPathSum(TreeNode* root)
    {
        return maxPathSumOf(root);
    }
};

// [1,-2,3]
// [2,-1]
// [5,4,8,11,null,13,4,7,2,null,null,null,1]
