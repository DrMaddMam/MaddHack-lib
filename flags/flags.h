#ifndef FLAGS_H
#define FLAGS_H
/*
Simple flags library
Call initFlags(), inline, for initialization.
You should setup your flags to have unique defined values from 0 to __BYTESMAX__-1.
Use setFlag(flag, &var), getFlag(flag, var), clearFlag(flag, &var) to manipulate flags in a UMax variable.
*/
#include "../madd-types.h"

#define FLAG_NONE 0x00
UMax flags[__BITSMAX__] = { 0 };
inline Bool initFlags() {
    for (UMax i = 0; i < __BITSMAX__; ++i)
    {
        flags[i] = 1 << i;
    }
    return true;
}
inline Bool setFlag(UMax flag, UMax* ptr) {
    if (flag >= __BITSMAX__ || !ptr) return false;
    *ptr |= flags[flag];
    return true;
}
inline Bool getFlag(UMax flag, UMax ptr) {
    if (flag >= __BITSMAX__ || !ptr) return false;
    return (ptr & flags[flag]) != 0;
}
inline Bool clearFlag(UMax flag, UMax* ptr) {
    if (flag >= __BITSMAX__) return false;
    *ptr &= ~flags[flag];
    return true;
}
#endif // FLAGS_H