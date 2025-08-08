#ifndef INSANELANG_AST_H
#define INSANELANG_AST_H

#include <string>
#include <vector>
#include <memory>

namespace InsaneLang {

struct SourceLocation {
    size_t line;
    size_t column;
};

class ASTNode {
public:
    enum class Kind {
        Module,
        Function,
        VarDecl,
        Identifier,
        NumberLiteral,
        StringLiteral,
        BinaryExpr,
        CallExpr,
        Block,
        ReturnStmt,
        ExpressionStmt
    };
    explicit ASTNode(Kind k) : kind(k) {}
    virtual ~ASTNode() = default;
    Kind kind;
    SourceLocation loc;
};

using ASTNodePtr = std::unique_ptr<ASTNode>;

class Expression : public ASTNode {
public:
    explicit Expression(Kind k) : ASTNode(k) {}
};

class Statement : public ASTNode {
public:
    explicit Statement(Kind k) : ASTNode(k) {}
};

class IdentifierExpr : public Expression {
public:
    std::string name;
    explicit IdentifierExpr(const std::string &n) : Expression(Kind::Identifier), name(n) {}
};

class NumberLiteralExpr : public Expression {
public:
    std::string value;
    explicit NumberLiteralExpr(const std::string &v) : Expression(Kind::NumberLiteral), value(v) {}
};

class StringLiteralExpr : public Expression {
public:
    std::string value;
    explicit StringLiteralExpr(const std::string &v) : Expression(Kind::StringLiteral), value(v) {}
};

class BinaryExpr : public Expression {
public:
    std::string op;
    ASTNodePtr left;
    ASTNodePtr right;
    BinaryExpr(const std::string &oper, ASTNodePtr lhs, ASTNodePtr rhs)
        : Expression(Kind::BinaryExpr), op(oper), left(std::move(lhs)), right(std::move(rhs)) {}
};

class CallExpr : public Expression {
public:
    ASTNodePtr callee;
    std::vector<ASTNodePtr> args;
    CallExpr(ASTNodePtr c, std::vector<ASTNodePtr> arguments)
        : Expression(Kind::CallExpr), callee(std::move(c)), args(std::move(arguments)) {}
};

class VarDeclStmt : public Statement {
public:
    std::string name;
    std::string typeName;
    ASTNodePtr initializer;
    VarDeclStmt(const std::string &n, const std::string &t, ASTNodePtr init)
        : Statement(Kind::VarDecl), name(n), typeName(t), initializer(std::move(init)) {}
};

class ReturnStmt : public Statement {
public:
    ASTNodePtr value;
    explicit ReturnStmt(ASTNodePtr val)
        : Statement(Kind::ReturnStmt), value(std::move(val)) {}
};

class ExpressionStmt : public Statement {
public:
    ASTNodePtr expr;
    explicit ExpressionStmt(ASTNodePtr e)
        : Statement(Kind::ExpressionStmt), expr(std::move(e)) {}
};

class BlockStmt : public Statement {
public:
    std::vector<ASTNodePtr> statements;
    BlockStmt() : Statement(Kind::Block) {}
};

class Parameter {
public:
    std::string name;
    std::string typeName;
    Parameter(const std::string &n, const std::string &t) : name(n), typeName(t) {}
};

class FunctionDecl : public ASTNode {
public:
    std::string name;
    std::vector<Parameter> params;
    std::string returnType;
    std::unique_ptr<BlockStmt> body;
    explicit FunctionDecl(const std::string &n)
        : ASTNode(Kind::Function), name(n) {}
};

class ModuleDecl : public ASTNode {
public:
    std::string name;
    std::vector<ASTNodePtr> members;
    explicit ModuleDecl(const std::string &n)
        : ASTNode(Kind::Module), name(n) {}
};

} // namespace InsaneLang

#endif // INSANELANG_AST_H
