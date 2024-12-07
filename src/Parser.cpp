#include "Parser.hpp"

#include <utility>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), exit_code(0), current(0), line(1) {}

Parser::~Parser() = default;

bool Parser::is_at_end() {
    return (current >= tokens.size());
}

void Parser::advance() {
    current ++;
}

void Parser::print_token(const Token& token) {
    std::cout << token.name << std::endl;
}

void Parser::parse_token() {
    print_token(tokens[current]);
    advance();
}

int Parser::parse() {
    while(!is_at_end()) {
        parse_token();
    }

    return exit_code;
}