from Token import Token

class Float(Token):
    def __str__(self):
        return '<Float, {0}>'.format(self.value)