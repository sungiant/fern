#pragma once

#include "conf.h"

namespace fern {

    // Instruction format.
    //  8: OP   [0..255]
    //  8: X    [0..255]
    //  8: Y    [0..255]
    //  8: Z    [0..255]
    // 32: VAL  [0..4,294,967,295]

    //
    // R(x) = Register x
    // K(x) = Constant x
    //
    enum opco {
        HALT    = 0x00,
        LOAD    = 0x01, // R(X) = K(VAL)
        MOVE    = 0x02, // R(X) = R(Y)

        ADD     = 0x03, // R(X) = R(Y) + R(Z)
        SUB     = 0x04, // R(X) = R(Y) - R(Z)
        MUL     = 0x05, // R(X) = R(Y) * R(Z)

        PRINT   = 0x06, // num_regs = K(X);
                        // if (num_regs == 0) PRINT R(Y) as UINT32
                        // else for (int i = 0; i < num_regs; ++ i) { PRINT R(Y + i) as UTF8 }
    };

    struct instr {
        // Defines the operation that the virtual machine should perform.
        opco op = opco::HALT;

        // Defines the indices of register operands that the virtual machine should use when performing the operation.
        u_int8_t x, y, z = 0;

        // Defines the data operand that the virtual machine should use when performing the operation.
        u_int32_t val = 0xDEADBEEF;

        static instr decode (u_int64_t i);
    };
}