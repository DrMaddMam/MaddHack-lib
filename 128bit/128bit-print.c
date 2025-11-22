#ifndef BIT_PRINT_C
#define BIT_PRINT_C
#include "../madd-types.h"

/// @brief prints U128 to buffer
/// @param n 
/// @param buf 
/// @param bufsize 
/// @return the buffer pointer
U8* print_u128(U128 n, U8* buf, UMin bufsize) {
    U8 i = bufsize-1;
    buf[i] = '\0';
    do {
        buf[--i] = '0' + (n % 10);
        n /= 10;
    } while (n);
    return buf;
}

/// @brief prints I128 to buffer
/// @param n 
/// @param buf 
/// @param bufsize 
/// @return the buffer pointer
U8 print_i128(I128 n, U8* buf, UMin bufsize) {
    if (n < 0) {
        buf[0] = '-';
        return print_u128((U128)(-n), buf+1, bufsize-1);
    } else {
        return print_u128((U128)n, buf, bufsize);
    }
}
#endif // 128BIT_PRINT_C