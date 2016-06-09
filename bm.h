#pragma once

#include "conf.h"

namespace fern {
    // binary maths functions
    // http://stackoverflow.com/questions/1149929/how-to-add-two-numbers-without-using-or-or-another-arithmetic-operator#
    class bm {
    public:
        static u_int32_t add (u_int32_t x, u_int32_t y);
        static u_int32_t subtract (u_int32_t x, u_int32_t y);
        static u_int32_t multiply (u_int32_t x, u_int32_t y);
    };
}