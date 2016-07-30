#include <sstream>
#include <iomanip>

#include "token.h"
#include "utils.h"

#define TOKEN_TYPE_NAME(_T)                                                                        \
    { _T, #_T }

struct {
    sb_token_type_t type;
    string name;
} token_type_name[TK_T_COUNT] = {
    TOKEN_TYPE_NAME(TK_T_NONE), TOKEN_TYPE_NAME(TK_T_INVALID), TOKEN_TYPE_NAME(TK_T_EOF),
    TOKEN_TYPE_NAME(TK_T_ID),   TOKEN_TYPE_NAME(TK_T_NUMBER),  TOKEN_TYPE_NAME(TK_T_ASSIGN),
    TOKEN_TYPE_NAME(TK_T_ADD),  TOKEN_TYPE_NAME(TK_T_SUB),     TOKEN_TYPE_NAME(TK_T_MUL),
    TOKEN_TYPE_NAME(TK_T_DIV),  TOKEN_TYPE_NAME(TK_T_SEMI),    TOKEN_TYPE_NAME(TK_T_LPAR),
    TOKEN_TYPE_NAME(TK_T_RPAR),
};


sb_token::sb_token() : type(TK_T_NONE), str(), line(0), column(0){};

sb_token::sb_token(sb_token_type_t t, char c, size_t _line, size_t _column)
    : type(t), str(1, c), line(_line), column(_column){};

sb_token::sb_token(sb_token_type_t t, string s, size_t _line, size_t _column)
    : type(t), str(s), line(_line), column(_column){};

sb_token::sb_token(sb_token_type_t t, vector<char> v, size_t _line, size_t _column)
    : type(t), str(v.begin(), v.end()), line(_line), column(_column){};

sb_token::~sb_token() {}


void sb_token::set(sb_token_type_t t, size_t _line, size_t _column) {
    type = t;
    str.clear();
    line = _line;
    column = _column;
}

void sb_token::set(sb_token_type_t t, char c, size_t _line, size_t _column) {
    type = t;
    str = string(1, c);
    line = _line;
    column = _column;
}

void sb_token::set(sb_token_type_t t, string s, size_t _line, size_t _column) {
    type = t;
    str = s;
    line = _line;
    column = _column;
}

void sb_token::set(sb_token_type_t t, vector<char> v, size_t _line, size_t _column) {
    type = t;
    str = string(v.begin(), v.end());
    line = _line;
    column = _column;
}


string sb_token::info() {
    std::ostringstream s;
    s.setf(std::ios::left);
    s << "{";
    s << "  " << std::setw(13) << token_type_name[type].name;
    s << "  (" << std::setw(3) << line << ", " << std::setw(2) << column << ")";
    s << "  " << std::setw(10) << repr(str);
    s << "}";
    return s.str();
}
