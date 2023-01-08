#ifndef GAME_SCREEN
#define GAME_SCREEN

#define screen_SCREEN_W (240)
#define screen_SCREEN_H (160)

#define screen_VCOUNT *((vu16 *) 0x04000006)

#define screen_BG0_TILEMAP ((vu16 *) 0x06008000)
#define screen_BG1_TILEMAP ((vu16 *) 0x06008800)
#define screen_BG2_TILEMAP ((vu16 *) 0x06009000)
#define screen_BG3_TILEMAP ((vu16 *) 0x06009800)

#define screen_BG0_XOFFSET *((vu16 *) 0x04000010)
#define screen_BG0_YOFFSET *((vu16 *) 0x04000012)

#define screen_BG1_XOFFSET *((vu16 *) 0x04000014)
#define screen_BG1_YOFFSET *((vu16 *) 0x04000016)

#define screen_BG2_XOFFSET *((vu16 *) 0x04000018)
#define screen_BG2_YOFFSET *((vu16 *) 0x0400001a)

#define screen_DISPLAY_CONTROL *((vu16 *) 0x04000000)
#define screen_DISPLAY_STATUS  *((vu16 *) 0x04000004)

#define screen_WINDOW_IN  *((vu16 *) 0x04000048)
#define screen_WINDOW_OUT *((vu16 *) 0x0400004a)

#define screen_CHAR_BLOCK_0 ((vu16 *) 0x06000000)
#define screen_CHAR_BLOCK_1 ((vu16 *) 0x06004000)
#define screen_CHAR_BLOCK_2 ((vu16 *) 0x06008000)
#define screen_CHAR_BLOCK_3 ((vu16 *) 0x0600c000)

#define screen_SPR_TILESET ((vu16 *) 0x06010000)

#define screen_BG0_CONTROL *((vu16 *) 0x04000008)
#define screen_BG1_CONTROL *((vu16 *) 0x0400000a)
#define screen_BG2_CONTROL *((vu16 *) 0x0400000c)
#define screen_BG3_CONTROL *((vu16 *) 0x0400000e)

#define screen_BG_PALETTE  ((vu16 *) 0x05000000)
#define screen_SPR_PALETTE ((vu16 *) 0x05000200)

/*
    memória de atributo de objeto. Em suma, é o espaço na RAM de vídeo onde os sprites são divididos em blocos 8x8,
    que podem ser montados e colocados em qualquer lugar da tela (ao contrário dos fundos, que precisam ser montados
    em uma grade e cobrir todo o espaço da tela).
*/
#define screen_OAM ((vu16 *) 0x07000000)

extern void screen_init(void);
extern void screen_vsync(void);

#endif // GAME_SCREEN