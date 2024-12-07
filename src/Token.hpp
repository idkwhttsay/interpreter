#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <utility>

struct Token {
    std::string type;
    std::string name;
    std::string value;

    Token(std::string type, std::string name, std::string value) : type(std::move(type)), name(std::move(name)), value(std::move(value)) {}
};

#endif // TOKEN_H