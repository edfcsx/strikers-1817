#ifndef GAME_ASM
#define GAME_ASM

#include "types.h"

#define asm_THUMB __attribute__((target("thumb")))

#define asm_NOINLINE __attribute__((noinline))
#define asm_NOCLONE  __attribute__((noclone))

#define asm_EWRAM_SECTION        __attribute__((section(".ewram")))
#define asm_EWRAM_BSS_SECTION    __attribute__((section(".bss.ewram")))
#define asm_IWRAM_SECTION        __attribute__((section(".iwram")))
#define asm_IWRAM_RODATA_SECTION __attribute__((section(".rodata_iwram")))

#define static_assert _Static_assert

#ifndef NULL
    #define NULL ((void *) 0)
#endif

#endif // GAME_ASM