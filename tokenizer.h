#include <istream>
#include <vector>
#include <string>

#include "token.h"

class tokenizer {
private:
    std::vector<token> tokens;
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

    
public:
    tokenizer(std::istream &in);
    ~tokenizer();
    
    bool stop();
    token next();

    int line();
    int column();
};
