#include <iostream>
#include <vector>
#include <stdexcept>

class CorrolexXCompiler {
public:
    CorrolexXCompiler() : dlmt(), lexer(), parser(nullptr), semantic_analyzer(), code_generator() {}

    std::string compile(const std::string& source_code) {
        // Step 1: Lexing
        std::vector<Token> tokens = lexer.lex(source_code);

        // Step 2: Parsing
        parser = new Parser(tokens);
        ASTNode ast = parser->parse();

        // Step 3: Semantic Analysis
        semantic_analyzer.analyze(ast);

        // Step 4: Code Generation
        std::string assembly_code = code_generator.generate(ast);

        // Step 5: Linker (final object code generation)
        std::vector<std::string> object_files = {assembly_code};
        Linker linker;
        std::string final_code = linker.link(object_files);

        return final_code;
    }

private:
    DLMT dlmt;
    Lexer lexer;
    Parser* parser;
    SemanticAnalyzer semantic_analyzer;
    CodeGenerator code_generator;
};

int main() {
    std::string source_code = "func add(a, b) { return a + b; }";
    CorrolexXCompiler compiler;

    try {
        std::string result = compiler.compile(source_code);
        std::cout << "Compiled Code:\n" << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error during compilation: " << e.what() << std::endl;
    }

    return 0;
}
