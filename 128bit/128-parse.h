#ifndef BIT_PARSE_H
#define BIT_PARSE_H

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#ifndef NO_QUADMATH
#include <quadmath.h>
#endif
#include "../madd-types.h"

static inline unsigned digit_val(char c) {
    if (c >= '0' && c <= '9')
        return (unsigned)(c - '0');
    if (c >= 'a' && c <= 'f')
        return (unsigned)(10 + (c - 'a'));
    if (c >= 'A' && c <= 'F')
        return (unsigned)(10 + (c - 'A'));
    return 255u;
}

U128 str_to_u128(const char* s, UMin base) {
    if (!s)
        return 0;

    U128 out = 0;

    while (isspace((unsigned char)*s))
        ++s;

    if (*s == '+')
        ++s;

    if (base == 0) {
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            base = 16;
            s += 2;
        }
        else {
            base = 10;
        }
    }
    else if (base == 16) {
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
            s += 2;
    }
    else if (base != 10) {
        return false;
    }

    U128 acc = 0;
    Bool any = false;

    for (;; ++s) {
        UMax d = digit_val(*s);
        if (d == 255u || d >= (UMax)base)
            break;
        any = true;

        if (acc > (U128_MAX - (U128)d) / (U128)base) {
            return false; // overflow
        }
        acc = acc * (U128)base + (U128)d;
    }

    if (!any)
        return false;

    while (isspace((unsigned char)*s))
        ++s;
    if (*s != '\0')
        return false;

    out = acc;
    return out;
}

I128 str_to_i128(const char* s, UMin base) {
    I128 out = 0;
    if (!s)
        return 0;

    while (isspace((unsigned char)*s))
        ++s;

    // sign
    bool neg = false;
    if (*s == '+' || *s == '-') {
        neg = (*s == '-');
        ++s;
    }

    const char* p = s;

    // just in case, check the base
    if (base == 0) {
        if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
            base = 16;
            p += 2;
        }
        else {
            base = 10;
        }
    }
    else if (base == 16) {
        if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
            p += 2;
    }
    else if (base != 10) {
        return false;
    }

    U128 mag = 0;
    Bool any = false;

    for (;; ++p) {
        UMax d = digit_val(*p);
        if (d == 255u || d >= (UMax)base)
            break;
        any = true;

        if (mag > (U128_MAX - (U128)d) / (U128)base)
            return false;
        mag = mag * (U128)base + (U128)d;
    }

    if (!any)
        return false;

    while (isspace((unsigned char)*p))
        ++p;
    if (*p != '\0')
        return false;

    if (!neg) {
        if (mag > (U128)I128_MAX)
            return false; // overflow
        out = (I128)mag;
    }
    else {

        U128 limit = ((U128)1 << 127);
        if (mag > limit)
            return false; // overflow
        if (mag == limit) {
            out = I128_MIN; // exactly -2^127
        }
        else {
            out = -(I128)mag;
        }
    }

    return out;
}

#endif