#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int find(int x, const vector<int>& xs, int begin, int end)
{
    if(begin - end == -1 || begin == end)
    {
        if(xs[begin] == x)
        {
            return begin;
        }
        else
        {
            return -1;
        }
    }

    int start = (begin + end) / 2;

    if(xs[start] == x)
    {
        return start;
    }

    if(xs[start] > x)
    {
        return find(x, xs, begin, start);
    }
    else
    {
        return find(x, xs, start, end);
    }
}

int findDumb(int x, const vector<int>& xs, int except)
{
    for(int i = 0; i < xs.size(); i++)
    {
        if(x == xs[i])
            if(i != except)
                return i;
    }
    return -1;
}

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        int Size = nums.size();
        vector<int> Result(2, 0);
        vector<int> sorted = nums;
        std::sort(std::begin(sorted), std::end(sorted));
        for(int i  = 0; i < Size; i++)
        {
            int Loc = find(target - nums[i], sorted, 0, Size);
            if(Loc != -1)
            {
                Result[0] = i+1;
                Result[1] = findDumb(sorted[Loc], nums, i)+1;
                if(Result[1] == 0)
                    continue;
                return Result;
            }
        }
        return Result;
    }
};

int main()
{
    Solution Sol;
    vector<int> xs {3,2,4};
    // for(int i = 0; i<10; i++)
    // {
    //     xs.push_back(i);
    // }

    vector<int> Result = Sol.twoSum(xs, 6);

    cout << Result[0] << ' ' << Result[1] << endl;
    return 0;
}
