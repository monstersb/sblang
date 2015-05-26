from Token import Token

class Operator(Token):
    def __str__(self):
        return '<Operator, {0}>'.format(self.value)