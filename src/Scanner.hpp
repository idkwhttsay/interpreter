#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "Token.hpp"

class Scanner {
private:
    std::string source;
    std::vector<Token> tokens;
    std::map<std::string, std::string> keywords;
    void initKeywords();
    int current;
    int line;
    int exit_code;
    bool to_print;
public:
    Scanner(std::string  str, bool to_print);
    ~Scanner();

    int tokenize();
    void add_token(char c);

    std::vector<Token> get_tokens();

    bool peek(char c) const;
    char peek_next() const;
    bool is_at_end() const;
    void advance();
    void skip_comment();

    static bool is_alpha(char c);
    static bool is_digit(char c);
    static bool is_alpha_numeric(char c);

    void string();
    void number();
    void identifier();

    void print_token(const std::string& type, const std::string &name, const std::string& literal);
};

#endif // SCANNER_H