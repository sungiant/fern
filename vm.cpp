#include "vm.h"

#include <iostream>

#include "bm.h"
#include "instr.h"

using namespace std;
using namespace fern;

vm::vm () {
    registers = new u_int32_t[num_registers];
    for (int i = 0; i < num_registers; ++i) {
        registers[i] = 0;
    }
};

vm::~vm () {
    delete registers;
    registers = nullptr;
};

vm::er vm::execute (instr* z) {
    switch (z->op) {
        case opco::LOAD:
            registers[z->x] = z->val;
            return er::CONTINUE;

        case opco::MOVE:
            registers[z->x] = registers[z->y];
            return er::CONTINUE;

        case opco::ADD:
            registers[z->x] = bm::add (registers[z->y], registers[z->z]);
            return er::CONTINUE;

        case opco::SUB:
            registers[z->x] = bm::subtract (registers[z->y], registers[z->z]);
            return er::CONTINUE;

        case opco::MUL:
            registers[z->x] = bm::multiply (registers[z->y], registers[z->z]);
            return er::CONTINUE;

        case opco::PRINT: {
            if (z->x == 0) { // print a single uint32
                cout << registers[z->y];
            }
            else { // print a range of utf8 characters
                for (int i = 0; i < z->x; ++i) {
                    wcout << (wchar_t) registers[z->y + i];
                }
            }
            return er::CONTINUE;
        }

        case opco::HALT:
            return er::EXIT;
    }

    return er::FATAL;
}