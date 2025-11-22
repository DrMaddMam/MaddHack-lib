#ifndef MADDHACK_H
#define MADDHACK_H
#include "madd-types.h"
#include "fast-memlib/fast-memlib.h"
#include "128bit/128bit.h"
#include "hackery/madd-hackery.h"
#include "flags/flags.h"

/// @brief initialize MaddHack resources
/// @return if initialization was successful
inline Bool initMaddHack() {
    return (
        initFlags() &&
        resetMem()
    );
}
/// @brief cleanup MaddHack resources
/// @return amount of errors during cleanup
inline UMax exitMaddHack() {
#ifdef USE_FAST_MEMLIB
    UMax errors = 0;
    errors += cleanupMem();
    return errors;
#endif
    return true;
}
#endif // MADDHACK_H