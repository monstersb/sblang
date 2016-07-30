#include <sstream>
#include <iomanip>

#include "token.h"
#include "utils.h"

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

string sb_token::info() {
    std::ostringstream s;
    s.setf(std::ios::left);
    s << "[ type: 0x" << std::setw(4) << std::hex << type << "str: " << std::setw(20) << repr(str) << "]";
    return s.str();
}