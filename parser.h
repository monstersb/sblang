#ifndef SB_PARSER_H
#define SB_PARSER_H

#include <iostream>

#include "tokenizer.h"
#include "ast.h"

class sb_parser {
private:
    sb_tokenizer tokenizer;
    
public:
    sb_parser(std::istream &in);
    ~sb_parser();
    
    void parse();
};

#endif // SB_PARSER_H