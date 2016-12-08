#include <cstdio>
#include <cstring>
#include "crc32c.h"

using namespace std;

int main() {
    uint32_t x = 42;
    uint32_t result = crc32c(&x, sizeof(x));

    printf("CRC32C of uint32_t(42): %s\n");

    return 0;
}
