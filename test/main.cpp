/* The MIT License (MIT)
 *
 * Copyright (c) 2016 Jean Gressmann <jean@0x42.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */



#include <cstdio>
#include <cstring>
#include <inttypes.h>

#include <crc32c.h>
#include "crc32c_sctp.h"

using namespace std;

int main() {
    printf("Checking single byte values...");
    for (int i = 0; i < 256; ++i) {
        uint8_t value = i;
        uint32_t sctp = crc32c_sctp(&value, sizeof(value));
        uint32_t fast = crc32c(&value, sizeof(value));
        if (sctp != fast) {
            printf("FAIL\n");
            return -1;
        }
    }

    printf("OK\n");

    printf("Checking two byte values...");
    for (int i = 0; i < 256; ++i) {
        uint16_t value = i * (UINT16_C(1) << 8);
        uint32_t sctp = crc32c_sctp(&value, sizeof(value));
        uint32_t fast = crc32c(&value, sizeof(value));
        if (sctp != fast) {
            printf("FAIL\n");
            return -1;
        }
    }

    printf("OK\n");

    printf("Checking four byte values...");
    for (int i = 0; i < 256; ++i) {
        uint32_t value = i * (UINT32_C(1) << 24);
        uint32_t sctp = crc32c_sctp(&value, sizeof(value));
        uint32_t fast = crc32c(&value, sizeof(value));
        if (sctp != fast) {
            printf("FAIL\n");
            return -1;
        }
    }

    printf("OK\n");

    printf("Checking 4K byte values...");
    uint8_t buf[4096];
    for (int i = 0; i < 256; ++i) {
        memset(buf, i, sizeof(buf));
        uint32_t sctp = crc32c_sctp(buf, sizeof(buf));
        uint32_t fast = crc32c(buf, sizeof(buf));
        if (sctp != fast) {
            printf("FAIL\n");
            return -1;
        }
    }

    printf("OK\n");

    return 0;
}
