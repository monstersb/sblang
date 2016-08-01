#ifndef SB_TOKENIZER_H
#define SB_TOKENIZER_H


#include <istream>
#include <vector>
#include <string>

#include "token.h"

class sb_tokenizer {
private:
    std::vector<sb_token> tokens;
    std::string source;
    std::istream &in;
    size_t _line;
    size_t _column;
    int lookahead;
    bool eof;
    bool invalid;

    bool is_white_char(char c);
    int get_char();
    void skip_white();
    sb_token_type_t keyword_type(string s);


public:
    sb_tokenizer(std::istream &in);
    ~sb_tokenizer();

    bool stop();
    sb_token &next();
    bool tokenize();
    sb_token &operator[](size_t i);
    sb_token &last_token();

    size_t line();
    size_t column();
};

#endif // SB_TOKENIZER_H