#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <sstream>

class Scanner {
private:
    std::string source;
    int current;
    int line;
    int exit_code;
public:
    Scanner(const std::string& str);
    int tokenize();
    void add_token(char c);
    bool peek(char c);
    char peek_next();
    bool is_at_end();
    void string();
    void number();
    void print_token(std::string type, std::string name, std::string literal);
    void skip_comment();
    void advance();
    ~Scanner();
};

#endif // SCANNER_H