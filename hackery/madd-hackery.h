#ifndef MADD_HACKERY_H
#define MADD_HACKERY_H
#include "../madd-types.h"
inline void call(void* func) {
    return ((void (*)())func)();
}
inline void* makeptr(UMax addr) {
    return (void*)addr;
}
#endif // MADD_HACKERY_H