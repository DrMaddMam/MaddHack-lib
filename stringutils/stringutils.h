#ifndef STRREV_H
#define STRREV_H
#include "../madd-types.h"

/// @brief reverses a string in place
/// @param s 
/// @return if successful
Bool strrev(char* s) {
    if (!s) return false;
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
    return true;
}
#endif // STRREV_H