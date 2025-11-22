#ifndef MADDHACK_H
#define MADDHACK_H
#include "128bit/128bit.h"
#include "fast-memlib/fast-memlib.h"
#include "flags/flags.h"
#include "hackery/madd-hackery.h"
#include "madd-types.h"

/// @brief initialize MaddHack resources
/// @return if initialization was successful
inline Bool initMaddHack() { return (initFlags() && resetMem()); }
/// @brief cleanup MaddHack resources
/// @return amount of errors during cleanup
inline UMax exitMaddHack() {
    UMax errors = 0;
    errors += cleanupMem();
    return errors;
}
#endif // MADDHACK_H