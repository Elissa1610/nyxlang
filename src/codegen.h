#ifndef INSANELANG_CODEGEN_H
#define INSANELANG_CODEGEN_H

#include <memory>
#include <string>
#include "ast.h"

namespace InsaneLang {

class CodeGenerator {
public:
    CodeGenerator() = default;
    // Generate a textual intermediate representation from a module
    std::string generate(std::unique_ptr<ModuleDecl> module);
};

} // namespace InsaneLang

#endif // INSANELANG_CODEGEN_H
