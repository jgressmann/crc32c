crc32c
======

Wraps Google's awesome [crcutil](https://code.google.com/archive/p/crcutil/) 
crc32c (Castagnoli) CRC implementation in a C library with miminal external 
dependencies (libc).

## Usage

Build and install the library. In your source code:

```
#include <crc32c.h>

char buffer[4096];
uint32_t crc = crc32c(buffer, sizeof(buffer); 
```

Link against crc32c.