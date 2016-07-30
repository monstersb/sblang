#include "ast.h"

#include <sstream>

sb_ast::sb_ast(sb_ast_type_t _type): type(_type) {

}

sb_ast::~sb_ast() {

}

string sb_ast::info() {
    std::ostringstream s;
    s << "[ type: " << type << " ]";
    return s.str();
}

sb_ast_program::sb_ast_program(sb_ast* _statements):sb_ast(AST_T_PROGRAM), statements(_statements) {

}

sb_ast_token::sb_ast_token(sb_token &_token):sb_ast(AST_T_TOKEN), token(_token) {

}

sb_ast_statements::sb_ast_statements(std::vector<sb_ast*> &_statements):sb_ast(AST_T_STATEMENTS), statements(_statements) {

}

sb_ast_statement::sb_ast_statement(sb_ast *_statement):sb_ast(AST_T_STATEMENT), statement(_statement) {

}

sb_ast_assignment_statement::sb_ast_assignment_statement(sb_ast *_left, sb_ast *_right):sb_ast(AST_T_ASSIGNMENT_STATEMENT), left(_left), right(_right) {

}


sb_ast_expression::sb_ast_expression(sb_ast *_expression):sb_ast(AST_T_EXPRESSION), expression(_expression) {

}


sb_ast_additive_expression::sb_ast_additive_expression(sb_ast *_base, vector<pair<sb_ast*, sb_ast*> > &_v):sb_ast(AST_T_ADDITIVE_EXPRESSION), base(_base), v(_v) {

}

sb_ast_multipicative_expression::sb_ast_multipicative_expression(sb_ast *_base, vector<pair<sb_ast*, sb_ast*> > &_v):sb_ast(AST_T_ADDITIVE_EXPRESSION), base(_base), v(_v) {
    
}

sb_ast_primary_expression::sb_ast_primary_expression(sb_ast *_exp):sb_ast(AST_T_ADDITIVE_EXPRESSION), exp(_exp) {
    
}

sb_ast_literal::sb_ast_literal(sb_ast *_value):sb_ast(AST_T_ADDITIVE_EXPRESSION), value(_value) {
    
}
