#include "token.h"
#include "utils.h"

sb_token_desc_t sb_token_desc[TK_T_COUNT] = {
    {TK_T_NONE, "NONE"}, {TK_T_INVALID, "INVALID"}, {TK_T_EOF, "EOF"},
    {TK_T_ID, "ID"},     {TK_T_NUMBER, "NUMBER"},   {TK_T_ASSIGN, "ASSIGN"},
    {TK_T_EQ, "EQ"},     {TK_T_ADD, "ADD"},         {TK_T_SUB, "SUB"},
    {TK_T_MUL, "MUL"},   {TK_T_DIV, "DIV"},         {TK_T_LT, "LT"},
    {TK_T_GT, "GT"},     {TK_T_SEMI, "SEMI"},       {TK_T_LPAR, "LPAR"},
    {TK_T_RPAR, "RPAR"}, {TK_T_LBRACE, "LBRACE"},   {TK_T_RBRACE, "RBRACE"},
    {TK_T_K_IF, "K_IF"}, {TK_T_K_WHILE, "K_WHILE"}, {TK_T_K_PRINT, "K_PRINT"},
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
    return format("{ %s  (%zu, %zu)  %s }", sb_token_desc[type].name.c_str(), line, column,
                  repr(str).c_str());
}
