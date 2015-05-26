class Expression(object):
    def __init__(self, exp, symbol):
        self.exp = exp
        self.symbol = symbol
        self.value = 0

    def calc(self):
        return self.value

    def __str__(self):
        return str(self.value)