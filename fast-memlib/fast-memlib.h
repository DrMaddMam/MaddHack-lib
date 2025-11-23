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
Bool resetMem();
Bool updateMem();
UMax cleanupMem();
/// @brief free mem_part and mark as reusable
/// @param part 
/// @return if the memory was successfully freed
static inline UMax freeMem(struct mem_part* part) {
    if (part && !part->freeable) {
        part->freeable = true;
        if (live_cnt) --live_cnt;

        if (live_cnt == 0) {

            resetMem();
        }
        return true;
    }
    return false;
}
#endif // FASTMEMLIB_H