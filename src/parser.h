#ifndef SB_PARSER_H
#define SB_PARSER_H

#include <iostream>

#include "token.h"
#include "tokenizer.h"
#include "ast.h"

class sb_parser {
private:
    sb_tokenizer tokenizer;
    sb_ast *ast;
    size_t token_pos;

    sb_token &lookahead();

    sb_ast *accept_program();
    sb_ast *accept_token(sb_token_type_t type);
    sb_ast *accept_statements();
    sb_ast *accept_statement();
    sb_ast *accept_assignment_statements();
    sb_ast *accept_if_statements();
    sb_ast *accept_while_statements();
    sb_ast *accept_print_statements();
    sb_ast *accept_block_statements();
    sb_ast *accept_expression();
    sb_ast *accept_relational_expression();
    sb_ast *accept_additive_expression();
    sb_ast *accept_multiplicative_expression();
    sb_ast *accept_primary_expression();
    sb_ast *accept_literal();


public:
    sb_parser(std::istream &in);
    ~sb_parser();

    sb_ast *parse();
};

#endif // SB_PARSER_H
