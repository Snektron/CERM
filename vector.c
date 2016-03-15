#include <math.h>
#include "vector.h"

vec2_t* vec2(vec2_t* v, double x, double y)
{
	v->x = x;
	v->y = y;
	return v;
}

vec3_t* vec3(vec3_t* v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return v;
}

// copy a to b
void vec3_copy(vec3_t* a, vec3_t* b)
{
	b->x = a->x;
	b->y = a->y;
	b->z = a->z;
}

void vec2_copy(vec2_t* a, vec2_t* b)
{
	b->x = a->x;
	b->y = a->y;
}

// normalize vector
vec2_t* vec2_normalize(vec2_t* a)
{
	double length = sqrt(a->x * a->x + a->y * a->y);
	a->x /= length;
	a->y /= length;
	return a;
}

vec3_t* vec3_normalize(vec3_t* a)
{
	double length = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x /= length;
	a->y /= length;
	a->z /= length;
	return a;
}

vec3_t* vec3_setLength(vec3_t* a, double x)
{
	double length = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x = a->x * x / length;
	a->y = a->x * x / length;
	a->z = a->x * x / length;
	return a;
}

vec3_t* vec3_cross(vec3_t* a, vec3_t* b, vec3_t* out)
{
	double tmpx = a->y * b->z - a->z * b->y;
	double tmpy = a->z * b->x - a->x * b->z;
	double tmpz = a->x * b->y - a->y * b->x;
	out->x = tmpx;
	out->y = tmpy;
	out->z = tmpz;
	return out;
}

vec3_t* vec3_add(vec3_t* a, vec3_t* b, vec3_t* out)
{
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;
	return out;
}

vec3_t* vec3_mul(vec3_t* a, vec3_t* b, vec3_t* out)
{
	out->x = a->x * b->x;
	out->y = a->y * b->y;
	out->z = a->z * b->z;
	return out;
}

vec3_t* vec3_scale(vec3_t* a, double x)
{
	a->x *= x;
	a->y *= x;
	a->z *= x;
	return a;
}

double vec2_length(vec2_t* a)
{
	return sqrt(a->x*a->x + a->y*a->y);
}

double vec3_length(vec3_t* a)
{
	return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

double vec3_dot(vec3_t* a, vec3_t* b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}
