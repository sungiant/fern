#include "instr.h"

using namespace fern;

instr instr::decode (u_int64_t i) {

    u_int8_t op   = (i & 0xFF00000000000000) >> 56;
    u_int8_t x    = (i & 0x00FF000000000000) >> 48;
    u_int8_t y    = (i & 0x0000FF0000000000) >> 40;
    u_int8_t z    = (i & 0x000000FF00000000) >> 32;
    u_int32_t val = (i & 0x00000000FFFFFFFF);

    instr r;
    r.op = static_cast<opco> (op);
    r.x = x;
    r.y = y;
    r.z = z;
    r.val = val;
    return r;
}