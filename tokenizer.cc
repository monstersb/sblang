#include <ctype.h>

#include "tokenizer.h"


tokenizer::tokenizer(std::istream &in): in(in), _line(1), _column(0), eof(false), invalid(false) {
    get_char();
}

tokenizer::~tokenizer() {
}

bool tokenizer::is_white_char(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

int tokenizer::get_char() {
    int c = in.get();
    if (c == '\n' || c == '\r') {
        _line += 1;
        _column = 1;
    } else {
        _column += 1;
    }
    if (c == EOF) {
        eof = true;
    } else {
        source.push_back(c);
    }
    lookahead = c;
    return c;
}

void tokenizer::skip_white() {
    while (is_white_char(lookahead)) {
        get_char();
    }
}

bool tokenizer::stop() {
    return eof || invalid;
}

size_t tokenizer::line() {
    return _line;
}

size_t tokenizer::column() {
    return _column;
}

token tokenizer::next() {
    std::vector<char> buffer;
    token tk;
    skip_white();
    switch (lookahead) {
        case '0' ... '9': {
            do {
                buffer.push_back(lookahead);
                get_char();
            } while (isdigit(lookahead));
            tk = token(TK_T_NUMBER, buffer);
            break;
        }
        case 'a' ... 'z':
        case 'A' ... 'Z':
        case '_':{
            do {
                buffer.push_back(lookahead);
                get_char();
            } while (isalnum(lookahead) || lookahead == '_');
            tk = token(TK_T_ID, buffer);
            break;
        }
        case '=':
            tk = token(TK_T_ASSIGN, '=');
            get_char();
            break;
        case '+':
            tk = token(TK_T_ADD, '+');
            get_char();
            break;
        case '-':
            tk = token(TK_T_SUB, '-');
            get_char();
            break;
        case '*':
            tk = token(TK_T_MUL, '*');
            get_char();
            break;
        case '/':
            tk = token(TK_T_DIV, '/');
            get_char();
            break;
        case ';':
            tk = token(TK_T_SEMI, ';');
            get_char();
            break;
        case '(':
            tk = token(TK_T_LPAR, '(');
            get_char();
            break;
        case ')':
            tk = token(TK_T_RPAR, ')');
            get_char();
            break;
        case EOF:
            break;
            
        default:
            tk.type = TK_T_INVALID;
            invalid = true;
            break;
    }
    if (tk.type != TK_T_NONE) {
        tokens.push_back(tk);
    }
    return tk;
}
