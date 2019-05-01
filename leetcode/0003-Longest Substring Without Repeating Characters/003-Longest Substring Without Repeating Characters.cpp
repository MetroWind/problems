class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int Left = 0;
        int Right = 1;
        int MaxDist = 0;
        set<char> Chars{s[Left]};
        while(Right < s.size())
        {
            // cout << Left << ' ' << Right << endl;
            if(Chars.count(s[Right]) == 1)
            {
                auto RepeatLoc = s.substr(Left, Right-Left).find(s[Right]);
                Left += RepeatLoc + 1;
                Chars.clear();
                for(int i = Left; i < Right; i++)
                    Chars.insert(s[i]);
            }
            Chars.insert(s[Right]);
            Right++;
            if(Right - Left > MaxDist)
            {
                MaxDist = Right - Left;
            }
        }
        return MaxDist;
    }
};
