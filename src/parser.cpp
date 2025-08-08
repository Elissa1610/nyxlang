#include "parser.h"
#include <stdexcept>

namespace InsaneLang {

Parser::Parser(std::vector<Token> tokens)
    : tokens(std::move(tokens)), current(0) {}

bool Parser::isAtEnd() const {
    return current >= tokens.size() || tokens[current].type == TokenType::EndOfFile;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::advance() {
    if (!isAtEnd()) {
        ++current;
    }
    return tokens[current - 1];
}

bool Parser::matchKeyword(const std::string& keyword) {
    if (!isAtEnd() && tokens[current].type == TokenType::Keyword && tokens[current].lexeme == keyword) {
        advance();
        return true;
    }
    return false;
}

bool Parser::matchSymbol(const std::string& symbol) {
    if (!isAtEnd() && tokens[current].type == TokenType::Symbol && tokens[current].lexeme == symbol) {
        advance();
        return true;
    }
    return false;
}

ASTNodePtr Parser::parse() {
    // For now, return an empty module declaration.
    return std::make_unique<ModuleDecl>("",
                                        std::vector<std::unique_ptr<FunctionDecl>>{},
                                        SourceLocation{1, 1});
}

ASTNodePtr Parser::parseModule() {
    // Delegate to parse() which returns an empty module.
    return parse();
}

ASTNodePtr Parser::parseDeclaration() {
    throw std::runtime_error("Parse declaration not implemented yet");
}

std::unique_ptr<FunctionDecl> Parser::parseFunction() {
    throw std::runtime_error("Parse function not implemented yet");
}

std::unique_ptr<VarDeclStmt> Parser::parseVarDecl() {
    throw std::runtime_error("Parse variable declaration not implemented yet");
}

std::unique_ptr<Statement> Parser::parseStatement() {
    throw std::runtime_error("Parse statement not implemented yet");
}

std::unique_ptr<Expression> Parser::parseExpression(int /*precedence*/) {
    throw std::runtime_error("Parse expression not implemented yet");
}

std::unique_ptr<Expression> Parser::parseCall(std::unique_ptr<Expression> /*callee*/) {
    throw std::runtime_error("Parse call not implemented yet");
}

std::unique_ptr<Expression> Parser::parsePrimary() {
    throw std::runtime_error("Parse primary not implemented yet");
}

} // namespace InsaneLang
