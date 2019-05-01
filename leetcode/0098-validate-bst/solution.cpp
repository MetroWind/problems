class Solution
{
public:
    bool isValidBSTInner(TreeNode* root, const int* lower, const int* upper) const
    {
        if(root == nullptr)
        {
            return true;
        }

        if(lower != nullptr)
        {
            if(root -> val <= *lower)
            {
                return false;
            }
        }
        if(upper != nullptr)
        {
            if(root -> val >= *upper)
            {
                return false;
            }
        }

        if(root -> left != nullptr)
        {
            if(!((root -> left -> val) < (root -> val) &&
                 isValidBSTInner(root -> left, lower, &(root -> val))))
            {
                return false;
            }
        }

        if(root -> right != nullptr)
        {
            if(!((root -> right -> val) > (root -> val) &&
                 isValidBSTInner(root -> right, &(root -> val), upper)))
            {
                return false;
            }
        }
        return true;
    }

    bool isValidBST(TreeNode* root)
    {
        return isValidBSTInner(root, nullptr, nullptr);
    }
};
