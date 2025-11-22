#ifndef STRREV_H
#define STRREV_H
#include "../madd-types.h"

U0 strrev(char* s) {
    if (!s) return;
    // char* start = s; // not needed, just use the original pointer 
    char* end = s;
    while (*end) {
        ++end;
    }
    --end; // last character before null terminator
    while (s < end) {
        *s ^= *end; // swap using XOR
        *end ^= *s;
        *s ^= *end;
        ++s;
        --end;
    }
}
#endif // STRREV_H