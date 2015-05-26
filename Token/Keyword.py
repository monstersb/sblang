from Token import Token

class Keyword(Token):
    @staticmethod
    def iskeyword(v):
        return v in ['if', 'else', 'for', 'while', 'continue', 'break', 'return', 'true', 'false', 'bool', 'int', 'float', 'string']

    def __str__(self):
        return '<Keyword, {0}>'.format(self.value)