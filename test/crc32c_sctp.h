#ifndef CRC32CXX_H
#define CRC32CXX_H

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

uint32_t crc32c_sctp(const void* buffer, size_t bytes);

#ifdef __cplusplus
}
#endif
#endif // CRC32CXX_H

