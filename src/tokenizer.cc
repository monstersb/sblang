#include <ctype.h>
#include <assert.h>

#include "tokenizer.h"
#include "log.h"
#include "utils.h"

sb_tokenizer::sb_tokenizer(std::istream &in)
    : in(in), _line(1), _column(0), eof(false), invalid(false) {
    init_keyword();
    get_char();
    sb_log::debug("sb_tokenizer inited");
}

sb_tokenizer::~sb_tokenizer() {}

void sb_tokenizer::init_keyword() {
    keyword["print"] = TK_T_K_PRINT;
    keyword["if"] = TK_T_K_IF;
    keyword["while"] = TK_T_K_WHILE;
}

bool sb_tokenizer::is_white_char(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

int sb_tokenizer::get_char() {
    int c = in.get();
    if (c == EOF) {
        eof = true;
    } else {
        if (c == '\n' || c == '\r') {
            _line += 1;
            _column = 1;
        } else {
            _column += 1;
        }
        source.push_back(c);
    }
    lookahead = c;
    return c;
}

void sb_tokenizer::skip_white() {
    while (is_white_char(lookahead)) {
        get_char();
    }
}


sb_token_type_t sb_tokenizer::keyword_type(string s) {
    if (keyword.find(s) != keyword.end()) {
        return keyword[s];
    } else {
        return TK_T_ID;
    }
}

bool sb_tokenizer::stop() {
    return eof || invalid;
}

size_t sb_tokenizer::line() {
    return _line;
}

size_t sb_tokenizer::column() {
    return _column;
}

sb_token &sb_tokenizer::next() {
    std::vector<char> buffer;
    sb_token tk;
    skip_white();
    size_t tk_line = _line;
    size_t tk_column = _column;
    switch (lookahead) {
        case '0' ... '9': {
            do {
                buffer.push_back(lookahead);
                get_char();
            } while (isdigit(lookahead));
            tk = sb_token(TK_T_NUMBER, buffer, tk_line, tk_column);
            break;
        }
        case 'a' ... 'z':
        case 'A' ... 'Z':
        case '_': {
            do {
                buffer.push_back(lookahead);
                get_char();
            } while (isalnum(lookahead) || lookahead == '_');
            tk = sb_token(keyword_type(string(buffer.begin(), buffer.end())), buffer, tk_line,
                          tk_column);
            break;
        }
        case '=':
            get_char();
            if (lookahead == '=') {
                tk.set(TK_T_EQ, "==", tk_line, tk_column);
                get_char();
            } else {
                tk.set(TK_T_ASSIGN, '=', tk_line, tk_column);
            }
            break;
        case '!':
            get_char();
            if (lookahead == '=') {
                tk.set(TK_T_NEQ, "!=", tk_line, tk_column);
                get_char();
            } else {
                tk.set(TK_T_L_NOT, '!', tk_line, tk_column);
            }
            break;
        case '&':
            get_char();
            if (lookahead == '&') {
                tk.set(TK_T_L_AND, "&&", tk_line, tk_column);
                get_char();
            } else {
                tk.set(TK_T_B_AND, '&', tk_line, tk_column);
            }
            break;
        case '|':
            get_char();
            if (lookahead == '|') {
                tk.set(TK_T_L_OR, "||", tk_line, tk_column);
                get_char();
            } else {
                tk.set(TK_T_B_OR, '|', tk_line, tk_column);
            }
            break;
        case '~':
            tk.set(TK_T_B_NOT, '~', tk_line, tk_column);
            get_char();
            break;
        case '^':
            tk.set(TK_T_B_XOR, '^', tk_line, tk_column);
            get_char();
            break;
        case '+':
            tk.set(TK_T_ADD, '+', tk_line, tk_column);
            get_char();
            break;
        case '-':
            tk.set(TK_T_SUB, '-', tk_line, tk_column);
            get_char();
            break;
        case '*':
            tk.set(TK_T_MUL, '*', tk_line, tk_column);
            get_char();
            break;
        case '/':
            tk.set(TK_T_DIV, '/', tk_line, tk_column);
            get_char();
            break;
        case '<':
            get_char();
            if (lookahead == '=') {
                tk.set(TK_T_LTE, "<=", tk_line, tk_column);
                get_char();
            } else {
                tk.set(TK_T_LT, '<', tk_line, tk_column);
            }
            break;
        case '>':
            get_char();
            if (lookahead == '=') {
                tk.set(TK_T_GTE, ">=", tk_line, tk_column);
                get_char();
            } else {
                tk.set(TK_T_GT, '>', tk_line, tk_column);
            }
            break;
        case ';':
            tk.set(TK_T_SEMI, ';', tk_line, tk_column);
            get_char();
            break;
        case '(':
            tk.set(TK_T_LPAR, '(', tk_line, tk_column);
            get_char();
            break;
        case ')':
            tk.set(TK_T_RPAR, ')', tk_line, tk_column);
            get_char();
            break;
        case '{':
            tk.set(TK_T_LBRACE, '{', tk_line, tk_column);
            get_char();
            break;
        case '}':
            tk.set(TK_T_RBRACE, '}', tk_line, tk_column);
            get_char();
            break;
        case EOF:
            tk.set(TK_T_EOF, tk_line, tk_column);
            break;
        default:
            tk.set(TK_T_INVALID, buffer, tk_line, tk_column);
            sb_log::error(format("INVALID TOKEN at line: %zu, column: %zu", tk_line, tk_column));
            invalid = true;
            break;
    }
    tokens.push_back(tk);
    return last_token();
}

bool sb_tokenizer::tokenize() {
    sb_log::debug("tokenizer started");
    while (!invalid) {
        sb_token &tk = next();
        if (tk.type == TK_T_EOF) {
            return true;
        }
    }
    return false;
}


sb_token &sb_tokenizer::operator[](size_t i) {
    assert(i < tokens.size());
    return tokens[i];
}


sb_token &sb_tokenizer::last_token() {
    return tokens.back();
}
