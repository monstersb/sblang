#include "test.h"
#include "tokenizer.h"

using std::istringstream;

TEST_CASE("tokenizer") {
    SECTION("token type") {
        istringstream *in = new istringstream(
                "if (a == abc && _b01 > Ab01_ || a + b >= 1) {"
                "   print \"test\";"
                "}"
        );
        sb_tokenizer *tokenizer = new sb_tokenizer(*in);
        REQUIRE(tokenizer->next().type == TK_T_K_IF);
        REQUIRE(tokenizer->next().type == TK_T_LPAR);
        REQUIRE(tokenizer->next().type == TK_T_ID);
        REQUIRE(tokenizer->next().type == TK_T_EQ);
        REQUIRE(tokenizer->next().type == TK_T_ID);
        REQUIRE(tokenizer->next().type == TK_T_L_AND);
        REQUIRE(tokenizer->next().type == TK_T_ID);
        REQUIRE(tokenizer->next().type == TK_T_GT);
        REQUIRE(tokenizer->next().type == TK_T_ID);
        REQUIRE(tokenizer->next().type == TK_T_L_OR);
        REQUIRE(tokenizer->next().type == TK_T_ID);
        REQUIRE(tokenizer->next().type == TK_T_ADD);
        REQUIRE(tokenizer->next().type == TK_T_ID);
        REQUIRE(tokenizer->next().type == TK_T_GTE);
        REQUIRE(tokenizer->next().type == TK_T_NUMBER);
        REQUIRE(tokenizer->next().type == TK_T_RPAR);
        REQUIRE(tokenizer->next().type == TK_T_LBRACE);
        REQUIRE(tokenizer->next().type == TK_T_K_PRINT);
        REQUIRE(tokenizer->next().type == TK_T_STRING);
        REQUIRE(tokenizer->next().type == TK_T_SEMI);
        REQUIRE(tokenizer->next().type == TK_T_RBRACE);
        REQUIRE(tokenizer->next().type == TK_T_EOF);
        delete in;
        delete tokenizer;

        in = new istringstream("test");
        tokenizer = new sb_tokenizer(*in);
        sb_token tk = tokenizer->next();
        REQUIRE(tk.type == TK_T_ID);
        REQUIRE(tk.str == "test");
        REQUIRE(tk.line == 1);
        REQUIRE(tk.column == 1);
        delete in;
        delete tokenizer;

        in = new istringstream("  \"test\"");
        tokenizer = new sb_tokenizer(*in);
        tk = tokenizer->next();
        REQUIRE(tk.type == TK_T_STRING);
        REQUIRE(tk.str == "\"test\"");
        REQUIRE(tk.line == 1);
        REQUIRE(tk.column == 3);
        delete in;
        delete tokenizer;
 
        in = new istringstream("\n\n 123456789 ");
        tokenizer = new sb_tokenizer(*in);
        tk = tokenizer->next();
        REQUIRE(tk.type == TK_T_NUMBER);
        REQUIRE(tk.str == "123456789");
        REQUIRE(tk.line == 3);
        REQUIRE(tk.column == 2);
        delete in;
        delete tokenizer;
 
        in = new istringstream("\n\n    123456789 ");
        tokenizer = new sb_tokenizer(*in);
        tk = tokenizer->next();
        REQUIRE(tk.type == TK_T_NUMBER);
        REQUIRE(tk.str == "123456789");
        REQUIRE(tk.line == 3);
        REQUIRE(tk.column == 5);
        delete in;
 
        in = new istringstream("\r\n print ");
        tokenizer = new sb_tokenizer(*in);
        tk = tokenizer->next();
        REQUIRE(tk.type == TK_T_K_PRINT);
        REQUIRE(tk.str == "print");
        REQUIRE(tk.line == 2);
        REQUIRE(tk.column == 2);
        delete in;
 
        in = new istringstream("\r\n\t  \r\rwhile");
        tokenizer = new sb_tokenizer(*in);
        tk = tokenizer->next();
        REQUIRE(tk.type == TK_T_K_WHILE);
        REQUIRE(tk.str == "while");
        REQUIRE(tk.line == 4);
        REQUIRE(tk.column == 1);
        delete in;

        in = new istringstream("\r\n\t  \r\r");
        tokenizer = new sb_tokenizer(*in);
        tk = tokenizer->next();
        REQUIRE(tk.type == TK_T_EOF);
        REQUIRE(tk.str == "");
        REQUIRE(tk.line == 4);
        REQUIRE(tk.column == 0);
        delete in;

        in = new istringstream("while (1)");
        tokenizer = new sb_tokenizer(*in);
        tokenizer->tokenize();
        REQUIRE((*tokenizer)[0].type == TK_T_K_WHILE);
        REQUIRE((*tokenizer)[0].str == "while");
        REQUIRE((*tokenizer)[1].type == TK_T_LPAR);
        REQUIRE((*tokenizer)[1].str == "(");
        REQUIRE((*tokenizer)[2].type == TK_T_NUMBER);
        REQUIRE((*tokenizer)[2].str == "1");
        REQUIRE((*tokenizer)[3].type == TK_T_RPAR);
        REQUIRE((*tokenizer)[3].str == ")");
        REQUIRE((*tokenizer)[4].type == TK_T_EOF);
        REQUIRE((*tokenizer)[4].str == "");
        delete in;
    }

    SECTION("invalid token") {
        istringstream *in = new istringstream("hello @test");
        sb_tokenizer *tokenizer = new sb_tokenizer(*in);
        REQUIRE(tokenizer->next().type == TK_T_ID);
        REQUIRE(tokenizer->next().type == TK_T_INVALID);
        delete in;
        delete tokenizer;

        in = new istringstream("$");
        tokenizer = new sb_tokenizer(*in);
        REQUIRE(tokenizer->next().type == TK_T_INVALID);
        delete in;
        delete tokenizer;
    }
}
