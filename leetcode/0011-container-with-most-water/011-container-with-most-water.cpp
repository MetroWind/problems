class Solution {
public:
    int area(int a1, int a2, int i1, int i2)
    {
        if(a1 >= a2)
            return a2 * (i2-i1);
        else
            return a1 * (i2-i1);
    }

    int maxArea(const vector<int>& height, int Min, int Max)
    {
        // cout << Min <<  ' ' << Max << endl;
        if(Max - Min == 1)
            return area(height[Min], height[Max], Min, Max);

        int Middle = Min + (Max - Min) / 2;
        int MaxArea = 0;

        int Left = Middle - 1;
        int Right = Middle + 1;

        // MaxArea = area(height[Left], height[Right], Left, Right);
        // int GoodLeft = Left, GoodRight = Right;

        // // Move left bound, and choose the one that provides the
        // // biggest area.
        // for(int Left = Middle - 1; Left >= Min; Left--)
        // {
        //     int Area = area(height[Left], height[Right], Left, Right);
        //     if(Area > MaxArea)
        //     {
        //         MaxArea = Area;
        //         GoodLeft = Left;
        //     }
        // }

        // Left = GoodLeft;
        // // Now move right bound.
        // for(int Right = Middle + 1; Right <= Max; Right++)
        // {
        //     int Area = area(height[Left], height[Right], Left, Right);
        //     if(Area > MaxArea)
        //     {
        //         MaxArea = Area;
        //         GoodRight = Right;
        //     }
        // }

        for(int Left = Middle - 1; Left >= Min; Left--)
        {
            if(Left > Min && height[Left-1] >= height[Left]-1)
                continue;
            // Right bound
            for(int Right = Middle + 1; Right <= Max; Right++)
            {
                if(Right < Max && height[Right+1] >= height[Right]-1)
                    continue;
                int Area = area(height[Left], height[Right], Left, Right);
                if(Area > MaxArea)
                    MaxArea = Area;
            }
        }

        int LeftMax = maxArea(height, Min, Middle);
        int RightMax = maxArea(height, Middle, Max);
        if(LeftMax > RightMax)
        {
            if(LeftMax > MaxArea)
                return LeftMax;
            else
                return MaxArea;
        }
        else
        {
            if(RightMax > MaxArea)
                return RightMax;
            else
                return MaxArea;
        }
    }

    int maxArea(vector<int>& height)
    {
        if(height.size() < 2)
        {
            return 0;
        }
        return maxArea(height, 0, height.size()-1);
    }
};
