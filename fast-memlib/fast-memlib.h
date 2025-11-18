#ifndef FASTMEMLIB_H
#define FASTMEMLIB_H
#include "../madd-types.h"
#include <stdalign.h>
#include "globals.h"

struct mem_part* getMem(UMax size);
struct mem_part {
    U0* location;
    UMax size;
    Bool freeable;
};
inline UMax freeMem(struct mem_part* part) {
    if (part && !part->freeable) {
        // if not freed, free
        part->freeable = true;
        // dont mess with size
        return true;
    }
    return false;
}
Bool resetMem();
Bool updateMem();
UMax cleanupMem();
#endif // FASTMEMLIB_H