class Solution
{
public:
    // std::map<std::tuple<unsigned int, unsigned int>, int> Cache;
    std::vector<int> Cache;

    int calcNum(const string& s, const string& t, unsigned int s_begin, unsigned int t_begin)
    {
        // cout << "Trying " << s_begin << ' ' << t_begin << ", "
        //      << s.substr(s_begin) << " vs " << t.substr(t_begin) << endl;
        if(t_begin >= t.size())
        {
            // cout << "t exhausted." << endl;
            return 1;
        }

        if(s_begin >= s.size())
        {
            // cout << "s exhausted." << endl;
            return 0;
        }

        unsigned int Num = 0;
        for(unsigned int is = s_begin; is < s.size(); is++)
        {
            if(s[is] == t[t_begin])
            {
                // cout << "Found "  << s[is] << " at " << is << ' ' << t_begin << endl;
                size_t key = (is+1) * (t.size()+1) + t_begin + 1;
                int CacheHit = Cache[key];
                int BranchNum = 0;
                if(CacheHit == -1)
                {
                    BranchNum = calcNum(s, t, is+1, t_begin+1);
                    Cache[key] = BranchNum;
                }
                else
                {
                    BranchNum = CacheHit;
                }
                // cout << s[is] << " at " << is << ' ' << t_begin << " gives "
                //      << BranchNum << endl;
                Num += BranchNum;
            }
        }
        return Num;
    }

    int numDistinct(string s, string t)
    {
        Cache.resize((s.size()+1) * (t.size()+1), -1);
        return calcNum(s, t, 0, 0);
    }
};
