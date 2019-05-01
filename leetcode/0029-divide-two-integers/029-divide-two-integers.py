def div(Top, Bot):
    if Top < Bot:
        return 0

    x = Bot
    Result = 1
    while True:
        if x+x < Top:
            x += x
            Result += Result
        else:
            break
    Result += div(Top - x, Bot)
    return Result

class Solution(object):
    def divide(self, dividend, divisor):
        """
        :type dividend: int
        :type divisor: int
        :rtype: int
        """
        MAX_INT = 0x7FFFFFFF
        if divisor == 1:
            if dividend > MAX_INT:
                return MAX_INT
            return dividend
        if divisor == -1:
            return -dividend

        Top = dividend
        if dividend < 0:
            Top = -dividend
        Bot = divisor
        if divisor < 0:
            Bot = -divisor

        Result = div(Top, Bot)
        if Result > MAX_INT:
            Result = MAX_INT
        if (dividend > 0 and divisor > 0) or (dividend < 0 and divisor < 0):
            return Result
        else:
            return -Result

