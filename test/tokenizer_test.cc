#include "test.h"
#include "tokenizer.h"

TEST_CASE("tokenizer") {
    std::istringstream in("print 123;");
    sb_tokenizer tokenizer(in);
    REQUIRE(tokenizer.next().type == TK_T_K_PRINT);
    REQUIRE(tokenizer.next().type == TK_T_NUMBER);
    REQUIRE(tokenizer.next().type == TK_T_SEMI);
}
