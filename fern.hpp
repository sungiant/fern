#pragma once

#include <iostream>
#include <limits>

namespace fern {

    // Instruction format.
    //  8: OP   [0..255]
    //  8: X    [0..255]
    //  8: Y    [0..255]
    //  8: Z    [0..255]
    // 32: VAL  [0..4,294,967,295]
    enum opco { // fern op codes
                                        // R(x) = Register x
                                        // K(x) = Constant x
        HALT    = 0x00,
        LOAD    = 0x01,                 // R(X) = K(VAL)
        MOVE    = 0x02,                 // R(X) = R(Y)

        ADD     = 0x03,                 // R(X) = R(Y) + R(Z)
        SUB     = 0x04,                 // R(X) = R(Y) - R(Z)
        MUL     = 0x05,                 // R(X) = R(Y) * R(Z)

        PRINT   = 0x06,                 // num_regs = K(X);
                                        // if (num_regs == 0) PRINT R(Y) as UINT32
                                        // else for (int i = 0; i < num_regs; ++ i) { PRINT R(Y + i) as UTF8 }
    };

    // binary maths - just for fun
    // http://stackoverflow.com/questions/1149929/how-to-add-two-numbers-without-using-or-or-another-arithmetic-operator#
    uint32_t bm_add (uint32_t x, uint32_t y) {
        uint32_t carry = 0;
        uint32_t result = 0;
        for (int i = 0; i < sizeof (uint32_t) * 8; ++i) {
            uint32_t a = (x >> i) & 1;
            uint32_t b = (y >> i) & 1;
            result |= ((a ^ b) ^ carry) << i;
            carry = (a & b) | (b & carry) | (carry & a);
        }
        return result;
    }

    uint32_t bm_subtract (uint32_t x, uint32_t y) {
        return bm_add (x, bm_add (~y, 1));
    }

    uint32_t bm_multiply (uint32_t x, uint32_t y) {
        static const uint32_t max_uint32_t = std::numeric_limits<uint32_t>::max();
        uint32_t result = 0;
        while (y > 0) {
            if (!(y & 1)) {
                x = x << 1;
                y = y >> 1;
            } else {
                result = bm_add (result, x);
                y = bm_add (y, max_uint32_t);
            }
        }
        return result;
    }

    struct instr {
        opco op = opco::HALT;           // Defines the operation that the virtual machine should perform.
        u_int8_t x, y, z  = 0;          // Defines the indices of register operands that the virtual machine should use when performing the operation.
        uint32_t val     = 0xDEADBEEF; // Defines the data operand that the virtual machine should use when performing the operation.

        static instr decode (u_int64_t i) {
            u_int8_t op   = (i & 0xFF00000000000000) >> 56;
            u_int8_t x    = (i & 0x00FF000000000000) >> 48;
            u_int8_t y    = (i & 0x0000FF0000000000) >> 40;
            u_int8_t z    = (i & 0x000000FF00000000) >> 32;
            uint32_t val = (i & 0x00000000FFFFFFFF);
            instr r;
            r.op = static_cast<opco> (op);
            r.x = x;
            r.y = y;
            r.z = z;
            r.val = val;
            return r;
        }
    };

    class vm {
    private:
        static const int num_registers = 64;
        uint32_t* registers;
    public:
        enum er { EXIT = -1, CONTINUE = 0, FATAL = 1 };

        vm () {
            registers = new uint32_t[num_registers];
            for (int i = 0; i < num_registers; ++i) {
                registers[i] = 0;
            }
        };

        ~vm () {
            delete registers;
            registers = nullptr;
        };

        er execute (instr* z) {
            switch (z->op) {
                case opco::LOAD:
                    registers[z->x] = z->val;
                    return er::CONTINUE;

                case opco::MOVE:
                    registers[z->x] = registers[z->y];
                    return er::CONTINUE;

                case opco::ADD:
                    registers[z->x] = bm_add (registers[z->y], registers[z->z]);
                    return er::CONTINUE;

                case opco::SUB:
                    registers[z->x] = bm_subtract (registers[z->y], registers[z->z]);
                    return er::CONTINUE;

                case opco::MUL:
                    registers[z->x] = bm_multiply (registers[z->y], registers[z->z]);
                    return er::CONTINUE;

                case opco::PRINT: {
                    if (z->x == 0) { // print a single uint32
                        std::cout << registers[z->y];
                    }
                    else { // print a range of utf8 characters
                        for (int i = 0; i < z->x; ++i) {
                            std::wcout << (wchar_t) registers[z->y + i];
                        }
                    }
                    return er::CONTINUE;
                }

                case opco::HALT:
                    return er::EXIT;
            }
            return er::FATAL;
        }
    };
}