import copy

def sgrouper(xs, n):
    Group = []
    i = 0
    while True:
        i += 1
        try:
            Group.append(next(xs))
        except StopIteration:
            break
        if i == n:
            yield ''.join(Group)
            Group = []
            i = 0
    yield ''.join(Group)

def ispermutation(s, words, n):
    if set(words) == set(grouper(iter(s), n)):
        return True

class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        # Build dict
        Words = set(words)
        AllWords = sorted(words)
        Size = len(s)
        WordSize = len(words[0])
        AllWordSize = WordSize * len(Words)
        Results = []

        ss = []
        for i in range(WordSize):
            Str = s[i:]
            Secs = list(sgrouper(iter(Str), WordSize))
            for j in range(len(Secs) - len(words)):
                LocalSecs = Secs[j:j+len(words)]
                if sorted(list(LocalSecs)) == AllWords:
                    Results.append(j*WordSize + i)

        return Results
