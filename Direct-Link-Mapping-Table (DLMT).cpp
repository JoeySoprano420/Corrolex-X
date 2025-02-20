#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <stdexcept>

class DLMT {
public:
    DLMT() {
        // Initialize Corrolex-X to Assembly mappings
        populate_mappings();
    }

    // Function to map Corrolex-X code to assembly
    std::string map_to_assembly(const std::string& corrolx_x_code) {
        std::string result = map_basic_syntax(corrolx_x_code);
        
        if (result != corrolx_x_code) {
            return result;  // Direct match found in basic mappings
        }

        // If no direct match, attempt to map expressions or control structures
        return map_advanced_syntax(corrolx_x_code);
    }

private:
    std::unordered_map<std::string, std::string> mappings;

    // Populating basic mappings for Corrolex-X language
    void populate_mappings() {
        // Basic statements
        mappings["func"] = "function PROC";
        mappings["return"] = "ret";
        mappings["print"] = "invoke printf";

        // Data types and operations
        mappings["int"] = "DWORD";
        mappings["float"] = "REAL4";
        mappings["string"] = "BYTE";

        // Logical operations
        mappings["=="] = "cmp";
        mappings["!="] = "cmp";
        mappings[">"] = "cmp";
        mappings["<"] = "cmp";
        mappings[">="] = "cmp";
        mappings["<="] = "cmp";
        mappings["&&"] = "and";
        mappings["||"] = "or";

        // Conditional control
        mappings["if"] = "cmp";
        mappings["else"] = "jmp";

        // Function calls and arguments
        mappings["()"] = "";  // Function call, handled separately
    }

    // Basic syntax mapping: simple replacements of Corrolex-X keywords with assembly
    std::string map_basic_syntax(const std::string& corrolx_x_code) {
        std::string lower_code = to_lower(corrolx_x_code);  // Normalize the case
        
        if (mappings.find(lower_code) != mappings.end()) {
            return mappings[lower_code];
        }

        return corrolx_x_code;  // Return as-is if no mapping found
    }

    // Advanced syntax parsing: Mapping expressions and control structures
    std::string map_advanced_syntax(const std::string& corrolx_x_code) {
        // Handle expression patterns (e.g., variables, operations)
        if (corrolx_x_code.find("==") != std::string::npos || 
            corrolx_x_code.find("!=") != std::string::npos ||
            corrolx_x_code.find(">") != std::string::npos || 
            corrolx_x_code.find("<") != std::string::npos) {
            return map_comparison_expression(corrolx_x_code);
        }

        // Handle function definitions
        if (corrolx_x_code.find("func") != std::string::npos) {
            return map_function_definition(corrolx_x_code);
        }

        // Handle variable assignments
        if (corrolx_x_code.find("=") != std::string::npos) {
            return map_variable_assignment(corrolx_x_code);
        }

        // Handle if-else conditions
        if (corrolx_x_code.find("if") != std::string::npos) {
            return map_if_statement(corrolx_x_code);
        }

        return corrolx_x_code;  // Default return if no special case matches
    }

    // Mapping for comparison expressions (like `x == 5`)
    std::string map_comparison_expression(const std::string& expression) {
        // Simple pattern matching (assumes expression is in the format "var op value")
        std::stringstream ss(expression);
        std::string left, op, right;
        ss >> left >> op >> right;

        // Build assembly comparison based on operator
        std::string assembly_code = "cmp " + left + ", " + right + "\n";
        if (op == "==") {
            assembly_code += "je ";
        } else if (op == "!=") {
            assembly_code += "jne ";
        } else if (op == ">") {
            assembly_code += "jg ";
        } else if (op == "<") {
            assembly_code += "jl ";
        } else if (op == ">=") {
            assembly_code += "jge ";
        } else if (op == "<=") {
            assembly_code += "jle ";
        } else {
            throw std::invalid_argument("Unsupported comparison operator: " + op);
        }

        assembly_code += "LABEL";  // Placeholder for actual jump target

        return assembly_code;
    }

    // Mapping for function definitions
    std::string map_function_definition(const std::string& function_definition) {
        std::stringstream ss(function_definition);
        std::string keyword, function_name;
        ss >> keyword >> function_name;
        
        if (function_name.empty()) {
            throw std::invalid_argument("Function name is missing");
        }

        // Assume standard PROC format for assembly function
        return function_name + " PROC\n";
    }

    // Mapping for variable assignments
    std::string map_variable_assignment(const std::string& assignment) {
        std::stringstream ss(assignment);
        std::string variable, eq, value;
        ss >> variable >> eq >> value;

        if (eq != "=") {
            throw std::invalid_argument("Invalid assignment operator");
        }

        return "mov " + variable + ", " + value;
    }

    // Mapping for if-else statements
    std::string map_if_statement(const std::string& condition) {
        // Example: `if (x == 5) { ... }`
        std::stringstream ss(condition);
        std::string keyword, condition_str;
        ss >> keyword >> condition_str;

        if (condition_str.empty()) {
            throw std::invalid_argument("If condition is missing");
        }

        // Build assembly code to evaluate condition and jump
        std::string assembly_code = "cmp " + condition_str + "\n";
        assembly_code += "je ";
        assembly_code += "LABEL";  // Placeholder for actual jump target

        return assembly_code;
    }

    // Utility function to convert strings to lowercase
    std::string to_lower(const std::string& input) {
        std::string result = input;
        for (char& c : result) {
            c = std::tolower(c);
        }
        return result;
    }
};

int main() {
    DLMT dlmt;

    // Example mappings
    std::vector<std::string> code_snippets = {
        "func main()",
        "return 0",
        "print 'Hello, world!'",
        "x = 5",
        "if (x == 5)",
        "x == 10",
    };

    for (const std::string& snippet : code_snippets) {
        std::cout << "Corrolex-X Code: " << snippet << std::endl;
        std::cout << "Mapped Assembly: " << dlmt.map_to_assembly(snippet) << std::endl << std::endl;
    }

    return 0;
}
