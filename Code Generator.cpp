#include <iostream>

class CodeGenerator {
public:
    std::string generate(const ASTNode& node) {
        if (node.type == "FUNC_DECLARATION") {
            return "func " + node.value + ":\n\t; Assembly code for function\n";
        }
        return "";
    }
};
