#include <iostream>
#include <unordered_map>

class SemanticAnalyzer {
public:
    void analyze(const ASTNode& node) {
        if (node.type == "FUNC_DECLARATION") {
            if (symbol_table.find(node.value) != symbol_table.end()) {
                throw std::runtime_error("Function already defined.");
            }
            symbol_table[node.value] = "function";
        }

        for (const auto& child : node.children) {
            analyze(child);
        }
    }

private:
    std::unordered_map<std::string, std::string> symbol_table;
};
