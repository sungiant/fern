# fern

[![Build Status](https://travis-ci.org/sungiant/fern.png?branch=master)](https://travis-ci.org/sungiant/fern)
![License](https://img.shields.io/github/license/sungiant/fern)

A really simple toy register based virtual machine.

An example program:

```
    uint64_t program[] = {
        0x0100000000000048, // load utf8 'H' into r0
        0x0101000000000065, // load utf8 'e' into r1
        0x010200000000006C, // load utf8 'l' into r2
        0x010300000000006C, // load utf8 'l' into r3
        0x010400000000006F, // load utf8 'o' into r4
        0x0105000000000020, // load utf8 ' ' into r5
        0x0106000000000077, // load utf8 'w' into r6
        0x010700000000006F, // load utf8 'o' into r7
        0x0108000000000072, // load utf8 'r' into r8
        0x010900000000006C, // load utf8 'l' into r9
        0x010A000000000064, // load utf8 'd' into r10
        0x010B000000000021, // load utf8 '!' into r11
        0x010C00000000000A, // load utf8 '\n' into r12
        0x060D0000FFFFFFFF, // print 13 registers from r0
        0x010000000000000F, // load # 15 into r0
        0x02010000FFFFFFFF, // copy r0 to r1
        0x03020001FFFFFFFF, // add r0 to r1 and put the result into r2
        0x05030201FFFFFFFF, // multiply r2 by r1 and put the result into r3
        0x04000300FFFFFFFF, // subtract r0 from r3 and put the result into r0
        0x06000000FFFFFFFF, // print r0
        0x06010C00FFFFFFFF, // print 13 '\n'
        0x06000100FFFFFFFF, // print r1
        0x06010C00FFFFFFFF, // print 13 '\n'
        0x06000200FFFFFFFF, // print r2
        0x06010C00FFFFFFFF, // print 13 '\n'
        0x06000300FFFFFFFF, // print r3
        0x06010C00FFFFFFFF, // print 13 '\n'
        0x00000000FFFFFFFF, // exit
    };
```

## Usage

To run the demo: `g++ -std=c++11 main.cpp -o demo`
