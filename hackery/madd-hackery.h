#ifndef MADD_HACKERY_H
#define MADD_HACKERY_H
#include "../madd-types.h"
/// @brief calls a function at a given pointer
/// @param func 
inline void call(void* func) {
    return ((void (*)())func)();
}
/// @brief makes a pointer from an integer address
/// @param addr 
/// @return the pointer
inline void* makeptr(UMax addr) {
    return (void*)addr;
}
/// @brief adds an offset in bytes to a pointer
/// @param ptr 
/// @param offset in bytes
/// @return the new pointer
inline void* addptr(void* ptr, UMax offset) {
    return (void*)((UMax)ptr + offset);
}
#endif // MADD_HACKERY_H