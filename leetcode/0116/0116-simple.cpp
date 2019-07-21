// This uses more than constant extra space though.

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
    void penetrate(Node* tree, std::vector<Node*>& prev_path, std::vector<Node*>& path)
    {
        if(tree == nullptr)
        {
            if(prev_path.size() != 0)
            {
                for(size_t i = 0; i < path.size(); i++)
                {
                    if(prev_path[i] != path[i])
                    {
                        prev_path[i] -> next = path[i];
                    }
                }
            }

            prev_path = path;
            return;
        }

        path.push_back(tree);

        penetrate(tree -> left, prev_path, path);
        penetrate(tree -> right, prev_path, path);
    }

    Node* connect(Node* root)
    {
        std::vector<Node*> PrevPath;
        std::vector<Node*> Path;
        penetrate(root, PrevPath, Path);

        for(auto* Node: Path)
        {
            Node -> next = nullptr;
        }
        return root;
    }
};
