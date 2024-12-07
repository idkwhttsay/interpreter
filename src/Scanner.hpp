#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <sstream>
#include <map>

class Scanner {
private:
    std::string source;
    std::map<std::string, std::string> keywords;
    void initKeywords();
    int current;
    int line;
    int exit_code;
public:
    Scanner(const std::string& str);
    ~Scanner();

    int tokenize();
    void add_token(char c);

    bool peek(char c);
    char peek_next();
    bool is_at_end();
    void advance();
    void skip_comment();

    static bool is_alpha(char c);
    static bool is_digit(char c);
    static bool is_alpha_numeric(char c);

    void string();
    void number();
    void identifier();

    static void print_token(std::string type, std::string name, std::string literal);
};

#endif // SCANNER_H