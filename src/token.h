#ifndef SB_TOKEN_H
#define SB_TOKEN_H

#include <vector>
#include <string>

using std::vector;
using std::string;

typedef enum {
    TK_T_NONE,
    TK_T_INVALID,
    TK_T_EOF,
    TK_T_ID,
    TK_T_NUMBER,
    TK_T_ASSIGN,
    TK_T_ADD,
    TK_T_SUB,
    TK_T_MUL,
    TK_T_DIV,
    TK_T_SEMI,
    TK_T_LPAR,
    TK_T_RPAR,

    TK_T_COUNT,
} sb_token_type_t;


class sb_token {
public:
    sb_token_type_t type;
    string str;
    size_t line;
    size_t column;

    sb_token();
    sb_token(sb_token_type_t t, char c, size_t _line, size_t _column);
    sb_token(sb_token_type_t t, string s, size_t _line, size_t _column);
    sb_token(sb_token_type_t t, vector<char> v, size_t _line, size_t _column);
    ~sb_token();

    void set(sb_token_type_t t, size_t _line, size_t _column);
    void set(sb_token_type_t t, char c, size_t _line, size_t _column);
    void set(sb_token_type_t t, string s, size_t _line, size_t _column);
    void set(sb_token_type_t t, vector<char> v, size_t _line, size_t _column);

    string info();
};

#endif // SB_TOKEN_H