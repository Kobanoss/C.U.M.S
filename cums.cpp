#include <iostream>
#include <cinttypes>
#include <vector>
#include <tuple>
#include <map>
#include <fstream>
#include <sstream>
#include "stack.h"

#define TUPLE_str_int_ std::tuple<std::string, int64_t>

uint16_t iota_counter = 0;
std::map<std::string, uint16_t> OP_MAP;

uint16_t iota(bool reset = false) {
    if (reset)
        iota_counter = 0;
    return iota_counter++;

}


// OPERATIONS BLOCK
TUPLE_str_int_ init(int64_t x) {
    return std::make_tuple("OP_INIT", x);
}

TUPLE_str_int_ push(int64_t x) {
    return std::make_tuple("OP_PUSH", x);
}

TUPLE_str_int_ pop() {
    return std::make_tuple("OP_POP", 0);
}

TUPLE_str_int_ plus() {
    return std::make_tuple("OP_PLUS", 0);
}

TUPLE_str_int_ print() {
    return std::make_tuple("OP_PRINT", 0);
}


// FILE OPERATIONS BLOCK
bool checkFileType(const std::string &file_path) {
    if (file_path[0] == '/')
        return false;
    return file_path.size() - file_path.rfind(".cums") == 5;
}

std::vector<std::tuple<int64_t, int64_t, std::string>> dataFromFile(const std::string &file_path) {
    std::vector<std::tuple<int64_t, int64_t, std::string>> file_data;
    std::string str;
    int64_t row = 0, col = 0;

    std::ifstream file(file_path);
    if (file.is_open()) {
        while (std::getline(file, str)) {
            // SKIP IF STRING IS EMPTY
            if (!str.empty())
                file_data.emplace_back(std::make_tuple(row, col, str));
            row++;
        }
    }
    file.close();

    return file_data;
}

// LEXER BLOCK
TUPLE_str_int_ lexLine(const std::vector<std::string> &tokens, int64_t row, int64_t col) {
    TUPLE_str_int_ res;
    std::string op = tokens[0];
    if (op == "//")
        res == std::make_tuple("", 0);
    else if (op == "push")
        res = push(std::stoi(tokens[1]));
    else if (op == "pop")
        res = pop();
    else if (op == "print")
        res = print();
    else if (op == "init")
        res = init(std::stoi(tokens[1]));
    else if (op == "plus")
        res = plus();
    else {
        std::cerr << row << "(" << row + 1 << ") : " << col << "(" << col + 1 << ") : " << op << " : "
                  << "UNKNOWN OPERATOR" << std::endl;
        exit(EXIT_FAILURE);
    }
    return res;
}

std::vector<std::tuple<std::string, int64_t>>
lexFile(const std::vector<std::tuple<int64_t, int64_t, std::string>> &data) {
    std::vector<std::tuple<std::string, int64_t>> program;
    for (auto &&line_info: data) {
        std::vector<std::string> tokens;
        std::stringstream str(std::get<2>(line_info));
        std::string token;

        while (std::getline(str, token, ' '))
            tokens.push_back(token);
        program.push_back(lexLine(tokens, std::get<0>(line_info), std::get<1>(line_info)));
    }

    return program;
}

// ERRORS BLOCK
void callImplementationError(uint16_t counter) {
    if (OP_MAP["OP_COUNTER"] != counter) {
        std::cerr << "NOT ALL OPERATIONS IMPLEMENTED\n";
        std::cerr << "PROGRAM TERMINATED!           \n";
        exit(EXIT_FAILURE);
    }
}

void callUsageError(const std::string &error_msg) {
    std::cout << "Usage:                                            \n"
                 "    PROGRAM CALL  - ./cums.exe FILENAME RUN_TYPE  \n"
                 "                                                  \n"
                 "    FILENAME      - filename.cums                 \n"
                 "                                                  \n"
                 "    RUN_TYPE      - sim (simulation in C++)       \n"
                 "                  - com (self compilation)        \n";

    std::cerr << "\n"
                 ">> " << error_msg << std::endl;

    exit(EXIT_FAILURE);
}

// RUN MODE BLOCK
uint8_t simulation(const std::vector<std::tuple<std::string, int64_t>> &data) {
    callImplementationError(6);
    Stack stack(1);
    for (auto &op: data) {
        switch (OP_MAP[std::get<0>(op)]) {
            // OP_INIT
            case 0 :
                stack.softResize(std::get<1>(op));
                break;

                // OP_PUSH
            case 1 :
                stack.push(std::get<1>(op));
                break;

                // OP_POP
            case 2 :
                stack.pop();
                break;

                // OP_PLUS
            case 3 :
                stack.push(stack.pop() + stack.pop());
                break;
                // OP_PRINT
            case 4 :
                std::cout << stack.pop() << std::endl;
                break;
            case 5 :
                break;
        };
    }

    return 0;
}


uint8_t compilation(const std::vector<std::tuple<std::string, int64_t>> &data) {
    callImplementationError(6);
    std::cerr << ">> COMPILATION NOT IMPLEMENTED YET" << std::endl;
    exit(EXIT_FAILURE);
    return 0;
}

int main(const int32_t argc, const char **argv) {
    int return_code = 1;

    OP_MAP["OP_INIT"] = iota(true);
    OP_MAP["OP_PUSH"] = iota();
    OP_MAP["OP_POP"] = iota();
    OP_MAP["OP_PLUS"] = iota();
    OP_MAP["OP_PRINT"] = iota();
    OP_MAP["COMMENT"] = iota();
    OP_MAP["OP_COUNTER"] = iota();

    if (argc != 3) {
        callUsageError("BAD ARGUMENTS ERROR!");
    }
    if (!checkFileType(argv[1])) {
        callUsageError("FILENAME ERROR!");
    }
    std::vector<TUPLE_str_int_ > program;
    program = lexFile(dataFromFile(argv[1]));

    if (strcmp(argv[2], "sim") == 0)
        return_code = simulation(program);
    else if (strcmp(argv[2], "com") == 0)
        return_code = compilation(program);
    else
        callUsageError("RUN_TYPE ERROR!");

    return return_code;
}
