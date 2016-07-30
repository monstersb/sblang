#ifndef SB_TOKEN_H
#define SB_TOKEN_H

#include <vector>
#include <string>

using std::vector;
using std::string;

typedef enum {
    TK_T_NONE,
    TK_T_INVALID,
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
} token_type;

class token {
public:
    token_type type;
    string str;
    
    token();
    token(token_type t, char c);
    token(token_type t, string s);
    token(token_type t, vector<char> v);
    
    string info();
};

#endif // SB_TOKEN_H