#include "screen.h"
#include "asm.h"

asm_IWRAM_SECTION
void screen_vsync(void) {
    __asm__ volatile ("swi 0x05 << 16");
}

static void load_tileset(vu16 *dest, const u8 *tileset, u32 size, u8 zero_conversion) {
    for (u32 i = 0; i < size; i++) {
        u8 b0 = tileset[i * 2];
        u8 b1 = tileset[i * 2 + 1];

        if ((b0 & 0x0f) == 0)
            b0 |= zero_conversion;
        if ((b0 & 0xf0) == 0)
            b0 |= (zero_conversion << 4);
        
        if ((b1 & 0x0f) == 0)
            b1 |= zero_conversion;
        if ((b1 & 0xf0) == 0)
            b1 |= (zero_conversion << 4);

        // in a byte, lower 4 bits are for left, upper 4 bits for right
        b0 = (b0 << 4) | (b0 >> 4);
        b1 = (b1 << 4) | (b1 >> 4);

        dest[i] = (b1 << 8) | b0;
    }
}

/*
    BG Control
    BG Priority (0 is highest, 3 is lowest)
    Tileset character block
    Color mode (0 is 4bpp with 16/16 palettes)
    Tilemap screen block
    BG size (0 is 256x256)
*/
void screen_init(void) {
    /*
        0 - video mode
        1 << 6  - OBJ Character mapping (1 is linear)
        1 << 7  - Forced Blank
        0 << 8  - Enable BG 0
        1 << 9  - Enable BG 1
        0 << 10 - Enable BG 2
        1 << 11 - Enable BG 3
        1 << 12 - Enable Obj
        1 << 15 - Enable Obj Window
    */
    screen_DISPLAY_CONTROL = 0 | 1 << 6 | 1 << 7 | 0 << 8 | 1 << 9 |
        0 << 10 | 1 << 11 | 1 << 12 | 1 << 15;
    
    // Filter out the light layer when inside OBJ Window
    screen_WINDOW_OUT = ~(1 << 10);

    /* Sky background */
    screen_BG0_CONTROL = 3 | 0 << 2 | 0 << 7 | 16 << 8 | 0 << 14;

    /* Level Tiles */
    screen_BG1_CONTROL = 2 | 0 << 2 | 0 << 7 | 17 << 8 | 0 << 14;

    /* Light System */
    screen_BG2_CONTROL = 1 |1 << 2 | 0 << 7  | 18 << 8 | 0 << 14;

    /* Text and GUI */
    screen_BG3_CONTROL = 0 |1 << 2 | 0 << 7 | 19 << 8 | 0 << 14;
}

extern void screen_init_fonts(void) {

}