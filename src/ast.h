#ifndef SB_AST_H
#define SB_AST_H

#include <vector>
#include <utility>

#include "token.h"

using std::vector;
using std::pair;

typedef enum {
    AST_T_NONE,
    AST_T_INVALID,
    AST_T_TOKEN,
    AST_T_PROGRAM,
    AST_T_STATEMENTS,
    AST_T_STATEMENT,
    AST_T_ASSIGNMENT_STATEMENT,
    AST_T_EXPRESSION,
    AST_T_ADDITIVE_EXPRESSION,
    AST_T_COUNT,
} sb_ast_type_t;

class sb_ast {
private:
    sb_ast_type_t type;

public:
    sb_ast(sb_ast_type_t _type);
    ~sb_ast();

    string info();
};

class sb_ast_token : public sb_ast {
private:
    sb_token token;

public:
    sb_ast_token(sb_token &_token);
};

class sb_ast_program : public sb_ast {
private:
    sb_ast *statements;

public:
    sb_ast_program(sb_ast *_statements);
};

class sb_ast_statements : public sb_ast {
private:
    vector<sb_ast *> statements;

public:
    sb_ast_statements(vector<sb_ast *> &_statements);
};

class sb_ast_statement : public sb_ast {
private:
    sb_ast *statement;

public:
    sb_ast_statement(sb_ast *_statement);
};

class sb_ast_assignment_statement : public sb_ast {
private:
    sb_ast *left;
    sb_ast *right;

public:
    sb_ast_assignment_statement(sb_ast *_left, sb_ast *_right);
};

class sb_ast_expression : public sb_ast {
private:
    sb_ast *expression;

public:
    sb_ast_expression(sb_ast *_expression);
};

class sb_ast_additive_expression : public sb_ast {
private:
    sb_ast *base;
    vector<pair<sb_ast *, sb_ast *>> v;

public:
    sb_ast_additive_expression(sb_ast *_base, vector<pair<sb_ast *, sb_ast *>> &_v);
};

class sb_ast_multipicative_expression : public sb_ast {
private:
    sb_ast *base;
    vector<pair<sb_ast *, sb_ast *>> v;

public:
    sb_ast_multipicative_expression(sb_ast *_base, vector<pair<sb_ast *, sb_ast *>> &_v);
};

class sb_ast_primary_expression : public sb_ast {
private:
    sb_ast *exp;

public:
    sb_ast_primary_expression(sb_ast *_exp);
};

class sb_ast_literal : public sb_ast {
private:
    sb_ast *value;

public:
    sb_ast_literal(sb_ast *_value);
};

#endif // SB_AST_H