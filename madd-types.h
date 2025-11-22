#ifndef MADDTYPES_H
#define MADDTYPES_H
#define __BITSMAX__ (__SIZEOF_POINTER__ * 8)
#define __BYTESMAX__ (__SIZEOF_POINTER__)
typedef void U0;
typedef void I0;
#define false 0
#define true 1
typedef unsigned char UMin;
#define UMin_MAX 0xFF
#ifdef __clang__
typedef UMin Bool;
#else
typedef _Bool Bool;
#endif
typedef Bool U1;
typedef Bool I1;
typedef unsigned char U8;
#define U8_MAX 0xFF
typedef signed char I8;
#define I8_MIN (-128)
#define I8_MAX 127
typedef unsigned short U16;
#define U16_MAX 0xFFFF
typedef signed short I16;
#define I16_MIN (-32768)
#define I16_MAX 32767
typedef unsigned int U32;
#define U32_MAX 0xFFFFFFFF
typedef signed int I32;
#define I32_MIN (-2147483648)
#define I32_MAX 2147483647
typedef unsigned long long U64;
#define U64_MAX 0xFFFFFFFFFFFFFFFFULL
typedef signed long long I64;
#define I64_MIN (-9223372036854775807LL-1)
#define I64_MAX 9223372036854775807LL
// Biggest Int types for x64 systems
typedef unsigned __int128 U128;
#define U128_MAX (((unsigned __int128)0xFFFFFFFFFFFFFFFFULL << 64) | (unsigned __int128)0xFFFFFFFFFFFFFFFFULL)
typedef __int128 I128;
#define I128_MIN ((I128)((U128)1 << 127))  // signed -2^127
#define I128_MAX ((I128)(((U128)1 << 127) - 1))
// Max Int for x86 and x64
#if __SIZEOF_POINTER__ == 16
typedef unsigned __int128 UMax;
typedef __int128 IMax;
#elif __SIZEOF_POINTER__ == 8
typedef unsigned long long UMax;
typedef signed long long IMax;
#define UMaxFORMAT "%llu"
#define IMaxFORMAT "%lld"
#elif __SIZEOF_POINTER__ == 4
typedef unsigned long UMax;
typedef signed long IMax;
#define UMaxFORMAT "%lu"
#define IMaxFORMAT "%ld"
#elif __SIZEOF_POINTER__ == 2
typedef unsigned short UMax;
typedef signed short IMax;
#define UMaxFORMAT "%hu"
#define IMaxFORMAT "%hd"
#elif __SIZEOF_POINTER__ == 1
typedef unsigned char UMax;
typedef signed char IMax;
#define UMaxFORMAT "%hhu"
#define IMaxFORMAT "%hhd"
#else
#error "Unsupported pointer size"
#endif
typedef float F32;
typedef double F64;
#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)
typedef long double F80;
#if defined(__GNUC__) || defined(__clang__)
typedef __float128 F128;
#endif
#endif
#endif // MADDTYPES_H