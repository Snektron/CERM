#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "vector.h"

void graphics_set_pixel(uint16_t x, uint8_t y, uint16_t color);
void graphics_clear();
uint16_t graphics_color(float r, float b, float g);
uint16_t graphics_colorv(vec3_t* color);

#endif
