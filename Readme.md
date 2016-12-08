crc32c
======

Wicked fast crc32c (Castagnoli) CRC implementation for AMD / Intel 
compatible cpus supporting the SSE4.2 instruction set.

A reasonably fast fallback implementation is used for all other cpu types.

## Usage

Build and install the library. In your source code:

```
#include <crc32c.h>

char buffer[4096];
uint32_t crc = crc32c(buffer, sizeof(buffer); 
```

Link against crc32c.
