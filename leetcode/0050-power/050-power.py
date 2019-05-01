def pow(x, n):
    if n == 1:
        return x
    if n == 0:
        return 1

    y = pow(x, n//2)
    if n % 2 == 1:
        return y * y * x
    else:
        return y * y

class Solution(object):
    def myPow(self, x, n):
        """
        :type x: float
        :type n: int
        :rtype: float
        """

        if n >= 0:
            return pow(x, n)
        else:
            return 1.0 / pow(x, -n)
