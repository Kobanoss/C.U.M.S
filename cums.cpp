#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

#include <any>
#include <cinttypes>

#include <sstream>
#include <cstring>

#include <map>
#include <vector>


#include <fstream>

#include "src/dStack.cpp"
#include "src/syscalls.c"

#define MEM_LIMIT 640000


uint16_t iota_counter = 0;


uint16_t iota(bool reset = false) {
    if (reset)
        iota_counter = 0;
    return iota_counter++;

}

typedef struct position {
    int64_t row = 0;
    int64_t col = 0;
} position;

enum Operations {OP_PUSH_INT, OP_PUSH_CHAR, OP_PUSH_STR, OP_DROP, OP_DUP, OP_DUPM, OP_OVER, OP_OVERM, OP_SWAP, COMMENT, OP_PLUS, OP_MINUS, OP_MUL, OP_DIV,
    OP_MOD, OP_DEBUG_INT, OP_DEBUG_CHAR, OP_MEM, OP_MEM_PUSH, OP_MEM_LOAD, OP_SYSCALL, OP_EQUAL,
    OP_NOT_EQUAL, OP_GREATER, OP_LOWER, OP_IF, OP_DO, OP_ELSE, OP_END, OP_WHILE, OP_AND_BIT,
    OP_OR_BIT, OP_BITSHIFT_LEFT, OP_BITSHIFT_RIGHT, OP_MACRO, OP_MACRO_END, OP_MACRO_SET_NAME, OP_MACRO_EXPAND, OP_INCLUDE, OP_COUNTER};

enum RunMode {RUN_DEBUG, RUN_TIMER_DEBUG ,RUN_RELEASE};

// [stack, 0x12345578] [int64_t , ...] [char, ...]

auto TYPE_KEYWORD = iota(true);
auto TYPE_INTEGER = iota();
auto TYPE_CHAR  = iota();
auto TYPE_STRING = iota();
auto TYPE_MACRO = iota();
auto TYPE_MACRO_EXPAND = iota();

auto TYPE_OTHER = iota();
auto TYPE_ERROR = iota();


typedef struct file_token {
    position pos = {0, 0};
    std::string token = "";
    uint16_t type = 0;
    Operations operation = {};
    std::vector<int64_t> args = {};
    std::vector<char> data = {};
}
        file_token;

std::map<std::string, uint64_t> MACRO_MAP = {};

std::map<std::string, Operations> KEYWORD_MAP = {
        {"drop",OP_DROP},
        {"dup", OP_DUP},
        {"dupm",OP_DUPM},
        {"over",OP_OVER},
        {"overm", OP_OVERM},
        {"swap",OP_SWAP},
        {"+", OP_PLUS},
        {"-", OP_MINUS},
        {"*", OP_MUL},
        {"//", OP_DIV},
        {"%", OP_MOD},
        {"iDebug", OP_DEBUG_INT},
        {"cDebug", OP_DEBUG_CHAR},
        {"mem", OP_MEM},
        {"mPush", OP_MEM_PUSH},
        {"mLoad", OP_MEM_LOAD},
        {"syscall", OP_SYSCALL},
        {"==", OP_EQUAL},
        {"!=", OP_NOT_EQUAL},
        {">", OP_GREATER},
        {"<", OP_LOWER},
        {"if", OP_IF},
        {":", OP_DO},
        {"else", OP_ELSE},
        {"end", OP_END},
        {"while", OP_WHILE},
        {"<<", OP_BITSHIFT_LEFT},
        {">>", OP_BITSHIFT_RIGHT},
        {"&", OP_AND_BIT},
        {"|", OP_OR_BIT},
        {"macro", OP_MACRO},
        {"macroEnd", OP_MACRO_END},
        {"include", OP_INCLUDE}
};




// ERRORS BLOCK
void callImplementationError(uint16_t counter) {
    if (OP_COUNTER != counter) {
        std::cerr << "NOT ALL OPERATIONS IMPLEMENTED\n";
        std::cerr << "PROGRAM TERMINATED!           \n";
        exit(EXIT_FAILURE);
    }
}

void callUsageError(const std::string &error_msg) {
    std::cout << "Usage:                                                        \n"
                 "    PROGRAM CALL  - ./cums.exe FILENAME RUN_MODE BUILD_MODE   \n"
                 "                                                              \n"
                 "    FILENAME      - filename.cums                             \n"
                 "                                                              \n"
                 "    RUN_MODE      - d (DEBUG)                                 \n"
                 "                  - r (RELEASE)                               \n"
                 "                                                              \n"
                 "    BUILD_MODE    - sim (simulation in C++)                   \n"
                 "                  - com (self compilation)                    \n";

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

std::vector<file_token> dataFromFile(const std::string &file_path) {
    std::vector<file_token> file_data;
    std::string str;
    int64_t row = 0;

    std::ifstream file(file_path);
    if (file.is_open()) {
        while (std::getline(file, str)) {
            std::string token = "";
            int16_t is_string = 0;
            for (int col = 0; col < str.size(); col++) {
                char char_ = str[col];

                if (char_ == '\"') {
                    is_string = 1 - is_string;
                    token += char_;
                }
                else if ((char_ == ' ' || char_ == '\n') && is_string == 0) {
                    if (token != "")
                        file_data.push_back({{row, col - (int64_t)token.size() + 1}, token});
                    token = "";
                }

                else if (col == str.size() - 1) {
                    token += char_;
                    file_data.push_back({{row, col - (int64_t)token.size() + 1}, token});
                }
                else
                    token += char_;

            }
            row++;
        }
    }

    file.close();

    return file_data;
}

uint16_t getTokenType(const std::string &token) {
    try {
        if (token[0] == '\'' && token[token.length()-1] == '\'')
            return TYPE_CHAR;
        else if (token[0] == '\"'&& token[token.length()-1] == '\"')
            return TYPE_STRING;
        else if (KEYWORD_MAP.find(token) != KEYWORD_MAP.end())
            return TYPE_KEYWORD;
        else if (MACRO_MAP.find(token) != MACRO_MAP.end())
            return TYPE_MACRO_EXPAND;
        else if (std::stoi(token) || token == "0")
            return TYPE_INTEGER;
        else
            return TYPE_OTHER;
    }
    catch (std::invalid_argument const& ex) {
        return TYPE_ERROR;
    }
}

// LEXER BLOCK
file_token lexToken(bool status_macro, file_token token, uint64_t index) {
    callImplementationError(39);

    token.type = getTokenType(token.token);

    if (token.type == TYPE_KEYWORD) {
        token.operation = KEYWORD_MAP[token.token];
    }
    else if (token.type == TYPE_INTEGER) {
        token.operation = OP_PUSH_INT;
        token.args.push_back(std::stoi(token.token));
    }
    else if (token.type == TYPE_CHAR) {
        token.operation = OP_PUSH_CHAR;
        token.args.push_back((int64_t)(token.token.c_str()[1]));
    }
    else if (token.type == TYPE_STRING) {
        token.operation = OP_PUSH_STR;
        token.data.reserve(token.token.length()-2);
        for (uint64_t i = 1; i < token.token.size() - 1; i++) {
            token.data.push_back(token.token.c_str()[i]);
        }
    }
    else if (status_macro && token.type == TYPE_ERROR) {
        token.operation = OP_MACRO_SET_NAME;
        MACRO_MAP[token.token] = index;
    }
    else if (token.type == TYPE_MACRO_EXPAND) {
        token.operation = OP_MACRO_EXPAND;
    }

    else {
        std::cerr   << token.pos.row << "(" << token.pos.row + 1 << ") : " << token.pos.col << "(" << token.pos.col + 1 << ") : " << token.token << " : "
                    << token.type << " : " << "UNKNOWN OPERATOR (NO TOKEN TYPE)" << std::endl;
        exit(EXIT_FAILURE);
    }

    return token;
}


// BLOCKS CROSS-REFERENCE BLOCK

void cross_reference_blocks (std::vector<file_token> &program) {
    callImplementationError(39);
    // NOT ALL OPERATIONS NEED TO BE IMPLEMENTED HERE.
    // ONLY OPERATIONS WHICH MODIFY CODE BLOCKS


    dStack cross_reference_macro_stack = dStack();
    dStack cross_reference_stack = dStack();
    dStack cross_reference_types_stack = dStack();
    dStack cross_reference_while_stack = dStack();

    int64_t type, start_block_point, start_macro_point;

    for (int64_t i = 0; i < program.size(); i++) {
        file_token token = program[i];

        switch (token.operation) {

            case OP_MACRO:
                cross_reference_macro_stack.push(i + 1);
                break;

            case OP_MACRO_EXPAND:
                program[i].args.push_back(MACRO_MAP[program[i].token]);
                break;

            case OP_MACRO_END:
                program[cross_reference_macro_stack.pop()].args.push_back(i);
                break;

            case OP_IF:
                cross_reference_types_stack.push(OP_IF);
                break;

            case OP_DO:
                cross_reference_stack.push(i);
                break;

            case OP_ELSE:
                cross_reference_types_stack.push(OP_ELSE);
                program[cross_reference_stack.pop()].args.push_back(i-1);
                cross_reference_stack.push(i);
                break;

            case OP_WHILE:
                cross_reference_types_stack.push(OP_WHILE);
                cross_reference_while_stack.push(i);
                break;

            case OP_END:
                start_block_point = cross_reference_stack.pop();
                type = cross_reference_types_stack.pop();


                if (type == OP_WHILE) {
                    program[i].args.push_back(cross_reference_while_stack.pop());
                    program[start_block_point].args.push_back(i);
                }
                else
                    program[start_block_point].args.push_back(i-1);

                if (type == OP_ELSE) {
                    start_block_point = cross_reference_stack.pop();
                    type = cross_reference_types_stack.pop();
                }
                break;
        }
    }

    cross_reference_macro_stack.~dStack();
    cross_reference_stack.~dStack();
    cross_reference_types_stack.~dStack();

}

std::vector<file_token> lexFile(const std::vector<file_token>& old_program, bool include = false, uint64_t include_offset = 0) {
    callImplementationError(39);

    std::vector<file_token> program;
    bool macro_status = false;
    uint64_t offset = 0;
    for (uint64_t i = 0; i < old_program.size(); i++) {
        auto token = old_program[i];
        auto data = lexToken(macro_status, token, i + include_offset);
        program.push_back(data);

        if (data.operation == OP_MACRO)
            macro_status = true;
        if (data.operation == OP_MACRO_END)
            macro_status = false;

        if (data.operation == OP_INCLUDE) {
            auto include_target = old_program[i - 1].token;
            std::erase(include_target, '\"');
            if (!checkFileType(include_target)) {
                std::cerr   << token.pos.row << "(" << token.pos.row + 1 << ") : "
                            << token.pos.col << "(" << token.pos.col + 1 << ") : "
                            << token.token + " " + include_target << " : " << "WRONG INCLUDE" << std::endl;
                exit(EXIT_FAILURE);
            }
            std::vector<file_token> include_data = lexFile(dataFromFile(include_target), true, i + 1);
            offset = include_data.size();
            for (auto & j : include_data) {
                program.push_back(j);
            }


        }
    }
    if (!include) {
        cross_reference_blocks(program);
    }

    return program;
}





// SIMULATION BLOCK
uint8_t simulation(std::vector<file_token> &program, RunMode run_mode) {
    callImplementationError(39);

    clock_t start_point = clock();

    char *ptr_mem = (char *) malloc(sizeof(char) * MEM_LIMIT);
    char *ptr_data = (char *) malloc(sizeof(char) * MEM_LIMIT);
    int64_t data_start_point = 0;

    dStack stack;
    uint8_t next_statement = 0;
    std::vector<bool> macro_status = {false};
    std::vector<uint64_t> macro_point = {};

    if (run_mode == RUN_DEBUG) {
        for (uint64_t i = 0; i < program.size(); i++) {
            std::cout << i << " : " << program[i].token << " : " << program[i].operation;
            auto op = program[i].operation;
            if (op == OP_PUSH_CHAR  || op == OP_PUSH_INT
                || op == OP_MACRO_SET_NAME
                || op ==  OP_MACRO_EXPAND) {
                std::cout << " : " << program[i].args[0];
            }
            std::cout << std::endl;
        }
    }

    for (uint64_t i = 0; i < program.size(); i++) {
        file_token token = program[i];
        clock_t loop_start_point = 0;
        switch (run_mode) {
            case RUN_DEBUG:
                usleep(100000);
                std::cout << token.token << std::endl;
                break;
            case RUN_TIMER_DEBUG:
                std::cout << token.token << std::endl;
                loop_start_point = clock();
                break;
        }


        int64_t a, b, load_address, push_address, push_value, len, statement;
        int64_t ops[7];
        std::vector<int64_t> tmp_vec = {};

        switch (token.operation) {


            case OP_PUSH_INT:
                stack.push(token.args[0]);
                break;

            case OP_PUSH_CHAR:
                stack.push(token.args[0]);
                break;

            case OP_PUSH_STR:
                for (int64_t j = 0; j < token.data.size(); j++)
                    ptr_data[j + data_start_point] = token.data[j];

                stack.push(((int64_t) ptr_data) + data_start_point);

                data_start_point += token.data.size();
                ptr_data[data_start_point] = '\0';
                data_start_point += 1;
                break;

            case OP_DROP:
                stack.pop();
                break;

            case OP_DUP:
                stack.push(stack.peek());
                break;

            case OP_DUPM:
                len = stack.pop();
                for (int64_t j = 0; j < len; j++) {
                    tmp_vec.push_back(stack.pop());
                }
                for (int64_t j = 0; j < tmp_vec.size(); j++) {
                    stack.push(tmp_vec[tmp_vec.size() - j - 1]);
                }
                for (int64_t j = 0; j < tmp_vec.size(); j++) {
                    stack.push(tmp_vec[tmp_vec.size() - j - 1]);
                }
                tmp_vec.erase(tmp_vec.begin(), tmp_vec.end());
                break;

            case OP_OVER:
                a = stack.pop();
                b = stack.pop();
                stack.push(b);
                stack.push(a);
                stack.push(b);
                break;
            case OP_OVERM:
                len = stack.pop();

                for (int64_t j = 0; j < len + 1; j++) {
                    a = stack.pop();
                    tmp_vec.push_back(a);
                }
                for (int64_t j = 0; j < tmp_vec.size(); j++) {
                    a = tmp_vec[tmp_vec.size() - 1 - j];
                    stack.push(a);
                }
                stack.push(tmp_vec[tmp_vec.size() - 1]);
                tmp_vec.erase(tmp_vec.begin(), tmp_vec.end());
                break;

            case OP_SWAP:
                a = stack.pop();
                b = stack.pop();
                stack.push(a);
                stack.push(b);
                break;

            case OP_PLUS:
                a = stack.pop();
                b = stack.pop();
                stack.push(b + a);
                break;

            case OP_MINUS:
                a = stack.pop();
                b = stack.pop();
                stack.push(b - a);
                break;

            case OP_MUL:
                a = stack.pop();
                b = stack.pop();
                stack.push(b * a);
                break;

            case OP_DIV:
                a = stack.pop();
                b = stack.pop();
                stack.push(b / a);
                break;

            case OP_MOD:
                a = stack.pop();
                b = stack.pop();
                stack.push(b % a);
                break;

            case OP_DEBUG_INT:
                std::cout << (int64_t) stack.pop();
                break;

            case OP_DEBUG_CHAR:
                std::cout << (char) stack.pop();
                break;

            case OP_MEM:
                stack.push((int64_t) ptr_mem);
                break;

            case OP_MEM_PUSH:
                push_value = stack.pop();
                push_address = (int64_t)stack.pop();
                *(char*)(push_address) = (char)push_value;
                break;

            case OP_MEM_LOAD:
                load_address = stack.pop();
                stack.push((int64_t)*(char*)load_address);
                break;

            case OP_SYSCALL:
                len = stack.pop();


                for (int64_t j = 0; j < len; j++)
                    ops[len-j-1] = stack.pop();

                syscall_all(ops, len);

                break;

            case OP_EQUAL:
                a = stack.pop();
                b = stack.pop();
                stack.push(b == a ? 1 : 0);
                break;

            case OP_NOT_EQUAL:
                a = stack.pop();
                b = stack.pop();
                stack.push(b != a ? 1 : 0);
                break;

            case OP_GREATER:
                a = stack.pop();
                b = stack.pop();
                stack.push(b > a ? 1: 0);
                break;

            case OP_LOWER:
                a = stack.pop();
                b = stack.pop();
                stack.push(b < a ? 1: 0);
                break;

            case OP_IF:
                break;

            case OP_DO:
                statement = stack.pop();
                next_statement = 1 - statement;
                switch (statement) {
                    case 0:
                        i = token.args[0];
                        break;
                    case 1:
                        break;

                    default:
                        std::cerr << token.pos.row << "(" << token.pos.row + 1 << ") : " << token.pos.col << "(" << token.pos.col + 1 << ") : " << token.token << " : "
                                  << "BAD STATEMENT" << std::endl;
                        free(ptr_mem);
                        free(ptr_data);
                        stack.~dStack();
                        exit(EXIT_FAILURE);
                        break;
                }
                break;

            case OP_ELSE:
                stack.push(next_statement);
                break;

            case OP_WHILE:
                break;

            case OP_END:
                if (token.args.size() != 0)
                    i = token.args[0];
                break;

            case OP_BITSHIFT_LEFT:
                a = stack.pop();
                b = stack.pop();
                stack.push((int64_t)(b << a));
                break;

            case OP_BITSHIFT_RIGHT:
                a = stack.pop();
                b = stack.pop();
                stack.push((int64_t)(b >> a));
                break;

            case OP_AND_BIT:
                a = stack.pop();
                b = stack.pop();
                stack.push((int64_t)(b & a));
                break;

            case OP_OR_BIT:
                a = stack.pop();
                b = stack.pop();
                stack.push((int64_t)(b | a));
                break;

            case OP_MACRO:
                break;

            case OP_MACRO_END:
                if (macro_status.back()) {
                    macro_status.pop_back();
                    i = macro_point.back();
                    macro_point.pop_back();
                }
                break;

            case OP_MACRO_SET_NAME:
                i = token.args[0];
                break;

            case OP_MACRO_EXPAND:
                macro_point.push_back(i);
                i = token.args[0];
                macro_status.push_back(true);
                break;

            case OP_INCLUDE:
                stack.pop();
                break;

            default:
                std::cerr << token.pos.row << "(" << token.pos.row + 1 << ") : " << token.pos.col << "(" << token.pos.col + 1 << ") : " << token.token << " : "
                          << "UNKNOWN OPERATOR AFTER LEX" << std::endl;
                free(ptr_mem);
                free(ptr_data);
                stack.~dStack();
                exit(EXIT_FAILURE);
                break;
        }
        if (run_mode == RUN_TIMER_DEBUG)
            printf("Simulation operator time: %ld ns\n", (clock() - loop_start_point) / (CLOCKS_PER_SEC/1000000));
    }

    free(ptr_mem);
    free(ptr_data);
    stack.~dStack();
    printf("Simulation time: %ld ns\n", (clock() - start_point) / (CLOCKS_PER_SEC/1000000));
    return 0;
}


uint8_t compilation(const std::vector<file_token> &program, uint16_t run_mode) {
    callImplementationError(32);
    std::cerr << ">> COMPILATION NOT IMPLEMENTED YET" << std::endl;
    exit(EXIT_FAILURE);
    return 0;
}

int main(const int32_t argc, const char **argv) {
    int return_code = 1;
    RunMode run_mode = {};

    if (argc != 4) {
        callUsageError("BAD ARGUMENTS ERROR!");
    }
    if (!checkFileType(argv[1])) {
        callUsageError("FILENAME ERROR!");
    }
    std::vector<file_token> program = lexFile(dataFromFile(argv[1]));

    if (strcmp(argv[2], "d") == 0)
        run_mode = RUN_DEBUG;
    else if (strcmp(argv[2], "dt") == 0)
        run_mode = RUN_TIMER_DEBUG;
    else if (strcmp(argv[2], "r") == 0)
        run_mode = RUN_RELEASE;
    else
        callUsageError("RUN_MODE ERROR!");

    if (strcmp(argv[3], "sim") == 0)
        return_code = simulation(program, run_mode);
    else if (strcmp(argv[3], "com") == 0)
        return_code = compilation(program, run_mode);
    else
        callUsageError("BUILD_MODE ERROR!");



    return return_code;
}
