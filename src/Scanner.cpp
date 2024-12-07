#include "Scanner.hpp"

void Scanner::initKeywords() {
    if (keywords.empty()) {
        keywords["and"] = "AND";
        keywords["class"] = "CLASS";
        keywords["else"] = "ELSE";
        keywords["false"] = "FALSE";
        keywords["for"] = "FOR";
        keywords["fun"] = "FUN";
        keywords["if"] = "IF";
        keywords["nil"] = "NIL";
        keywords["or"] = "OR";
        keywords["print"] = "PRINT";
        keywords["return"] = "RETURN";
        keywords["super"] = "SUPER";
        keywords["this"] = "THIS";
        keywords["true"] = "TRUE";
        keywords["var"] = "VAR";
        keywords["while"] = "WHILE";
    }
}

Scanner::Scanner(const std::string& str)
    : source(str), current(0), line(1), exit_code(0) {
        initKeywords();
    }

void Scanner::advance() {
    current ++;
}

int Scanner::tokenize() {
    while(!is_at_end()) {
        add_token(source[this->current]);
    }

    std::cout << "EOF  null" << std::endl;
    return this->exit_code;
}

bool Scanner::is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::is_digit(char c) {
    return (c >= '0' && c <= '9');
}

bool Scanner::is_alpha_numeric(char c) {
    return is_alpha(c) || is_digit(c);
}

void Scanner::skip_comment() {
    while(!is_at_end() && source[current] != '\n') {
        advance();
    }

    this->line ++;
    advance();
}

bool Scanner::peek(char c) {
    return (this->current+1 < source.size() && source[this->current+1] == c);
}

bool Scanner::is_at_end() {
    return !(current < source.size());
}

void Scanner::print_token(std::string type, std::string name, std::string literal) {
    std::cout << type << ' ' << name << ' ' << literal << std::endl;
}

char Scanner::peek_next() {
    if (current + 1 >= source.size()) return '\0';
    return source[current + 1];
}

void Scanner::number() {
    std::string value = "";
    while(!is_at_end() && isdigit(source[current])) {
        value.push_back(source[current]);
        advance();
    }

    if(source[current] == '.' && isdigit(peek_next())) {
        value.push_back(source[current]);
        advance();

        while(isdigit(source[current])) {
            value.push_back(source[current]);
            advance();
        }

        double dvalue = std::stod(value);
        std::ostringstream oss;
        oss << dvalue;
        std::string result = oss.str();

        if(result.find('.') == std::string::npos) {
            result.push_back('.');
            result.push_back('0');
        }

        print_token("NUMBER", value, result);
    } else {
        std::string dvalue = value;
        dvalue.push_back('.');
        dvalue.push_back('0');
        print_token("NUMBER", value, dvalue);
    }
}

void Scanner::string() {
    advance();
    std::string value = "";
    while(!is_at_end() && source[current] != '"') {
        if(source[current] == '\n') line ++;
        value.push_back(source[current]);
        advance();
    }

    if(is_at_end()) {
        std::cerr << "[line " << line << "] Error: Unterminated string." << std::endl;
        this->exit_code = 65;
        return;
    }

    advance();
    print_token("STRING", "\"" + value + "\"", value);
}

void Scanner::identifier() {
    std::string value = "";
    while(!is_at_end() && is_alpha_numeric(source[current])) {
        value.push_back(source[current]);
        advance();
    }

    if(keywords.find(value) != keywords.end()) {
        print_token(keywords[value], value, "null");
        return;
    }

    print_token("IDENTIFIER", value, "null");
}

void Scanner::add_token(char c) {
    switch (c) {
        case ' ':
        case '\r':
        case '\t': advance(); break;
        case '\n': this->line ++; advance(); break;
        case '"': string(); break;
        case '(': print_token("LEFT_PAREN", "(", "null"); advance(); break;
        case ')': print_token("RIGHT_PAREN", ")", "null"); advance(); break;
        case '{': print_token("LEFT_BRACE", "{", "null"); advance(); break;
        case '}': print_token("RIGHT_BRACE", "}", "null"); advance(); break;
        case '*': print_token("STAR", "*", "null"); advance(); break;
        case ',': print_token("COMMA", ",", "null"); advance(); break;
        case '+': print_token("PLUS", "+", "null"); advance(); break;
        case '.': print_token("DOT", ".", "null"); advance(); break;
        case '-': print_token("MINUS", "-", "null"); advance(); break;
        case ';': print_token("SEMICOLON", ";", "null"); advance(); break;
        case '/':
            if(peek('/')) {
                skip_comment();
            } else {
                print_token("SLASH", "/", "null"); advance();
            } break;
        case '=':
            if(peek('=')) {
                print_token("EQUAL_EQUAL", "==", "null"); advance(); advance();
            } else {
                print_token("EQUAL", "=", "null"); advance();
            } break;
        case '!':
            if(peek('=')) {
                print_token("BANG_EQUAL", "!=", "null"); advance(); advance();
            } else {
                print_token("BANG", "!", "null"); advance();
            } break;
        case '<':
            if(peek('=')) {
                print_token("LESS_EQUAL", "<=", "null"); advance(); advance();
            } else {
                print_token("LESS", "<", "null"); advance();
            } break;
        case '>':
            if(peek('=')) {
                print_token("GREATER_EQUAL", ">=", "null"); advance(); advance();
            } else {
                print_token("GREATER", ">", "null"); advance();
            } break;
        default:
            if(is_digit(c)) {
                number();
            } else if(is_alpha(c)) {
                identifier();
            } else {
                std::cerr << "[line " << line << "] Error: Unexpected character: " << c << std::endl; advance(); exit_code = 65;
            }
    }
}

Scanner::~Scanner() {}