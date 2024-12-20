#include "Scanner.hpp"
#include "Parser.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string read_file_contents(const std::string& filename);

int main(const int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    if (const std::string command = argv[1]; command == "tokenize") {
        const std::string file_contents = read_file_contents(argv[2]);

        Scanner scanner(file_contents, true);
        return scanner.tokenize();
    } else if(command == "parse") {
        const std::string file_contents = read_file_contents(argv[2]);

        Scanner scanner(file_contents, false);
        scanner.tokenize();

        Parser parser(scanner.get_tokens());
        return parser.parse();
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }
}

std::string read_file_contents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
