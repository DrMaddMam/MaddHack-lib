#ifndef MADDHACK_H
#define MADDHACK_H
#include <stdio.h>
#include "madd-types.h"
#include "fast-memlib/fast-memlib.h"
#include "128bit/128bit.h"
#include "hackery/madd-hackery.h"
#include "flags/flags.h"
inline Bool initMaddHack() {
    return (initFlags() && resetMem()); // todo: add more init functions later
}
inline Bool exitMaddHack() {
    UMax unfreed = cleanupMem();
    if(unfreed > 0) { 
        fprintf(stderr, "Forgot to free "UMaxFORMAT" pieces of memory", unfreed);
        return false;
    }
    return true;
}
#endif // MADDHACK_H