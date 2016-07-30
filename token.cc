#include <sstream>
#include <iomanip>

#include "token.h"
#include "utils.h"

#define TOKEN_TYPE_NAME(_T) {_T, #_T}

struct {
    sb_token_type_t type;
    string name;
} token_type_name[TK_T_COUNT] = {
    TOKEN_TYPE_NAME(TK_T_NONE),
    TOKEN_TYPE_NAME(TK_T_INVALID),
    TOKEN_TYPE_NAME(TK_T_EOF),
    TOKEN_TYPE_NAME(TK_T_ID),
    TOKEN_TYPE_NAME(TK_T_NUMBER),
    TOKEN_TYPE_NAME(TK_T_ASSIGN),
    TOKEN_TYPE_NAME(TK_T_ADD),
    TOKEN_TYPE_NAME(TK_T_SUB),
    TOKEN_TYPE_NAME(TK_T_MUL),
    TOKEN_TYPE_NAME(TK_T_DIV),
    TOKEN_TYPE_NAME(TK_T_SEMI),
    TOKEN_TYPE_NAME(TK_T_LPAR),
    TOKEN_TYPE_NAME(TK_T_RPAR),
};


sb_token::sb_token():type(TK_T_NONE), str() {
};

sb_token::sb_token(sb_token_type_t t, char c):type(t), str(1, c) {
};

sb_token::sb_token(sb_token_type_t t, string s):type(t), str(s) {
};

sb_token::sb_token(sb_token_type_t t, vector<char> v):type(t), str(v.begin(), v.end()) {
};

sb_token::~sb_token() {
}


void sb_token::set(sb_token_type_t t) {
    type = t;
    str.clear();
}

void sb_token::set(sb_token_type_t t, char c) {
    type = t;
    str = string(1, c);
}

void sb_token::set(sb_token_type_t t, string s) {
    type = t;
    str = s;
}

void sb_token::set(sb_token_type_t t, vector<char> v) {
    type = t;
    str = string(v.begin(), v.end());
}


string sb_token::info() {
    std::ostringstream s;
    s.setf(std::ios::left);
    s << "[ type: " << std::setw(15) << token_type_name[type].name << "str: " << std::setw(20) << repr(str) << "]";
    return s.str();
}