#include <list>
#include <string>
#include <utility>

using namespace std;

class Trie
{
public:
    /** Initialize your data structure here. */
    Trie() = default;

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        if(word.size() == 0)
        {
            return;
        }

        Trie* Root = this;
        std::string CurrentKey{};

        for(char c: word)
        {
            CurrentKey.push_back(c);
            Root = &(*(Root -> insertChild(CurrentKey)));
        }
        Root -> Finish = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        if(word.size() == 0)
        {
            return true;
        }

        Trie* Root = this;

        for(char c: word)
        {
            auto Result = Root -> findChild(c);
            if(Result.first)
            {
                Root = &(*(Result.second));
            }
            else
            {
                return false;
            }
        }
        return Root -> isFinish();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        if(prefix.size() == 0)
        {
            return true;
        }

        Trie* Root = this;

        for(char c: prefix)
        {
            auto Result = Root -> findChild(c);
            if(Result.first)
            {
                Root = &(*(Result.second));
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    bool isLeaf() const
    {
        return Children.size() == 0;
    }

    bool isFinish() const
    {
        return Finish;
    }

private:
    std::list<Trie> Children;
    char Edge;
    std::string Key;
    bool Finish = false;

    decltype(Children)::iterator insertChild(const std::string& key)
    {
        auto Result = findChild(key);
        if(!(Result.first))    // Not found
        {
            Trie NewNode{};
            NewNode.Edge = key.back();
            NewNode.Key = key;
            return Children.insert(Result.second, NewNode);
        }
        else
        {
            return Result.second;
        }
    }

    std::pair<bool, decltype(Children)::iterator> findChild(char key)
    {
        for(auto Child = std::begin(Children); Child != std::end(Children); ++Child)
        {
            if(Child -> Edge == key)
            {
                return std::make_pair(true, Child);
            }
            else if(Child -> Edge > key)
            {
                return std::make_pair(false, Child);
            }
        }
        return std::make_pair(false, std::end(Children));
    }

    std::pair<bool, decltype(Children)::iterator> findChild(const std::string& key)
    {
        for(auto Child = std::begin(Children); Child != std::end(Children); ++Child)
        {
            if(Child -> Edge == key.back())
            {
                return std::make_pair(true, Child);
            }
            else if(Child -> Edge > key.back())
            {
                return std::make_pair(false, Child);
            }
        }
        return std::make_pair(false, std::end(Children));
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main()
{
}
