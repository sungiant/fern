#pragma once

#include "conf.h"

namespace fern {

    struct instr;

    // virtual machine
    class vm {
    public:

        // execute result
        enum er { EXIT = -1, CONTINUE = 0, FATAL = 1 };

        vm ();
        ~vm ();

        er execute (instr* z);

    private:

        static constexpr int num_registers = 256;
        u_int32_t * registers;
    };
}

