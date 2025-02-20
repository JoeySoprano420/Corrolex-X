#include <iostream>
#include <string>
#include <vector>
#include <regex>

enum class TokenType {
    KEYWORD, IDENTIFIER, NUMBER, STRING, OPERATOR, PUNCTUATION, WHITESPACE
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    static const std::regex keyword_regex;
    static const std::regex identifier_regex;
    static const std::regex number_regex;
    static const std::regex string_regex;
    static const std::regex operator_regex;
    static const std::regex punctuation_regex;
    static const std::regex whitespace_regex;

    std::vector<Token> lex(const std::string& source_code) {
        std::vector<Token> tokens;
        size_t pos = 0;

        while (pos < source_code.length()) {
            std::smatch match;
            
            if (std::regex_search(source_code.begin() + pos, source_code.end(), match, keyword_regex)) {
                tokens.push_back({TokenType::KEYWORD, match.str()});
            } else if (std::regex_search(source_code.begin() + pos, source_code.end(), match, identifier_regex)) {
                tokens.push_back({TokenType::IDENTIFIER, match.str()});
            } else if (std::regex_search(source_code.begin() + pos, source_code.end(), match, number_regex)) {
                tokens.push_back({TokenType::NUMBER, match.str()});
            } else if (std::regex_search(source_code.begin() + pos, source_code.end(), match, string_regex)) {
                tokens.push_back({TokenType::STRING, match.str()});
            } else if (std::regex_search(source_code.begin() + pos, source_code.end(), match, operator_regex)) {
                tokens.push_back({TokenType::OPERATOR, match.str()});
            } else if (std::regex_search(source_code.begin() + pos, source_code.end(), match, punctuation_regex)) {
                tokens.push_back({TokenType::PUNCTUATION, match.str()});
            } else if (std::regex_search(source_code.begin() + pos, source_code.end(), match, whitespace_regex)) {
                // Ignore whitespace
            } else {
                throw std::runtime_error("Unexpected character encountered");
            }

            pos += match.length();
        }

        return tokens;
    }
};

// Token Regex Patterns (simplified for example)
const std::regex Lexer::keyword_regex("\\b(?:int|float|struct|return|if|else|while|func|print|class)\\b");
const std::regex Lexer::identifier_regex("[a-zA-Z_][a-zA-Z_0-9]*");
const std::regex Lexer::number_regex("\\d+");
const std::regex Lexer::string_regex("\"(\\.|[^\"])*\"");
const std::regex Lexer::operator_regex("[+\\-*/=<>!&|]");
const std::regex Lexer::punctuation_regex("[(),;{}]");
const std::regex Lexer::whitespace_regex("\\s+");
