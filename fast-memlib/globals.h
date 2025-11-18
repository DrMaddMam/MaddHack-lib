#ifndef FASTMEMLIB_GLOBALS_H
#define FASTMEMLIB_GLOBALS_H
#ifndef BLOCK_LIST_SIZE_REPLACE
#define BLOCK_LIST_SIZE 256
#endif
#ifndef BLOCK_SIZE_FORCE_REPLACE
#define BLOCK_SIZE (BLOCK_LIST_SIZE * 8)    // Default to 2048 bytes
#endif
#define OVERHEAD_SIZE (alignof(max_align_t)*8)                  // overhead for management
#define BLOCK_SIZE_FUNCTIONAL ((BLOCK_SIZE-OVERHEAD_SIZE)+1)    // usable size after overhead
#ifndef MAIN_BLOCK_REPLACE
#define MAIN_BLOCK mem_block
#endif
#ifndef UPDATE_MEM_ON_FUNC_CALL
#define UPDATE_MEM_ON_FUNC_CALL
#endif
#ifndef MH_BUMP_FIRST
#define MH_BUMP_FIRST 1           /* 1 = bump path first (fast common case) */
#endif
#ifndef MH_ALIGN
#define MH_ALIGN _Alignof(max_align_t)  /* usually 16 on x86-64 */
#endif
#define MH_ALIGN_UP(x)  (((x) + (UMax)(MH_ALIGN-1)) & ~(UMax)(MH_ALIGN-1))
#endif // FASTMEMLIB_GLOBALS_H