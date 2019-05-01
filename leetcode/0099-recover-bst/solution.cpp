class Solution
{
public:
    void swap(int* x, int* y)
    {
        const int t = *x;
        *x = *y;
        *y = t;
    }

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

    void validateBSTInner(TreeNode* root, int* lower, int* upper)
    {
        if(root == nullptr)
        {
            return;
        }

        if(lower != nullptr)
        {
            if(root -> val <= *lower)
            {
                swap(&(root -> val), lower);
                return;
            }
        }
        if(upper != nullptr)
        {
            if(root -> val >= *upper)
            {
                swap(&(root -> val), upper);
                return;
            }
        }

        if(root -> left != nullptr)
        {
            if((root -> left -> val) < (root -> val))
            {
                validateBSTInner(root -> left, lower, &(root -> val));
            }
            else
            {
                swap(&(root -> left -> val), &(root -> val));
                return;
            }
        }

        if(root -> right != nullptr)
        {
            if((root -> right -> val) > (root -> val))
            {
                validateBSTInner(root -> right, &(root -> val), upper);
            }
            else
            {
                swap(&(root -> right -> val), &(root -> val));
                return;
            }
        }
        return;
    }

    void recoverTree(TreeNode* root)
    {
        while(!isValidBST(root))
        {
            validateBSTInner(root, nullptr, nullptr);
        }
    }
};
