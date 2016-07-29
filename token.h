#include <vector>
#include <string>

using std::vector;
using std::string;

typedef enum {
    TK_T_NONE,
    TK_T_INVALID,
    TK_T_IDENTIFIER,
    TK_T_NUMBER,
    TK_T_ASSIGNMENT,
    TK_T_ADDITION,
    TK_T_MINUS,
    TK_T_MULTIPLICATION,
    TK_T_DIVISION,
    TK_T_SEMI,
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
