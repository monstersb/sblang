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
} sb_token_type_t;

class sb_token {
public:
    sb_token_type_t type;
    string str;
    
    sb_token();
    sb_token(sb_token_type_t t, char c);
    sb_token(sb_token_type_t t, string s);
    sb_token(sb_token_type_t t, vector<char> v);
    ~sb_token();
    
    string info();
};

#endif // SB_TOKEN_H