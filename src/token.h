#ifndef INSANELANG_TOKEN_H
#define INSANELANG_TOKEN_H

#include <string>

namespace InsaneLang {

enum class TokenType {
    Identifier,
    Number,
    String,
    Keyword,
    Symbol,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string lexeme;
    size_t line;

    Token(TokenType t, const std::string& lex, size_t ln)
        : type(t), lexeme(lex), line(ln) {}
};

} // namespace InsaneLang

#endif
