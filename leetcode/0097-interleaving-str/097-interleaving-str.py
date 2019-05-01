#!/usr/bin/env python3

def isInter(s1, s2, s3, cache):
    if not s1:
        return s2 == s3
    if not s2:
        return s1 == s3

    if (s1, s2, s3) in cache:
        return cache[s1, s2, s3]

    Prefix12 = False
    Prefix13 = False
    Prefix23 = False
    if s1[0] == s2[0]:
        Prefix12 = True
    if s1[0] == s3[0]:
        Prefix13 = True
    if s2[0] == s3[0]:
        Prefix23 = True

    if Prefix13:
        Result13 = isInter(s1[1:], s2, s3[1:], cache)
        if Result13:
            cache[s1, s2, s3] = True
            return True
    else:
        Result13 = False
    if Prefix23:
        Result23 = isInter(s1, s2[1:], s3[1:], cache)
    else:
        Result23 = False
    cache[s1, s2, s3] = (Result13 or Result23)
    return Result13 or Result23

print(isInter("bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa",
              "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab",
              "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab", dict()))
