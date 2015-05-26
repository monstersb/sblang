#! env python

from Token.Token import Token
from Token.Integer import Integer
from Token.Float import Float
from Token.String import String
from Token.Identifier import Identifier
from Token.Keyword import Keyword
from Token.Operator import Operator
from Token.Type import Type
from Token.Number import Number

class Tokenizer(object):
    def __init__(self, input):
        self.input = input
        self.line = 1
        self.pos = 1
        self.peek = None
        self.read()
        self.eof = False

    def read(self):
        if self.peek == '\n':
            self.line += 1
            self.pos = 1
        else:
            self.pos += 1
        self.peek = self.input.read(1)
        if len(self.peek) == 0:
            self.eof = True
            raise EOFError('EOF')
        return  self.peek

    def match(self, c):
        if self.peek in c:
            self.read()
            return True
        else:
            return False

    def scan(self):
        while self.match('\t\r\n '):
            pass
        if self.match('&'):
            if self.match('&'):
                return Operator('&&')
            else:
                return Operator('&')
        elif self.match('|'):
            if self.match('|'):
                return Operator('||')
            else:
                return Operator('|')
        elif self.match('='):
            if self.match('='):
                return Operator('==')
            else:
                return Operator('=')
        elif self.match('!'):
            if self.match('='):
                return Operator('!=')
            else:
                return Operator('!')
        elif self.match('>'):
            if self.match('='):
                return Operator('>=')
            else:
                return Operator('>')
        elif self.match('<'):
            if self.match('='):
                return Operator('<=')
            else:
                return Operator('<')
        elif self.match('{'):
            return Operator('{')
        elif self.match('}'):
            return Operator('}')
        elif self.match('['):
            return Operator('[')
        elif self.match(']'):
            return Operator(']')
        elif self.match('('):
            return Operator('(')
        elif self.match(')'):
            return Operator(')')
        elif self.match('+'):
            return Operator('+')
        elif self.match('-'):
            return Operator('-')
        elif self.match('*'):
            return Operator('*')
        elif self.match('/'):
            return Operator('/')
        elif self.match(','):
            return Operator(',')
        elif self.match(';'):
            return Operator(';')
        elif self.match('"'):
            v = self.peek
            while True:
                if self.match('"') and v[-1] != '\\':
                    v = v[:-1]
                    break
                else:
                    self.read()
                v += self.peek
            return String(v)
        elif self.match('\''):
            v = self.peek
            while True:
                if self.match('\'') and v[-1] != '\\':
                    v = v
                    break
                else:
                    self.read()
                v += self.peek
            return String(v)
        elif self.peek.isdigit():
            v = self.peek
            self.read()
            while self.peek.isdigit():
                v += self.peek
                self.read()
            if self.match('.'):
                v += '.'
                while self.peek.isdigit():
                    v += self.peek
                    self.read()
                return Float(v)
            else:
                return Integer(v)
        elif self.peek.isalpha() or self.peek == '_':
            v = self.peek
            self.read()
            while self.peek.isalnum() or self.peek == '_':
                v += self.peek
                self.read()
            if Keyword.iskeyword(v):
                if Type.istype(v):
                    return Type(v)
                return Keyword(v)
            return Identifier(v)
        print '\n [#]Error, unrecognized token in [{0}, {1}]\n'.format(self.line, self.pos)
        raise NameError()