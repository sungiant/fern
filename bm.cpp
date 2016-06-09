#include "bm.h"

using namespace fern;

u_int32_t bm::add (u_int32_t x, u_int32_t y) {
    u_int32_t carry = 0;
    u_int32_t result = 0;
    for (int i = 0; i < sizeof (u_int32_t) * 8; ++i) {
        u_int32_t a = (x >> i) & 1;
        u_int32_t b = (y >> i) & 1;
        result |= ((a ^ b) ^ carry) << i;
        carry = (a & b) | (b & carry) | (carry & a);
    }
    return result;
}

u_int32_t bm::subtract (u_int32_t x, u_int32_t y) {
    return add (x, add (~y, 1));
}

u_int32_t bm::multiply (u_int32_t x, u_int32_t y) {
    u_int32_t result = 0;
    while (y > 0) {
        if (!(y & 1)) {
            x = x << 1;
            y = y >> 1;
        } else {
            result = add (result, x);
            y = add (y, u_int32_t_max);
        }
    }
    return result;
}