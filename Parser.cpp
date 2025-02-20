#include <iostream>
#include <string>
#include <vector>

struct ASTNode {
    std::string type;
    std::string value;
    std::vector<ASTNode> children;
};

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

    ASTNode parse() {
        return statement();
    }

private:
    const std::vector<Token>& tokens;
    size_t pos;

    ASTNode statement() {
        Token current = tokens[pos];
        if (current.type == TokenType::KEYWORD && current.value == "func") {
            return function_declaration();
        } else {
            throw std::runtime_error("Syntax error: unexpected token.");
        }
    }

    ASTNode function_declaration() {
        consume(TokenType::KEYWORD, "func");
        Token name = consume(TokenType::IDENTIFIER);
        consume(TokenType::PUNCTUATION, "(");
        consume(TokenType::PUNCTUATION, ")");
        consume(TokenType::PUNCTUATION, "{");
        consume(TokenType::PUNCTUATION, "}");
        
        ASTNode funcNode = {"FUNC_DECLARATION", name.value};
        return funcNode;
    }

    Token consume(TokenType type, const std::string& value = "") {
        Token token = tokens[pos];
        if (token.type == type && (value.empty() || token.value == value)) {
            pos++;
            return token;
        }
        throw std::runtime_error("Unexpected token.");
    }
};
