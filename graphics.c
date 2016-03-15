#include <tice.h>
#include <stdint.h>
#include "graphics.h"
#include "vector.h"

#define VRAM_START 0xD40000

void graphics_set_vram(uint24_t address, uint16_t color);

double clampcolor(double c)
{
	return c < 0.0 ? 0.0 : c > 1.0 ? 1.0 : c;
}

void graphics_set_pixel(uint16_t x, uint8_t y, uint16_t color)
{
	if (x < 320 && y < 240)
		graphics_set_vram((y << 9) + (y << 7) + (x << 1) + VRAM_START, color);
}

void graphics_set_vram(uint24_t address, uint16_t color)
{
	_OS(
		asm("LD HL,(IX+6)");
		asm("LD A,(IX+9)");
		asm("LD (HL), A");
		asm("INC HL");
		asm("LD A,(IX+10)");
		asm("LD (HL), A");
	);
}

void graphics_clear()
{
	_OS(boot_ClearVRAM());
}

uint16_t graphics_color(float r, float g, float b)
{
	return ((uint8_t) (r * 31.0) << 11) | ((uint8_t) (g * 63.0) << 5) | (uint8_t) (b * 31.0);
}

uint16_t graphics_colorv(vec3_t* color)
{
	return graphics_color(clampcolor(color->x), clampcolor(color->y), clampcolor(color->z));
}
