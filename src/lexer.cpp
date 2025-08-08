#include "lexer.h"
#include <cctype>
#include <stdexcept>

namespace InsaneLang {

Lexer::Lexer(const std::string &src)
    : source(src), index(0), line(1), column(1) {}

bool Lexer::isAtEnd() const {
    return index >= source.size();
}

char Lexer::peekChar(size_t offset) const {
    if (index + offset >= source.size()) return '\0';
    return source[index + offset];
}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    char c = source[index++];
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return c;
}

void Lexer::skipWhitespaceAndComments() {
    while (!isAtEnd()) {
        char c = peekChar();
        if (std::isspace(static_cast<unsigned char>(c))) {
            advance();
        } else if (c == '/' && peekChar(1) == '/') {
            // Skip single-line comment
            advance();
            advance();
            while (!isAtEnd() && peekChar() != '\n') {
                advance();
            }
        } else {
            break;
        }
    }
}

Token Lexer::makeToken(TokenType type, const std::string &lexeme) {
    return Token(type, lexeme, line);
}

bool Lexer::isAlpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

bool Lexer::isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

Token Lexer::identifier() {
    size_t start = index - 1; // include first char already consumed
    while (isAlpha(peekChar()) || isDigit(peekChar())) {
        advance();
    }
    std::string lexeme = source.substr(start, index - start);
    // Keywords
    if (lexeme == "module" || lexeme == "func" || lexeme == "class" || lexeme == "var" ||
        lexeme == "if" || lexeme == "else" || lexeme == "loop" || lexeme == "unsafe" ||
        lexeme == "return" || lexeme == "true" || lexeme == "false") {
        return makeToken(TokenType::Keyword, lexeme);
    }
    return makeToken(TokenType::Identifier, lexeme);
}

Token Lexer::number() {
    size_t start = index - 1;
    while (isDigit(peekChar())) {
        advance();
    }
    if (peekChar() == '.' && isDigit(peekChar(1))) {
        advance(); // consume '.'
        while (isDigit(peekChar())) {
            advance();
        }
    }
    std::string lexeme = source.substr(start, index - start);
    return makeToken(TokenType::Number, lexeme);
}

Token Lexer::stringLiteral() {
    size_t start = index;
    while (!isAtEnd() && peekChar() != '"') {
        if (peekChar() == '\\') {
            advance();
        }
        advance();
    }
    std::string lexeme = source.substr(start, index - start);
    if (peekChar() == '"') {
        advance(); // consume closing quote
    }
    return makeToken(TokenType::String, lexeme);
}

Token Lexer::nextToken() {
    skipWhitespaceAndComments();
    if (isAtEnd()) {
        return makeToken(TokenType::EndOfFile, "");
    }
    char c = advance();
    // Single-character tokens and punctuation
    switch (c) {
        case '(': return makeToken(TokenType::Symbol, "(");
        case ')': return makeToken(TokenType::Symbol, ")");
        case '{': return makeToken(TokenType::Symbol, "{");
        case '}': return makeToken(TokenType::Symbol, "}");
        case ':': return makeToken(TokenType::Symbol, ":");
        case ',': return makeToken(TokenType::Symbol, ",");
        case ';': return makeToken(TokenType::Symbol, ";");
        case '+': return makeToken(TokenType::Symbol, "+");
        case '-': {
            if (peekChar() == '>') {
                advance();
                return makeToken(TokenType::Symbol, "->");
            }
            return makeToken(TokenType::Symbol, "-");
        }
        case '*': return makeToken(TokenType::Symbol, "*");
        case '/': return makeToken(TokenType::Symbol, "/");
        case '=': {
            if (peekChar() == '=') {
                advance();
                return makeToken(TokenType::Symbol, "==");
            }
            return makeToken(TokenType::Symbol, "=");
        }
        case '"': {
            return stringLiteral();
        }
        default:
            if (isDigit(c)) {
                return number();
            }
            if (isAlpha(c)) {
                return identifier();
            }
            // Unknown char; treat as symbol
            return makeToken(TokenType::Symbol, std::string(1, c));
    }
}

Token Lexer::peekToken() {
    size_t savedIndex = index;
    size_t savedLine = line;
    size_t savedColumn = column;
    Token tok = nextToken();
    index = savedIndex;
    line = savedLine;
    column = savedColumn;
    return tok;
}

} // namespace InsaneLang
