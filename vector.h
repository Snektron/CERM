#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct
{
	double x, y;
} vec2_t;

typedef struct
{
	double x, y, z;
} vec3_t;

vec2_t* vec2(vec2_t* v, double x, double y);
vec3_t* vec3(vec3_t* v, double x, double y, double z);

void vec2_copy(vec2_t* a, vec2_t* b);
void vec3_copy(vec3_t* a, vec3_t* b);

vec2_t* vec2_normalize(vec2_t* a);
vec3_t* vec3_normalize(vec3_t* a);

vec3_t* vec3_setLength(vec3_t* a, double x);

vec3_t* vec3_cross(vec3_t* a, vec3_t* b, vec3_t* out);

vec3_t* vec3_add(vec3_t* a, vec3_t* b, vec3_t* out);

vec3_t* vec3_mul(vec3_t* a, vec3_t* b, vec3_t* out);

vec3_t* vec3_scale(vec3_t* a, double x);

#define vec2_length(a)  (sqrt((a)->x*(a)->x + (a)->y*(a)->y))

#define vec3_length(a)  (sqrt((a)->x*(a)->x + (a)->y*(a)->y + (a)->z*(a)->z))

#define vec3_dot(a,b)   ((a)->x*(b)->x + (a)->y*(b)->y + (a)->z*(b)->z)

#endif
