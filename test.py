#! env python

from Parser import Parser
import sys

parser = Parser(sys.stdin)
parser.parse()
