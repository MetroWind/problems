/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/

class Solution
{
public:
    Node* penetrate(Node* root, Node* prev_node, unsigned int level, unsigned int max_level)
    {
        if(level == max_level - 1)
        {
            if(prev_node != nullptr)
            {
                prev_node -> next = root;
            }

            return root;
        }

        if(root -> left != nullptr)
        {
            prev_node = penetrate(root -> left, prev_node, level + 1, max_level);
        }

        if(root -> right != nullptr)
        {
            prev_node = penetrate(root -> right, prev_node, level + 1, max_level);
        }

        return prev_node;
    }

    Node* connect(Node* root)
    {
        if(root == nullptr)
        {
            return nullptr;
        }

        unsigned int Level = 1;
        Node* Last = nullptr;
        do
        {
            Last = penetrate(root, nullptr, 0, Level++);
        }
        while(Last != nullptr);
        return root;
    }
};
