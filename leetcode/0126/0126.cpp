#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution
{
public:
    typedef std::unordered_map<std::string, std::unordered_set<std::string>> CacheType;
    typedef std::vector<std::vector<std::string>> PathsType;
    typedef std::unordered_map<std::string, PathsType> PathCacheType;

    template <class SeqType>
    void printSeq(const SeqType& xs, bool newline=true)
    {
        for(auto& x: xs)
        {
            cout << x << ' ';
        }
        if(newline)
        {
            cout << endl;
        }
    }

    bool canTransformCached(const std::string& s1, const std::string& s2,
                            const CacheType& cache)
    {
        const auto& Paths1 = cache.at(s1);
        if(Paths1.find(s2) == std::end(Paths1))
        {
            const auto& Paths2 = cache.at(s2);
            return (Paths2.find(s1) != std::end(Paths2));
        }
        else
        {
            return true;
        }
    }

    bool canTransform(const std::string& s1, const std::string& s2)
    {
        bool Diff = false;

        for(size_t i = 0; i < s1.size(); i++)
        {
            if(s1[i] != s2[i])
            {
                if(Diff == false)
                {
                    Diff = true;
                }
                else
                {
                    return false;
                }
            }
        }
        return Diff;
    }

    PathsType findPathsInner(const std::string& beginWord, const std::string& endWord,
                             const CacheType& cache, size_t& max_length,
                             const std::vector<std::string>& path)
    {
        // cout << "What could go after ";
        // printSeq(path, false);
        // cout << "...?" << endl;

        std::vector<std::string> Path = path;
        PathsType Paths;

        for(const auto& Next: cache.at(beginWord))
        {
            if(std::find(std::begin(path), std::end(path), Next) != std::end(path))
            {
                continue;
            }

            if(Next == endWord)
            {
                Paths.push_back(Path);
                Paths[Paths.size()-1].push_back(endWord);



                if(path.size() < max_length - 1)
                {
                    max_length = path.size() + 1;
                }
            }
            else if(path.size() >= max_length - 1)
            {
                continue;
            }
            else
            {
                auto NewPath = Path;
                NewPath.push_back(Next);
                auto NewPaths = findPathsInner(Next, endWord, cache, max_length, NewPath);
                Paths.insert(std::end(Paths), std::begin(NewPaths), std::end(NewPaths));
            }
        }

        return Paths;
    }

    PathsType findPaths(const std::string& beginWord, const std::string& endWord,
                        const CacheType& cache)
    {
        std::vector<std::vector<std::string>> Paths;
        size_t MinLength = 999999999;

        for(const auto& Word1: cache)
        {
            if(canTransform(beginWord, Word1.first))
            {
                // cout << Word1.first << " is a go!" << endl;
                auto NewPaths = findPathsInner(Word1.first, endWord, cache, MinLength,
                                               {beginWord, Word1.first});
                Paths.insert(std::end(Paths), std::begin(NewPaths), std::end(NewPaths));
            }
        }

        std::vector<std::vector<std::string>> Result;
        for(auto& Path: Paths)
        {
            if(Path.size() <= MinLength)
            {
                Result.push_back(Path);
            }
        }

        return Result;
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
    {
        if(wordList.size() == 1)
        {
            if(wordList[0] == endWord && canTransform(beginWord, endWord))
            {
                return {{beginWord, endWord}};
            }
            else
            {
                return {};
            }
        }

        if(canTransform(beginWord, endWord))
        {
            return {{beginWord, endWord}};
        }

        CacheType Paths;

        for(size_t i = 0; i < wordList.size(); i++)
        {
            Paths[wordList[i]] = {};
        }

        for(size_t i = 0; i < wordList.size() - 1; i++)
        {
            auto& Targets = Paths[wordList[i]];
            for(size_t j = i + 1; j < wordList.size(); j++)
            {
                if(canTransform(wordList[i], wordList[j]))
                {
                    Targets.insert(wordList[j]);
                    Paths[wordList[j]].insert(wordList[i]);
                }
            }
        }
        cout << "Finished caching." << endl;
        return findPaths(beginWord, endWord, Paths);
    }
};

int main()
{
    Solution Sol;
    vector<string> Dict{"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"};

    Sol.findLadders("cet", "ism", Dict);
    return 0;
}


/*
"a"
"c"
["a","b","c"]
*/

/*
"hot"
"dog"
["hot","cog","dog","tot","hog","hop","pot","dot"]
*/

/*
"cet"
"ism"
["kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"]
*/
