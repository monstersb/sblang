#include <istream>
#include <vector>

#include "token.h"

class tokenizer {
private:
    std::vector<token> tokens;
    std::vector<char> source;
    std::istream &in;
    size_t line;
    size_t column;
    int lookahead;
    bool eof;
    
    bool is_white_char(char c);
    int get_char();
    void skip_white();

    
public:
    tokenizer(std::istream &in);
    ~tokenizer();
    
    bool stop();
    token next();
};
