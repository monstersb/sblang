#ifndef SB_AST_H
#define SB_AST_H

#include <vector>
#include <utility>

#include "token.h"
#include "type.h"

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
    AST_T_IF_STATEMENT,
    AST_T_PRINT_STATEMENT,
    AST_T_BLOCK_STATEMENT,
    AST_T_EXPRESSION,
    AST_T_ADDITIVE_EXPRESSION,
    AST_T_MULTIPICATE_EXPRESSION,
    AST_T_PRIMARY_EXPRESSION,
    AST_T_LITERAL,

    AST_T_COUNT,
} sb_ast_type_t;

typedef struct {
    sb_ast_type_t type;
    string name;
} sb_ast_desc_t;

extern sb_ast_desc_t sb_ast_desc[AST_T_COUNT];

class sb_ast {
public:
    sb_ast_type_t type;
    size_t begin_tk_pos;
    size_t end_tk_pos;

    sb_ast(sb_ast_type_t _type);
    sb_ast(sb_ast_type_t _type, size_t _begin_tk_pos, size_t _end_tk_pos);
    virtual ~sb_ast();

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_token : public sb_ast {
public:
    sb_token token;

    sb_ast_token(sb_token &_token);
    sb_ast_token(sb_token &_token, size_t pos);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_program : public sb_ast {
public:
    sb_ast *statements;

    sb_ast_program(sb_ast *_statements);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_statements : public sb_ast {
public:
    vector<sb_ast *> statements;

    sb_ast_statements(vector<sb_ast *> &_statements);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_statement : public sb_ast {
public:
    sb_ast *statement;

    sb_ast_statement(sb_ast *_statement);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_assignment_statement : public sb_ast {
public:
    sb_ast *left;
    sb_ast *right;

    sb_ast_assignment_statement(sb_ast *_left, sb_ast *_right);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_if_statement : public sb_ast {
public:
    sb_ast *test;
    sb_ast *statement;

    sb_ast_if_statement(sb_ast *_test, sb_ast *_statement);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_print_statement : public sb_ast {
public:
    sb_ast *exp;
    
    sb_ast_print_statement(sb_ast *_exp);
    
    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_block_statement : public sb_ast {
public:
    sb_ast *statements;
    
    sb_ast_block_statement(sb_ast *_statements);
    
    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_expression : public sb_ast {
public:
    sb_ast *expression;

    sb_ast_expression(sb_ast *_expression);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_additive_expression : public sb_ast {
public:
    sb_ast *base;
    vector<pair<sb_ast *, sb_ast *>> v;

    sb_ast_additive_expression(sb_ast *_base, vector<pair<sb_ast *, sb_ast *>> &_v);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_multipicative_expression : public sb_ast {
public:
    sb_ast *base;
    vector<pair<sb_ast *, sb_ast *>> v;

    sb_ast_multipicative_expression(sb_ast *_base, vector<pair<sb_ast *, sb_ast *>> &_v);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_primary_expression : public sb_ast {
public:
    sb_ast *exp;

    sb_ast_primary_expression(sb_ast *_exp);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

class sb_ast_literal : public sb_ast {
public:
    sb_ast *value;

    sb_ast_literal(sb_ast *_value);

    virtual string info();
    virtual string str();
    virtual sb_t_object *execute();
};

#endif // SB_AST_H
