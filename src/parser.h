#ifndef INSANELANG_PARSER_H
#define INSANELANG_PARSER_H

#include <vector>
#include <memory>
#include "token.h"
#include "ast.h"

namespace InsaneLang {

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);
    ASTNodePtr parse();

private:
    std::vector<Token> tokens;
    size_t index;

    bool isAtEnd() const;
    const Token &peek(int offset = 0) const;
    const Token &advance();
    bool matchKeyword(const std::string &kw);
    bool matchSymbol(const std::string &sym);

    ASTNodePtr parseModule();
    ASTNodePtr parseDeclaration();
    std::unique_ptr<FunctionDecl> parseFunction();
    std::unique_ptr<VarDeclStmt> parseVarDecl();
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseCall();
    std::unique_ptr<Expression> parsePrimary();
};

} // namespace InsaneLang

#endif // INSANELANG_PARSER_H
