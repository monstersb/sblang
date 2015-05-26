from Tokenizer import Tokenizer
from collections import deque
from Token.Type import Type
from Token.Identifier import Identifier
from Token.Operator import Operator
from Token.Integer import Integer
from Token.Float import Float
from Token.String import String
from Symbol import *

class Parser(object):
    def __init__(self, input):
        self.tokenizer = Tokenizer(input)
        self.tkbuf = deque()
        self.tk = None
        self.next()
        self.eof = False
        self.symbol = SymbolTable()

    def next(self):
        if len(self.tkbuf) == 0:
            self.read()
        if len(self.tkbuf) > 0:
            self.tk = self.tkbuf.pop()
            return self.tk

    def push(self, t):
        if isinstance(t, list):
            map(self.push, t)
        else:
            self.tkbuf.append(self.tk)
            self.tk = t

    def read(self):
        try:
            self.tkbuf.appendleft(self.tokenizer.scan())
        except EOFError:
            self.eof = True

    def match(self, tp, v=None):
        if isinstance(self.tk, tp):
            if v is not None:
                if self.tk.value == v:
                    self.next()
                    return True
                else:
                    return False
            else:
                self.next()
                return True
        else:
            return False

    def parse(self):
        sb = self.stmt()
        self.printSyntaxTree(sb)

    def expr1(self):
        buf = []
        t = self.expr3()
        if t is not None:
            buf.append(t)
            t = self.expr2()
            if t is not None:
                if t != "null":
                    buf.append(t)
                return buf
            else:
                map(self.push, buf)

    def expr2(self):
        buf = []
        if isinstance(self.tk, Operator) and (self.tk.value == '+' or self.tk.value == '-'):
            buf.append(self.tk)
            self.next()
            t = self.expr3()
            if t is not None:
                buf.append(t)
                t = self.expr2()
                if t is not None:
                    if t != "null":
                        buf.append(t)
                    return buf
                else:
                    map(self.push, buf)
            else:
                map(self.push, buf)
        else:
            return 'null'

    def expr3(self):
        buf = []
        t = self.expr5()
        if t is not None:
            buf.append(t)
            t = self.expr4()
            if t is not None:
                if t != "null":
                    buf.append(t)
                return buf
            else:
                map(self.push, buf)

    def expr4(self):
        buf = []
        if isinstance(self.tk, Operator) and (self.tk.value == '*' or self.tk.value == '/'):
            buf.append(self.tk)
            self.next()
            t = self.expr5()
            if t is not None:
                buf.append(t)
                t = self.expr4()
                if t is not None:
                    if t != "null":
                        buf.append(t)
                    return buf
                else:
                    map(self.push, buf)
            else:
                map(self.push, buf)
        else:
            return 'null'

    def expr5(self):
        buf = []
        if isinstance(self.tk, Operator) and self.tk.value == '(':
            buf.append(self.tk)
            self.next()
            t = self.expr1()
            if t is not None:
                buf.append(t)
                t = self.tk
                if self.match(Operator, ')'):
                    buf.append(t)
                    return buf
                else:
                    map(self.push, buf)
            else:
                map(self.push, buf)
        elif isinstance(self.tk, Integer):
            t = self.tk
            self.next()
            return t
        elif isinstance(self.tk, Float):
            t = self.tk
            self.next()
            return t
        elif isinstance(self.tk, String):
            t = self.tk
            self.next()
            return t
        elif isinstance(self.tk, Identifier):
            self.symbol.get(self.tk.value)
            t = self.tk
            self.next()
            return t
        else:
            t = self.call()
            if t is not None:
                return t

    def decl(self):
        buf = []
        if isinstance(self.tk, Type):
            buf.append(self.tk)
            self.next()
            if isinstance(self.tk, Identifier):
                buf.append(self.tk)
                self.next()
                if isinstance(self.tk, Operator) and self.tk.value == '=':
                    buf.append(self.tk)
                    self.next()
                    t = self.expr1()
                    if t is not None:
                        buf.append(t)
                        if isinstance(self.tk, Operator) and self.tk.value == ';':
                            buf.append(self.tk)
                            self.next()
                            self.symbol.decl(buf[0], buf[1].value)
                            self.symbol.set(buf[1].value, 0)
                            self.symbol.set(buf[1].value, 0)
                            return buf
                elif isinstance(self.tk, Operator) and self.tk.value == ';':
                    buf.append(self.tk)
                    self.next()
                    self.symbol.decl(buf[0], buf[1].value)
                    return buf
        map(self.push, buf)

    def assign(self):
        buf = []
        if isinstance(self.tk, Identifier):
            buf.append(self.tk)
            self.next()
            if isinstance(self.tk, Operator) and self.tk.value == '=':
                buf.append(self.tk)
                self.next()
                t = self.expr1()
                if t is not None:
                    buf.append(t)
                    if isinstance(self.tk, Operator) and self.tk.value == ';':
                        buf.append(self.tk)
                        self.next()
                        return buf
        map(self.push, buf)

    def stmt(self):
        buf = []
        while True:
            if self.eof:
                break
            t = self.decl()
            if t is not None:
                buf.append(t)
                continue
            t = self.expr1()
            if t is not None:
                if isinstance(self.tk, Operator) and self.tk.value == ';':
                    buf.append([t, self.tk])
                    self.next()
                    continue
                else:
                    self.push(t)
            t = self.assign()
            if t is not None:
                buf.append(t)
                continue
            t = self.block()
            if t is not None:
                buf.append(t)
                continue
            if isinstance(self.tk, Operator) and self.tk.value == ';':
                buf.append(self.tk)
                self.next()
                continue
            break
        return buf

    def block(self):
        buf = []
        if isinstance(self.tk, Operator) and self.tk.value == '{':
            self.symbol.push()
            buf.append(self.tk)
            self.next()
            t = self.stmt()
            if t is not None:
                buf.append(t)
                if isinstance(self.tk, Operator) and self.tk.value == '}':
                    self.symbol.pop()
                    buf.append(self.tk)
                    self.next()
                    return buf
        map(self.push, buf)

    def call(self):
        buf = []
        if isinstance(self.tk, Operator) and self.tk.value == '[':
            buf.append(self.tk)
            self.next()
            if isinstance(self.tk, Identifier):
                buf.append(self.tk)
                self.next()
                while True:
                    t = self.expr1()
                    if t is not None:
                        buf.append(t)
                    break
                if isinstance(self.tk, Operator) and self.tk.value == ']':
                    buf.append(self.tk)
                    self.next()
                    return buf
        map(self.push, buf)

    def printSyntaxTree(self, t, deep = 0):
        if isinstance(t, list):
            for i in t:
                self.printSyntaxTree(i, deep + 1)
        else:
            print deep * '  ', t


