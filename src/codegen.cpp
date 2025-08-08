#include "codegen.h"
#include <sstream>

namespace InsaneLang {

std::string CodeGenerator::generate(std::unique_ptr<ModuleDecl> module) {
    std::ostringstream oss;
    oss << "; Module: " << module->name << "\n";
    // List functions in the module
    for (const auto& fn : module->functions) {
        oss << "; Function: " << fn->name << "\n";
    }
    return oss.str();
}

} // namespace InsaneLang
