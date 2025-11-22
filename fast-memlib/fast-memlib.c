#ifndef FASTMEMLIB_C
#define FASTMEMLIB_C

#include <stddef.h>
#include <stdalign.h>
#include "../madd-types.h"
#include "globals.h"

// fastasf
_Alignas(max_align_t) static U8 mem_block[BLOCK_SIZE];

// close enough to linked list
struct mem_part {
    U0*  location;   // first for *(void**)
    UMax size;
    Bool freeable;
} mem_block_list[BLOCK_LIST_SIZE] = {{mem_block, 0, false}};

#define MAIN_BLOCK mem_block
#define CURRENT_BLOCK mem_block_list[rover.current_block_index]

struct mem_rover { UMax current_block_index; } rover = {0};
static UMax mem_top  = 0;
static UMax live_cnt = 0; // amount of block list used

// honestly just learned that align is fast and had to add some devil code
#define A_ALIGN ((UMax)_Alignof(max_align_t))
#define ALIGN_UP(x) (((x) + (A_ALIGN - 1)) & ~(A_ALIGN - 1))

// avail + alignment space
inline UMax tail_avail() {
    UMax t = ALIGN_UP(mem_top);
    return (t <= BLOCK_SIZE) ? (BLOCK_SIZE - t) : 0;
}

// 0 = freeable
static inline struct mem_part* grab_empty_slot() {
    for (UMax k = 0; k < BLOCK_LIST_SIZE; ++k)
        if (!mem_block_list[k].freeable && mem_block_list[k].size == 0)
            return &mem_block_list[k];
    return NULL;
}

// maintenance
Bool updateMem() {
    for (UMax i = 0; i < BLOCK_LIST_SIZE; ++i) {
        if (!(mem_block_list[i].freeable && mem_block_list[i].size)) continue;
        U8* i_end = (U8*)mem_block_list[i].location + mem_block_list[i].size;

        for (UMax j = 0; j < BLOCK_LIST_SIZE; ++j) {
            if (i == j) continue;
            if (!(mem_block_list[j].freeable && mem_block_list[j].size)) continue;

            U8* j_start = (U8*)mem_block_list[j].location;
            if (i_end == j_start) {

                mem_block_list[i].size += mem_block_list[j].size;
                mem_block_list[j].size  = 0;

                j = (UMax)-1;
                i_end = (U8*)mem_block_list[i].location + mem_block_list[i].size;
            }
        }
    }
    return true;
}

// bump fast
static inline struct mem_part* bump_alloc(UMax size) {
    size = ALIGN_UP(size);
    mem_top = ALIGN_UP(mem_top);

    if (rover.current_block_index >= BLOCK_LIST_SIZE) return NULL;
    if (mem_top + size > BLOCK_SIZE) return NULL;

    struct mem_part *p = &CURRENT_BLOCK;
    p->location = (U8*)MAIN_BLOCK + mem_top;
    p->size = size;
    p->freeable = false;

    mem_top += size;
    ++live_cnt;

    ++rover.current_block_index;
    if (rover.current_block_index < BLOCK_LIST_SIZE) {
        mem_block_list[rover.current_block_index].location = (U8*)MAIN_BLOCK + mem_top;
        mem_block_list[rover.current_block_index].size = 0;
        mem_block_list[rover.current_block_index].freeable = false;
    }
    return p;
}

/// @brief allocate memory
/// @param size 
/// @return pointer to mem_part struct describing allocated memory
struct mem_part* getMem(UMax size) {
    if (!size) return NULL;
#ifdef UPDATE_MEM_ON_FUNC_CALL
    updateMem();
#endif

    // carmack ctrl-c ctrl-v
    UMax need = ALIGN_UP(size);

    for (UMax i = 0; i < BLOCK_LIST_SIZE; ++i) { // ++i is better, and (++)i will die on this hill
        if (!mem_block_list[i].freeable) continue;

        U0* base = mem_block_list[i].location;
        UMax blk = mem_block_list[i].size;

        if (blk < need) continue;

        // if big enough to split off a tail chunk, do it
        if (blk >= need + A_ALIGN) {
            struct mem_part* tail = grab_empty_slot();
            if (tail) {
                // head becomes the allocated block
                mem_block_list[i].size = need;
                mem_block_list[i].freeable = false;

                // tail is the remainder (still free)
                tail->location = (U8*)base + need;
                tail->size = blk - need;
                tail->freeable = true;

                ++live_cnt;
                return &mem_block_list[i];
            }
            // if no descriptor available, fall through and take whole block
        }

        // take block as-is (no split)
        mem_block_list[i].freeable = false;
        ++live_cnt;
        return &mem_block_list[i];
    }

    // bump
    return bump_alloc(size);
}

// reset
Bool resetMem() {
    mem_top = 0;
    live_cnt = 0;
    rover.current_block_index = 0;

    mem_block_list[0].location = (U8*)MAIN_BLOCK;
    mem_block_list[0].size = 0;
    mem_block_list[0].freeable = false;

    for (UMax i = 1; i < BLOCK_LIST_SIZE; ++i) {
        mem_block_list[i].location = (U8*)MAIN_BLOCK;
        mem_block_list[i].size = 0;
        mem_block_list[i].freeable = false;
    }
    return true;
}
// cleanup
UMax cleanupMem() {
    mem_top = 0;
    rover.current_block_index = 0;
    UMax unfreed = 0;
    for(UMax i = 0; i < live_cnt; ++i) {
        if(mem_block_list[i].freeable == false && mem_block_list[i].size > 0) {
            ++unfreed;
            mem_block_list[i].freeable = true;
            mem_block_list[i].size = 0;
        }
    }
    live_cnt = 0;
    return unfreed;
}

/// @brief free mem_part and mark as reusable
/// @param part 
/// @return if the memory was successfully freed
inline Bool freeMem(struct mem_part* part) {
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

#endif /* FASTMEMLIB_C */
