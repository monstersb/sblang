from Token import Token

class Identifier(Token):
    def __str__(self):
        return '<Identifier, {0}>'.format(self.value)