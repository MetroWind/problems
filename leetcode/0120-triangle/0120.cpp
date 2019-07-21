class Solution
{
public:
    int findMin(vector<vector<int>>& triangle, vector<vector<int>>& cache,
                size_t start_row, size_t start_col)
    {
        if(start_row >= triangle.size() - 1)
        {
            return triangle[start_row][start_col];
        }

        int& Cache = cache[start_row][start_col];
        if(Cache != 0)
        {
            return Cache + triangle[start_row][start_col];
        }
        else
        {
            int x = findMin(triangle, cache, start_row + 1, start_col);
            int y = findMin(triangle, cache, start_row + 1, start_col + 1);
            if(x < y)
            {
                Cache = x;
                return x + triangle[start_row][start_col];
            }
            else
            {
                Cache = y;
                return y + triangle[start_row][start_col];
            }
        }

    }

    int minimumTotal(vector<vector<int>>& triangle)
    {
        if(triangle.size() == 0)
        {
            return 0;
        }

        vector<vector<int>> Cache(triangle.size() - 1);

        for(size_t i = 0; i < triangle.size() - 1; i++)
        {
            Cache[i].resize(i + 1, 0);
        }

        return findMin(triangle, Cache, 0, 0);
    }
};
