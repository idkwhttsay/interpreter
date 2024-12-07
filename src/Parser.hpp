#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "Token.hpp"

class Parser {
private:
    std::vector<Token> tokens;
    int exit_code;
    int line;
    int current;
public:
    explicit Parser(std::vector<Token> tokens);
    int parse();
    void advance();
    bool is_at_end();

    void parse_token();
    void print_token(const Token& token);

    ~Parser();
};

#endif // PARSER_H