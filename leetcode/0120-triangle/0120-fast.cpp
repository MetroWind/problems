class Solution
{
public:
    int findMin(vector<vector<int>>& triangle, vector<int>& cache, size_t cache_row,
                size_t start_row, size_t start_col)
    {
        if(start_row >= triangle.size() - 1)
        {
            return triangle[start_row][start_col];
        }

        if(cache_row > 0 && start_row == triangle.size() - cache_row)
        {
            int& Cache = cache[start_col];
            if(Cache != 0)
            {
                return Cache + triangle[start_row][start_col];
            }
        }

        int x = findMin(triangle, cache, cache_row, start_row + 1, start_col);
        int y = findMin(triangle, cache, cache_row, start_row + 1, start_col + 1);
        if(x < y)
        {
            if(cache_row > 0 && start_row == triangle.size() - cache_row)
            {
                cache[start_col] = x;
            }

            return x + triangle[start_row][start_col];
        }
        else
        {
            if(cache_row > 0 && start_row == triangle.size() - cache_row)
            {
                cache[start_col] = y;
            }

            return y + triangle[start_row][start_col];
        }

    }

    int minimumTotal(vector<vector<int>>& triangle)
    {
        if(triangle.size() == 0)
        {
            return 0;
        }

        size_t CacheRow = 2;
        vector<int> Cache;
        if(triangle.size() <= CacheRow && CacheRow > 0)
        {
            CacheRow = 0;
        }
        else
        {
            Cache.resize(triangle.size() - CacheRow + 1, 0);
        }

        return findMin(triangle, Cache, CacheRow, 0, 0);
    }
};
