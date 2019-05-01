// https://www.hackerrank.com/challenges/angry-children
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <limits>

int main()
{
    int N, K, Unfair;
    std::cin >> N >> K;

    std::vector<int> Numbers(N, 0);
    for(auto& x: Numbers)
        std::cin >> x;

    std::sort(Numbers.begin(), Numbers.end());
    std::vector<int> Deltas(N-1, 0);
    for(auto i = 0; i < N-1; i++)
    {
        Deltas[i] = Numbers[i+1] - Numbers[i];
    }

    // Find the minimum of Deltas[i, i+K-1]
    int OldSum = std::numeric_limits<int>::max();
    int Index = 0;
    for(auto i = 0; i < N-K+1; i++)
    {
        int Sum = std::accumulate(Deltas.begin() + i, Deltas.begin() + i + K-1, 0);
        if(Sum < OldSum)
        {
            OldSum = Sum;
            Index = i;
        }
    }

    // Print fairness
    std::cout << Numbers[Index + K-1] - Numbers[Index] << std::endl;
    // for(auto i = Index; i < Index + K; i++)
    // {
    //     std::cout << Numbers[i] << ", ";
    // }
    // std::cout << std::endl;

    return 0;
}
