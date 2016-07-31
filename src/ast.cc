#include <sstream>

#include "ast.h"
#include "utils.h"


sb_ast_desc_t sb_ast_desc[AST_T_COUNT] = {
    { AST_T_NONE, "NONE" },
    { AST_T_INVALID, "INVALID"},
    { AST_T_TOKEN, "TOKEN"},
    { AST_T_PROGRAM, "PROGRAM"},
    { AST_T_STATEMENTS, "STATEMENTS"},
    { AST_T_STATEMENT, "STATEMENT"},
    { AST_T_ASSIGNMENT_STATEMENT, "ASSIGNMENT_STATEMENT"},
    { AST_T_EXPRESSION, "EXPRESSION"},
    { AST_T_ADDITIVE_EXPRESSION, "ADDITIVE_EXPRESSION"},
    { AST_T_MULTIPICATE_EXPRESSION, "MULTIPICATE_EXPRESSION"},
    { AST_T_PRIMARY_EXPRESSION, "PRIMARY_EXPRESSION"},
    { AST_T_LITERAL, "LITERAL"},
};

sb_ast::sb_ast(sb_ast_type_t _type) : type(_type) {}

sb_ast::sb_ast(sb_ast_type_t _type, size_t _begin_tk_pos, size_t _end_tk_pos)
    : type(_type), begin_tk_pos(_begin_tk_pos), end_tk_pos(_end_tk_pos) {}

sb_ast::~sb_ast() {}

string sb_ast::info() {
    return format("{ %zu:%zu %s }", begin_tk_pos, end_tk_pos, sb_ast_desc[type].name.c_str());
}

sb_ast_program::sb_ast_program(sb_ast *_statements)
    : sb_ast(AST_T_PROGRAM), statements(_statements) {}

sb_ast_token::sb_ast_token(sb_token &_token) : sb_ast(AST_T_TOKEN), token(_token) {}

sb_ast_token::sb_ast_token(sb_token &_token, size_t pos)
    : sb_ast(AST_T_TOKEN, pos, pos), token(_token) {}


string sb_ast_token::info() {
    return format("{ %zu %s }", begin_tk_pos, token.info().c_str());
    
}

sb_ast_statements::sb_ast_statements(std::vector<sb_ast *> &_statements)
    : sb_ast(AST_T_STATEMENTS), statements(_statements) {}

sb_ast_statement::sb_ast_statement(sb_ast *_statement)
    : sb_ast(AST_T_STATEMENT), statement(_statement) {}

sb_ast_assignment_statement::sb_ast_assignment_statement(sb_ast *_left, sb_ast *_right)
    : sb_ast(AST_T_ASSIGNMENT_STATEMENT), left(_left), right(_right) {}


sb_ast_expression::sb_ast_expression(sb_ast *_expression)
    : sb_ast(AST_T_EXPRESSION), expression(_expression) {}


sb_ast_additive_expression::sb_ast_additive_expression(sb_ast *_base,
                                                       vector<pair<sb_ast *, sb_ast *>> &_v)
    : sb_ast(AST_T_ADDITIVE_EXPRESSION), base(_base), v(_v) {}

sb_ast_multipicative_expression::sb_ast_multipicative_expression(
    sb_ast *_base,
    vector<pair<sb_ast *, sb_ast *>> &_v)
    : sb_ast(AST_T_MULTIPICATE_EXPRESSION), base(_base), v(_v) {}

sb_ast_primary_expression::sb_ast_primary_expression(sb_ast *_exp)
    : sb_ast(AST_T_PRIMARY_EXPRESSION), exp(_exp) {}

sb_ast_literal::sb_ast_literal(sb_ast *_value) : sb_ast(AST_T_LITERAL), value(_value) {}
