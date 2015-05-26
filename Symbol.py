from collections import deque

class Symbol(object):
    def __init__(self, tp, name, value):
        self.tp = tp
        self.name = name
        self.value = value

class SymbolTable(object):
    def __init__(self):
        self.stack = deque()
        self.push()

    def push(self):
        self.stack.append(dict())

    def pop(self):
        self.stack.pop()

    def top(self):
        return self.stack[-1]

    def decl(self, tp, name):
        if name in self.top().keys():
            raise NameError("Redefined identifier")
        self.top()[name] = Symbol(tp, name, None)

    def set(self, name, value):
        self.get(name).value = value

    def get(self, name):
        for x in range(len(self.stack) - 1, -1, -1):
            if name in self.stack[x].keys():
                return self.stack[x][name]
        raise NameError('Undefined identifier')
