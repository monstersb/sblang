#include <iostream>
#include <sstream>

#include "ast.h"
#include "utils.h"
#include "log.h"


sb_ast_desc_t sb_ast_desc[AST_T_COUNT] = {
    {AST_T_NONE, "NONE"},
    {AST_T_INVALID, "INVALID"},
    {AST_T_TOKEN, "TOKEN"},
    {AST_T_PROGRAM, "PROGRAM"},
    {AST_T_STATEMENTS, "STATEMENTS"},
    {AST_T_STATEMENT, "STATEMENT"},
    {AST_T_ASSIGNMENT_STATEMENT, "ASSIGNMENT_STATEMENT"},
    {AST_T_PRINT_STATEMENT, "PRINT_STATEMENT"},
    {AST_T_BLOCK_STATEMENT, "BLOCK_STATEMENT"},
    {AST_T_EXPRESSION, "EXPRESSION"},
    {AST_T_ADDITIVE_EXPRESSION, "ADDITIVE_EXPRESSION"},
    {AST_T_MULTIPICATE_EXPRESSION, "MULTIPICATE_EXPRESSION"},
    {AST_T_PRIMARY_EXPRESSION, "PRIMARY_EXPRESSION"},
    {AST_T_LITERAL, "LITERAL"},
};


sb_ast::sb_ast(sb_ast_type_t _type) : type(_type) {}

sb_ast::sb_ast(sb_ast_type_t _type, size_t _begin_tk_pos, size_t _end_tk_pos)
    : type(_type), begin_tk_pos(_begin_tk_pos), end_tk_pos(_end_tk_pos) {}

sb_ast::~sb_ast() {}

string sb_ast::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast::str() {
    return string();
}

sb_t_object *sb_ast::execute() {
    return new sb_t_object();
}


sb_ast_program::sb_ast_program(sb_ast *_statements)
    : sb_ast(AST_T_PROGRAM), statements(_statements) {}

string sb_ast_program::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_program::str() {
    return statements->str();
}

sb_t_object *sb_ast_program::execute() {
    return statements->execute();
}


sb_ast_token::sb_ast_token(sb_token &_token) : sb_ast(AST_T_TOKEN), token(_token) {}

sb_ast_token::sb_ast_token(sb_token &_token, size_t pos)
    : sb_ast(AST_T_TOKEN, pos, pos), token(_token) {}


string sb_ast_token::info() {
    return format("{ %zu:%zu T_%s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_token_desc[token.type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_token::str() {
    return token.str;
}

sb_t_object *sb_ast_token::execute() {
    return new sb_t_null();
}


sb_ast_statements::sb_ast_statements(std::vector<sb_ast *> &_statements)
    : sb_ast(AST_T_STATEMENTS), statements(_statements) {}

string sb_ast_statements::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_statements::str() {
    std::ostringstream s;
    for (auto i = statements.begin(); i != statements.end(); ++i) {
        sb_log::error((*i)->str());
        s << (*i)->str() << ";";
    }
    return s.str();
}

sb_t_object *sb_ast_statements::execute() {
    for (auto i = statements.begin(); i != statements.end(); ++i) {
        (*i)->execute();
    }
    return new sb_t_null();
}


sb_ast_statement::sb_ast_statement(sb_ast *_statement)
    : sb_ast(AST_T_STATEMENT), statement(_statement) {}

string sb_ast_statement::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_statement::str() {
    return statement->str();
}

sb_t_object *sb_ast_statement::execute() {
    return statement->execute();
}


sb_ast_assignment_statement::sb_ast_assignment_statement(sb_ast *_left, sb_ast *_right)
    : sb_ast(AST_T_ASSIGNMENT_STATEMENT), left(_left), right(_right) {}


string sb_ast_assignment_statement::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_assignment_statement::str() {
    return format("%s=%s", left->str().c_str(), right->str().c_str());
}

sb_t_object *sb_ast_assignment_statement::execute() {
    sb_t_object *value = right->execute();
    return value;
}


sb_ast_print_statement::sb_ast_print_statement(sb_ast *_exp)
: sb_ast(AST_T_PRINT_STATEMENT), exp(_exp) {}


string sb_ast_print_statement::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_print_statement::str() {
    return format("print %s", exp->str().c_str());
}

sb_t_object *sb_ast_print_statement::execute() {
    sb_t_object *value = exp->execute();
    std::cout << value->str() << std::endl;
    return value;
}


sb_ast_block_statement::sb_ast_block_statement(sb_ast *_statements)
: sb_ast(AST_T_BLOCK_STATEMENT), statements(_statements) {}


string sb_ast_block_statement::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_block_statement::str() {
    return format("{%s}", statements->str().c_str());
}

sb_t_object *sb_ast_block_statement::execute() {
    return statements->execute();
}


sb_ast_expression::sb_ast_expression(sb_ast *_expression)
    : sb_ast(AST_T_EXPRESSION), expression(_expression) {}


string sb_ast_expression::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_expression::str() {
    return expression->str();
}

sb_t_object *sb_ast_expression::execute() {
    return expression->execute();
}


sb_ast_additive_expression::sb_ast_additive_expression(sb_ast *_base,
                                                       vector<pair<sb_ast *, sb_ast *>> &_v)
    : sb_ast(AST_T_ADDITIVE_EXPRESSION), base(_base), v(_v) {}


string sb_ast_additive_expression::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_additive_expression::str() {
    std::ostringstream s;
    s << base->str();
    for (auto i = v.begin(); i != v.end(); ++i) {
        s << i->first->str() << i->second->str();
    }
    return s.str();
}

sb_t_object *sb_ast_additive_expression::execute() {
    return new sb_t_int(0);
}


sb_ast_multipicative_expression::sb_ast_multipicative_expression(
    sb_ast *_base,
    vector<pair<sb_ast *, sb_ast *>> &_v)
    : sb_ast(AST_T_MULTIPICATE_EXPRESSION), base(_base), v(_v) {}


string sb_ast_multipicative_expression::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_multipicative_expression::str() {
    std::ostringstream s;
    s << base->str();
    for (auto i = v.begin(); i != v.end(); ++i) {
        s << i->first->str() << i->second->str();
    }
    return s.str();
}

sb_t_object *sb_ast_multipicative_expression::execute() {
    return new sb_t_int(0);
}


sb_ast_primary_expression::sb_ast_primary_expression(sb_ast *_exp)
    : sb_ast(AST_T_PRIMARY_EXPRESSION), exp(_exp) {}

string sb_ast_primary_expression::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_primary_expression::str() {
    if (exp->type == AST_T_EXPRESSION) {
        return format("(%s)", exp->str().c_str());
    } else if (exp->type == AST_T_LITERAL) {
        return exp->str();
    } else if (exp->type == AST_T_TOKEN && ((sb_ast_token *)exp)->token.type == TK_T_ID) {
        return ((sb_ast_token *)exp)->token.str;
    } else {
        return string();
    }
}

sb_t_object *sb_ast_primary_expression::execute() {
    return exp->execute();
}


sb_ast_literal::sb_ast_literal(sb_ast *_value) : sb_ast(AST_T_LITERAL), value(_value) {}

string sb_ast_literal::info() {
    return format("{ %zu:%zu %s %s }",
                  begin_tk_pos,
                  end_tk_pos,
                  sb_ast_desc[type].name.c_str(),
                  repr(str()).c_str());
}

string sb_ast_literal::str() {
    return value->str();
}

sb_t_object *sb_ast_literal::execute() {
    if (value->type == AST_T_TOKEN && ((sb_ast_token *)value)->token.type == TK_T_NUMBER) {
        return new sb_t_int(0);
    } else {
        return value->execute();
    }
}
