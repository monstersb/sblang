from Token import Token

class Type(Token):
    @staticmethod
    def istype(v):
        return v in ['bool', 'int', 'float', 'string']

    def __str__(self):
        return '<Type, {0}>'.format(self.value)