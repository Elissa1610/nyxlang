#ifndef INSANELANG_LEXER_H
#define INSANELANG_LEXER_H

#include <string>
#include <vector>
#include "token.h"

namespace InsaneLang {

class Lexer {
public:
    explicit Lexer(const std::string &source);

    // Get the next token and advance.
    Token nextToken();

    // Peek at the current token without consuming it.
    Token peekToken();

private:
    std::string source;
    size_t index;
    size_t line;
    size_t column;
    Token currentToken;

    bool isAtEnd() const;
    char peekChar(size_t offset = 0) const;
    char advance();
    void skipWhitespaceAndComments();

    Token makeToken(TokenType type, const std::string &lexeme);

    Token identifier();
    Token number();
    Token stringLiteral();

    static bool isAlpha(char c);
    static bool isDigit(char c);
};

} // namespace InsaneLang

#endif // INSANELANG_LEXER_H
