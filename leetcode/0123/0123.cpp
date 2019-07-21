#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // 普通版 maxSum, O(N).
    int maxSum(const vector<int>& xs, size_t left, size_t right)
    {
        int Max = 0;
        int Sum = 0;
        // vector<int> Sums(xs.size());
        for(size_t i = left; i < right; i++)
        {
            Sum += xs[i];
            if(Sum >= xs[i])
            {
                if(Sum > Max)
                {
                    Max = Sum;
                }
            }
            else
            {
                Sum = xs[i];
                if(xs[i] > Max)
                {
                    Max = xs[i];
                }
            }
        }
        return Max;
    }

    // 逼格版 maxSum, O(NlogN).
    int maxSumZhuangbility(const vector<int>& xs, size_t left, size_t right)
    {
        // printVec(xs);
        // cout << "Looking at " << left << "--" << right << "..." << endl;
        if(right - left == 1)
        {
            return std::max(xs[left], 0);
        }

        if(right - left <= 0)
        {
            return 0;
        }

        size_t Mid = (left + right) / 2;
        // cout << "Mid is " << Mid << endl;

        int SumLeft = maxSum(xs, left, Mid);
        int SumRight = maxSum(xs, Mid, right);

        // cout << "Calculating middle with " << left << ' ' << Mid << ' ' << right << "..." << endl;
        int LeftMax = 0;
        int LeftSum = 0;
        // cout << "Calculating left..." << endl;
        for(size_t i = Mid; i --> left ;)
        {
            // cout << "i = " << i << endl;
            LeftSum += xs[i];
            if(LeftSum > LeftMax)
            {
                LeftMax = LeftSum;
            }
        }

        int RightMax = 0;
        int RightSum = 0;
        // cout << "Calculating right..." << endl;
        for(size_t i = Mid; i < right; i++)
        {
            // cout << "i = " << i << endl;
            RightSum += xs[i];
            if(RightSum > RightMax)
            {
                RightMax = RightSum;
            }
        }

        int SumMid = LeftMax + RightMax;

        return std::max({SumLeft, SumRight, SumMid});
    }

    int maxProfit(vector<int>& prices)
    {
        if(prices.size() <= 1)
        {
            return 0;
        }

        vector<int> Diff(prices.size() - 1);
        for(size_t i = 0; i < Diff.size(); i++)
        {
            Diff[i] = prices[i + 1] - prices[i];
        }

        size_t First = 0;
        size_t Last = Diff.size() - 1;
        for(size_t i = 0; i < Diff.size(); i++)
        {
            if(Diff[i] > 0)
            {
                First = i;
                break;
            }
        }

        for(size_t i = Diff.size(); i --> 0 ;)
        {
            if(Diff[i] > 0)
            {
                Last = i+1;
                break;
            }
        }

        if(Last - First <= 0)
        {
            return 0;
        }

        // Case 1: 1 transaction
        int Sum1 = maxSum(Diff, First, Last);

        // Case 2: 2 transactions
        int Sum2 = 0;
        for(size_t Split = First + 1; Split < Last - 1; Split++)
        {
            // cout << "Split at " << Split << endl;

            int x = maxSum(Diff, First, Split) + maxSum(Diff, Split, Last);
            if(x > Sum2)
            {
                Sum2 = x;
            }
        }
        return std::max(Sum1, Sum2);
    }
};

int main()
{
    vector<int> xs{2,1,2,0,1};

    Solution Sol;
    cout << Sol.maxProfit(xs) << endl;
    return 0;
}
