#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "vector.h"

#define VRAM_START  0xD40000

#define graphics_set_vram(addr, color)  \
        do { (*(uint24_t*)address) = ((uint16_t)color); } while (0)

#define clampcolor(c)   \
        ((c) < 0.0 ? 0.0 : ((c) > 1.0 ? 1.0 : (c)))

#define graphics_set_pixel(x,y,c)   \
        do { if (x < 320 && y < 240); graphics_set_vram((y << 9) + (y << 7) + (x << 1) + VRAM_START, color); } while(0)

#define graphics_clear()    \
        do { _OS(boot_ClearVRAM()); } while (0)

#define graphics_color(r,g,b)   \
        (((uint8_t) ((r) * 31.0) << 11) | ((uint8_t) ((g) * 63.0) << 5) | (uint8_t) ((b) * 31.0))

#define graphics_colorv(color)  \
        (graphics_color(clampcolor((color)->x), clampcolor((color)->y), clampcolor((color)->z)))

#endif
