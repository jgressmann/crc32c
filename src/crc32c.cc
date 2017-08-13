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

#include "crc32c.h"
#include "interface.h"
#include <cassert>
#include <cstdlib>

using namespace std;

#ifdef __linux__
extern "C" int __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle);

static int AtExit(void (*func) ()) {
    return __cxa_atexit ((void (*) (void *)) func, NULL, NULL);;
}
#endif

namespace  {

void CrcTeardown();
crcutil_interface::CRC* CrcSetup();
crcutil_interface::CRC*  s_Algorithm = CrcSetup();

void CrcTeardown() {
    if (s_Algorithm) {
        s_Algorithm->Delete();
        s_Algorithm = NULL;
    }
}

const unsigned RollBytes = 0;

crcutil_interface::CRC*
CrcSetup() {
#ifdef __linux__
    AtExit(CrcTeardown);
#else
    atexit(CrcTeardown);
#endif
    return crcutil_interface::CRC::Create(
                0x82F63B78 /* inverted iSCSI poly implemented in i5 and onwards as crc32 */,
                0, 32, true, 0, 0, RollBytes,
                crcutil_interface::CRC::IsSSE42Available(), NULL);
}
} // anon namespace


extern "C"
uint32_t
crc32c_update(uint32_t initial, const void* ptr, size_t bytes) {
    crcutil_interface::UINT64 lo = initial;
    s_Algorithm->Compute(ptr, bytes, &lo);
    return static_cast<uint32_t>(lo);
}
