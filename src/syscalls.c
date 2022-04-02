#include <unistd.h>



void syscall_all(int64_t* ops, size_t len) {
    switch (len) {
        case 0: 
            return;
        case 1:
            syscall(ops[0]);
            break;
        case 2:
            syscall(ops[0], ops[1]);
            break;
        case 3:
            syscall(ops[0], ops[1], ops[2]);
            break;
        case 4:
            syscall(ops[0], ops[1], ops[2], ops[3]);
            break;
        case 5:
            syscall(ops[0], ops[1], ops[2], ops[3], ops[4]);
            break;
        case 6:
            syscall(ops[0], ops[1], ops[2], ops[3], ops[4], ops[5]);
            break;
    }
}