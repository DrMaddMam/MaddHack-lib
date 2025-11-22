#ifndef BIT_PRINT_C
#define BIT_PRINT_C
#include <stdio.h>
#include "../madd-types.h"
inline U0 print_u128(U128 n) {
    char buf[50];
    U8 i = sizeof(buf)-1;
    buf[i] = '\0';
    do {
        buf[--i] = '0' + (n % 10);
        n /= 10;
    } while (n);
    puts(&buf[i]);
}
inline U0 print_i128(I128 n) {
    if (n < 0) {
        putchar('-');
        print_u128((U128)(-n));
    } else {
        print_u128((U128)n);
    }
}
#endif // 128BIT_PRINT_C