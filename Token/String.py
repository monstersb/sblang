from Token import Token

class String(Token):
    def __str__(self):
        return '<String, {0}>'.format(self.value)