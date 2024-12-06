#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CELLS 30000

void interpret_bf(const char* bf_code) {
    char mem[NUM_CELLS] = {0};
    char* ptr = mem;
    const char* code = bf_code;

    while (*code) {
        switch (*code) {
            case '>':
                ++ptr;
                break;
            case '<':
                --ptr;
                break;
            case '+':
                ++(*ptr);
                break;
            case '-':
                --(*ptr);
                break;
            case '.':
                putchar(*ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                if (*ptr == 0) {
                    int depth = 1;

                    do {
                        code++;

                        if (*code == '[')
                            depth++;
                        else if (*code == ']')
                            depth--;
                    } while (depth && *code);
                }
                break;
            case ']':
                if (*ptr != 0) {
                    int depth = 1;

                    do {
                        code--;

                        if (*code == '[')
                            depth--;
                        else if (*code == ']')
                            depth++;
                    } while (depth && code >= bf_code);

                    code--;
                }
                break;
        }

        code++;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "ERROR: Too few arguments\r\nUsage: %s <brainfuck code>\r\n", argv[0]);
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "ERROR: Too many arguments\r\nUsage: %s <brainfuck code>\r\n", argv[0]);
        return 1;
    }

    interpret_bf(argv[1]);

    return 0;
}
