#include "token.h"


token::token():type(TK_T_NONE), str() {
};

token::token(token_type t, char c):type(t), str(1, c) {
};

token::token(token_type t, string s):type(t), str(s) {
};

token::token(token_type t, vector<char> v):type(t), str(v.begin(), v.end()) {
};

string token::info() {
    return str;
}