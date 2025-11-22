#ifndef BIT_PRINT_H
#define BIT_PRINT_H
#include "../madd-types.h"
U8* print_u128(U128 n, char* out, U8 max_digits);
U8* print_i128(I128 n, char* out, U8 max_digits);
#endif // BIT_PRINT_H