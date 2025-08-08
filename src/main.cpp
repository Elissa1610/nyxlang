#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "lexer.h"
#include "parser.h"

using namespace InsaneLang;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: insanelang <source file>" << std::endl;
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Failed to open file " << argv[1] << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    std::vector<Token> tokens;
    while (true) {
        Token tok = lexer.nextToken();
        tokens.push_back(tok);
        if (tok.type == TokenType::EndOfFile) {
            break;
        }
    }

    for (const auto& tok : tokens) {
        std::cout << "Token: type=" << static_cast<int>(tok.type)
                  << " lexeme='" << tok.lexeme
                  << "' line=" << tok.location.line
                  << " col=" << tok.location.column
                  << std::endl;
    }

    Parser parser(tokens);
    try {
        auto module = parser.parse();
        std::cout << "Parsing completed." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Parser error: " << ex.what() << std::endl;
    }
    return 0;
}
