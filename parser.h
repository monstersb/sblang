#ifndef SB_PARSER_H
#define SB_PARSER_H

#include <iostream>

#include "tokenizer.h"

class parser {
private:
    tokenizer _tokenizer;
    
public:
    parser(std::istream &in);
    ~parser();
    
    void parse();
};

#endif // SB_PARSER_H