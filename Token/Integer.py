from Token import Token

class Integer(Token):
    def __str__(self):
        return '<Integer, {0}>'.format(self.value)