#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <cinttypes>

#include <sstream>
#include <cstring>

#include <vector>
#include <tuple>

#include <fstream>

#include "dStack.h"
#include "syscalls.c"

#define TUPLE_str_int_ std::tuple<std::string, int64_t>

uint16_t iota_counter = 0;


uint16_t iota(bool reset = false) {
    if (reset)
        iota_counter = 0;
    return iota_counter++;

}


auto OP_PUSH = iota(true);
auto OP_POP = iota();
auto OP_DUP = iota();
auto COMMENT = iota();

auto OP_PLUS = iota();
auto OP_MINUS = iota();
auto OP_MUL = iota();
auto OP_DIV = iota();
auto OP_MOD = iota();


auto OP_OUT_INT = iota();
auto OP_OUT_CHAR = iota();


auto OP_MEM = iota();
auto OP_MEM_PUSH = iota();
auto OP_MEM_LOAD = iota();

auto OP_EQUAL = iota();
auto OP_GREATER = iota();
auto OP_LOWER = iota();

auto OP_COUNTER = iota();


// OPERATIONS BLOCK
TUPLE_str_int_ comment() {
    return std::make_tuple("COMMENT", 0);
}

TUPLE_str_int_ push(int64_t x) {
    return std::make_tuple("OP_PUSH", x);
}

TUPLE_str_int_ pop() {
    return std::make_tuple("OP_POP", 0);
}

TUPLE_str_int_ dup() {
    return std::make_tuple("OP_DUP", 0);
}


TUPLE_str_int_ outi() {
    return std::make_tuple("OP_OUT_INT", 0);
}

TUPLE_str_int_ outc() {
    return std::make_tuple("OP_OUT_CHAR", 0);
}


TUPLE_str_int_ plus() {
    return std::make_tuple("OP_PLUS", 0);
}

TUPLE_str_int_ minus() {
    return std::make_tuple("OP_MINUS", 0);
}

TUPLE_str_int_ mul() {
    return std::make_tuple("OP_MUL", 0);
}

TUPLE_str_int_ div() {
    return std::make_tuple("OP_DIV", 0);
}

TUPLE_str_int_ mod() {
    return std::make_tuple("OP_MOD", 0);
}


TUPLE_str_int_ mem() {
    return std::make_tuple("OP_MEM", 0);
}

TUPLE_str_int_ memPush() {
    return std::make_tuple("OP_MEM_PUSH", 0);
}

TUPLE_str_int_ memLoad() {
    return std::make_tuple("OP_MEM_LOAD", 0);
}


TUPLE_str_int_ equal() {
    return std::make_tuple("OP_EQUAL", 0);
}

TUPLE_str_int_ greater() {
    return std::make_tuple("OP_GREATER", 0);
}

TUPLE_str_int_ lower() {
    return std::make_tuple("OP_LOWER", 0);
}

// ERRORS BLOCK
void callImplementationError(uint16_t counter) {
    if (OP_COUNTER != counter) {
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

// BLOCKS CROSS-REFERENCE BLOCK

std::vector<TUPLE_str_int_> cross_reference_blocks (std::vector<TUPLE_str_int_> program) {
    callImplementationError(17);
    // NOT ALL OPERATIONS NEED TO BE IMPLEMENTED HERE.
    // ONLY OPERATIONS WHICH MODIFY CODE BLOCKS
    dStack cross_reference_stack = dStack();
    for (int32_t i = 0; i < program.size(); i++) {
        std::string op = std::get<0>(program[i]);

        if (op == "OP_IF") {

        }

        if (op == "OP_ELSE") {

        }

        if (op == "OP_WHILE") {

        }

        if (op == "OP_END") {

        }
    }

    return program;
}


// LEXER BLOCK
TUPLE_str_int_ lexLine(const std::vector<std::string> &tokens, int64_t row, int64_t col) {
    callImplementationError(17);
    TUPLE_str_int_ res;
    std::string op = tokens[0];

    if (op == "//")
        res = comment();


    else if (op == "push") {
        try {
            res = push(std::stoll(tokens[1]));
        }
        catch (const std::logic_error &e) {
            res = push((int64_t) (tokens[1].c_str())[0]);
        }
    }
    else if (op == "pop")
        res = pop();
    else if (op == "dup")
        res = dup();


    else if (op == "outi")
        res = outi();
    else if (op == "outc")
        res = outc();


    else if (op == "plus")
        res = plus();
    else if (op == "minus")
        res = minus();
    else if (op == "mul")
        res = mul();
    else if (op == "div")
        res = div();
    else if (op == "mod")
        res = mod();


    else if (op == "mem")
        res = mem();
    else if (op == "memPush")
        res = memPush();
    else if (op == "memLoad")
        res = memLoad();


    else if (op == "equal")
        res = equal();
    else if (op == "greater")
        res = greater();
    else if (op == "lower")
        res = lower();


    else {
        std::cerr << row << "(" << row + 1 << ") : " << col << "(" << col + 1 << ") : " << op << " : "
                  << "UNKNOWN OPERATOR" << std::endl;
        exit(EXIT_FAILURE);
    }

    return res;
}

std::vector<TUPLE_str_int_ > lexFile(const std::vector<std::tuple<int64_t, int64_t, std::string>> &data) {
    std::vector<TUPLE_str_int_ > program;
    for (auto &&line_info: data) {
        std::string token;
        std::vector<std::string> tokens;

        std::stringstream str(std::get<2>(line_info));

        while (std::getline(str, token, ' '))
            tokens.push_back(token);

        program.push_back(lexLine(tokens, std::get<0>(line_info), std::get<1>(line_info)));
    }

    program = cross_reference_blocks(program);

    return program;
}



// RUN MODE BLOCK
uint8_t simulation(const std::vector<TUPLE_str_int_ > &data) {
    callImplementationError(17);
    char *ptr = (char *) malloc(1);
    dStack stack;
    int i = 0;
    for (auto &op: data) {
        // COMMENT
        if (std::get<0>(op) == "COMMENT") {
            continue;
        }
            // OP_PUSH
        else if (std::get<0>(op) == "OP_PUSH") {
            stack.push(std::get<1>(op));
        }
            // OP_POP
        else if (std::get<0>(op) == "OP_POP") {
            stack.pop();
        }
            // OP_DUP
        else if (std::get<0>(op) == "OP_DUP") {
            stack.push(stack.peek());
        }


            // OP_PLUS
        else if (std::get<0>(op) == "OP_PLUS") {
            stack.push(stack.pop() + stack.pop());
        }
            // OP_MINUS
        else if (std::get<0>(op) == "OP_MINUS") {
            stack.push(-stack.pop() + stack.pop());
        }
            // OP_MUL
        else if (std::get<0>(op) == "OP_MUL") {
            stack.push(stack.pop() * stack.pop());
        }
            // OP_DIV
        else if (std::get<0>(op) == "OP_DIV") {
            auto tmp = stack.pop();
            stack.push(stack.pop() / tmp);
        }
            // OP_MOD
        else if (std::get<0>(op) == "OP_MOD") {
            stack.push(stack.pop() % stack.pop());
        }


            // OP_OUT_INT
        else if (std::get<0>(op) == "OP_OUT_INT") {
            std::cout << stack.pop();
        }
            // OP_OUT_CHAR
        else if (std::get<0>(op) == "OP_OUT_CHAR") {
            std::cout << (char) stack.pop();
        }


            // OP_MEM
        else if (std::get<0>(op) == "OP_MEM") {
            stack.push((int64_t) ptr);
        }

            // OP_MEM_PUSH
        else if (std::get<0>(op) == "OP_MEM_PUSH") {
            int64_t push_value = stack.pop();
            int64_t push_pos = stack.pop();
            int64_t push_address = stack.pop();
            *((char *) push_address + push_pos) = (char) push_value;
        }

            // OP_MEM_LOAD
        else if (std::get<0>(op) == "OP_MEM_LOAD") {
            int64_t load_pos = stack.pop();
            int64_t load_address = stack.pop();
            stack.push(*((char *) load_address + load_pos));
        }


            // OP_EQUAL
        else if (std::get<0>(op) == "OP_EQUAL") {
            stack.push(stack.pop() == stack.pop() ? 1 : 0);
        }
            // OP_GREATER
        else if (std::get<0>(op) == "OP_GREATER") {
            stack.push(stack.pop() < stack.pop() ? 1: 0);
        }
            // OP_LOWER
        else if (std::get<0>(op) == "OP_LOWER") {
            stack.push(stack.pop() > stack.pop() ? 1: 0);
        }
        else {
            std::cerr << "Unknown OPERATOR after lex";
            exit(EXIT_FAILURE);
        }

        // std::cout << std::get<1>(op) << " :: " << i << " :: " << std::get<0>(op) << '\n';
        i++;
    }

    return 0;
}


uint8_t compilation(const std::vector<std::tuple<std::string, int64_t>> &data) {
    callImplementationError(17);
    std::cerr << ">> COMPILATION NOT IMPLEMENTED YET" << std::endl;
    exit(EXIT_FAILURE);
    return 0;
}

int main(const int32_t argc, const char **argv) {
    int return_code = 1;

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
