#include <utility>

#include "parser.h"
#include "log.h"
#include "utils.h"

sb_parser::sb_parser(std::istream &in) : tokenizer(in), ast(NULL), token_pos(0) {
    sb_log::debug("sb_parser inited");
}

sb_parser::~sb_parser() {}

sb_ast *sb_parser::parse() {
    sb_log::debug("parser started");
    if (!tokenizer.tokenize()) {
        return NULL;
    }
    ast = accept_program();
    return ast;
}


sb_token &sb_parser::lookahead() {
    return tokenizer[token_pos];
}

sb_ast *sb_parser::accept_token(sb_token_type_t type) {
    if (lookahead().type == type) {
        sb_ast *ast = new sb_ast_token(lookahead(), token_pos);
        sb_log::debug(ast->info());
        token_pos += 1;
        return ast;
    }
    return NULL;
}

sb_ast *sb_parser::accept_program() {
    sb_ast *statements = accept_statements();
    if (statements) {
        sb_ast *eof = accept_token(TK_T_EOF);
        if (eof) {
            delete eof;
            sb_ast *ast = new sb_ast_program(statements);
            ast->begin_tk_pos = statements->begin_tk_pos;
            ast->end_tk_pos = token_pos - 1;
            sb_log::debug(ast->info());
            return ast;
        }
        delete statements;
    }
    return NULL;
}

sb_ast *sb_parser::accept_statements() {
    size_t _begin_tk_pos = token_pos;
    vector<sb_ast *> statements;
    while (true) {
        sb_ast *statement = accept_statement();
        sb_ast *semi = accept_token(TK_T_SEMI);
        if (semi) {
            delete semi;
        } else {
            if (statement) {
                delete statement;
            }
            break;
        }
        if (statement) {
            statements.push_back(statement);
        }
    }
    sb_ast *ast = new sb_ast_statements(statements);
    ast->begin_tk_pos = _begin_tk_pos;
    ast->end_tk_pos = token_pos - 1;
    sb_log::debug(ast->info());
    return ast;
}

sb_ast *sb_parser::accept_statement() {
    sb_ast *statement = accept_assignment_statements();
    if (statement) {
        sb_ast *ast = new sb_ast_statement(statement);
        ast->begin_tk_pos = statement->begin_tk_pos;
        ast->end_tk_pos = token_pos - 1;
        sb_log::debug(ast->info());
        return ast;
    }
    return NULL;
}

sb_ast *sb_parser::accept_assignment_statements() {
    sb_ast *left = accept_token(TK_T_ID);
    if (left) {
        sb_ast *assign = accept_token(TK_T_ASSIGN);
        if (assign) {
            delete assign;
            sb_ast *right = accept_expression();
            if (right) {
                sb_ast *ast = new sb_ast_assignment_statement(left, right);
                ast->begin_tk_pos = left->begin_tk_pos;
                ast->end_tk_pos = token_pos - 1;
                sb_log::debug(ast->info());
                return ast;
            }
        }
        delete left;
    }
    return NULL;
}

sb_ast *sb_parser::accept_expression() {
    sb_ast *additive_expression = accept_additive_expression();
    if (additive_expression) {
        sb_ast *ast = new sb_ast_expression(additive_expression);
        ast->begin_tk_pos = additive_expression->begin_tk_pos;
        ast->end_tk_pos = token_pos - 1;
        sb_log::debug(ast->info());
        return ast;
    }
    return NULL;
}

sb_ast *sb_parser::accept_additive_expression() {
    sb_ast *base = accept_multiplicative_expression();
    if (base) {
        vector<pair<sb_ast *, sb_ast *>> v;
        while (true) {
            sb_ast *op = accept_token(TK_T_ADD);
            if (!op) {
                op = accept_token(TK_T_SUB);
            }
            if (!op) {
                break;
            }
            sb_ast *exp = accept_multiplicative_expression();
            if (!exp) {
                break;
            }
            v.push_back(pair<sb_ast *, sb_ast *>(op, exp));
        }
        sb_ast *ast = new sb_ast_additive_expression(base, v);
        ast->begin_tk_pos = base->begin_tk_pos;
        ast->end_tk_pos = token_pos - 1;
        sb_log::debug(ast->info());
        return ast;
    }
    return NULL;
}

sb_ast *sb_parser::accept_multiplicative_expression() {
    sb_ast *base = accept_primary_expression();
    if (base) {
        vector<pair<sb_ast *, sb_ast *>> v;
        while (true) {
            sb_ast *op = accept_token(TK_T_MUL);
            if (!op) {
                op = accept_token(TK_T_DIV);
            }
            if (!op) {
                break;
            }
            sb_ast *exp = accept_primary_expression();
            if (!exp) {
                break;
            }
            v.push_back(pair<sb_ast *, sb_ast *>(op, exp));
        }
        sb_ast *ast = new sb_ast_multipicative_expression(base, v);
        ast->begin_tk_pos = base->begin_tk_pos;
        ast->end_tk_pos = token_pos - 1;
        sb_log::debug(ast->info());
        return ast;
    }
    return NULL;
}

sb_ast *sb_parser::accept_primary_expression() {
    sb_ast *exp = accept_literal();
    if (exp) {
        sb_ast *ast = new sb_ast_primary_expression(exp);
        ast->begin_tk_pos = exp->begin_tk_pos;
        ast->end_tk_pos = token_pos - 1;
        sb_log::debug(ast->info());
        return ast;
    }
    exp = accept_token(TK_T_ID);
    if (exp) {
        sb_ast *ast = new sb_ast_primary_expression(exp);
        ast->begin_tk_pos = exp->begin_tk_pos;
        ast->end_tk_pos = exp->end_tk_pos;
        sb_log::debug(ast->info());
        return ast;
    }
    sb_ast *l = accept_token(TK_T_LPAR);
    if (l) {
        exp = accept_expression();
        if (exp) {
            sb_ast *r = accept_token(TK_T_RPAR);
            if (r) {
                delete r;
                sb_ast *ast = new sb_ast_primary_expression(exp);
                ast->begin_tk_pos = l->begin_tk_pos;
                ast->end_tk_pos = r->begin_tk_pos;
                sb_log::debug(ast->info());
                return ast;
            }
            delete exp;
        }
        delete l;
    }
    return NULL;
}

sb_ast *sb_parser::accept_literal() {
    sb_ast *tk = accept_token(TK_T_NUMBER);
    if (tk) {
        sb_ast *ast = new sb_ast_literal(tk);
        ast->begin_tk_pos = tk->begin_tk_pos;
        ast->end_tk_pos = token_pos - 1;
        sb_log::debug(ast->info());
        return ast;
    }
    return NULL;
}
