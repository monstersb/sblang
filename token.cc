#include <sstream>
#include <iomanip>

#include "token.h"
#include "utils.h"

token::token():type(TK_T_NONE), str() {
};

token::token(token_type t, char c):type(t), str(1, c) {
};

token::token(token_type t, string s):type(t), str(s) {
};

token::token(token_type t, vector<char> v):type(t), str(v.begin(), v.end()) {
};

string token::info() {
    std::ostringstream s;
    s.setf(std::ios::left);
    s << "[ type: 0x" << std::setw(4) << std::hex << type << "str: " << std::setw(20) << repr(str) << "]";
    return s.str();
}