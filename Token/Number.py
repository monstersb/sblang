from Token import Token

class Number(Token):
    def __str__(self):
        return '<Number, {0}>'.format(self.value)