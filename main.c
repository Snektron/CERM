
#include <tice.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "vector.h"
#include "graphics.h"

#define MAX_DISTANCE 10.0
#define MAX_STEPS 50
#define EPSILON 0.01

const double pi = 3.14159265;

const double fov = 67.0 / 180.0 * pi;
vec3_t dir = {0,0,-1};
vec3_t pos = {0,1,5};
vec3_t up = {0,1,0};
vec3_t light = {1,1,1};
vec3_t right;

double max(double a, double b) { return a > b ? a : b; }
double min(double a, double b) { return a < b ? a : b; }

double f(vec3_t* p);
vec3_t* getNormal(vec3_t* p, vec3_t* n);
float diff(vec3_t* n, vec3_t* l);
double raymarch(vec3_t* ro, vec3_t* rd, vec3_t* color);
void raymain(vec2_t* uv, vec3_t* color);
void getRay(vec2_t* uv, vec3_t* rd);
void rayinit();

double sdSphere(vec3_t* p, double r){ return vec3_length(p)-r;}
double sdPlane(vec3_t* p, vec3_t* n, float h){ return vec3_dot(p, n) + h;}

double add(double d1, double d2){return min(d1, d2);}

double f(vec3_t* p)
{
	return add(sdPlane(p, &up, 0), sdSphere(p, 1.0));
}

vec3_t* getNormal(vec3_t* p, vec3_t* n)
{
	double x, d0;
	d0 = f(p);

	x = p->x; p->x += EPSILON; n->x = f(p) - d0; p->x = x;
	x = p->y; p->y += EPSILON; n->y = f(p) - d0; p->y = x;
	x = p->z; p->z += EPSILON; n->z = f(p) - d0; p->z = x;

	vec3_normalize(n);
	return n;
}

double diff(vec3_t* n, vec3_t* l)
{
	return max(0.0, vec3_dot(n, l));
}

double raymarch(vec3_t* ro, vec3_t* rd, vec3_t* color)
{
	double d = 0, h, s;
	vec3_t p, n;
	int i;

	for (i=0; i<MAX_STEPS; i++)
	{
		vec3_copy(rd, &p);
		vec3_scale(&p, d);
		vec3_add(&p, ro, &p);

		h = f(&p);
		if (h < EPSILON)
		{
			getNormal(&p, &n);
			s = diff(&n, &light);
			vec3(color, s, s, s);
			return d;
		}
		d += h;
		if (d > MAX_DISTANCE)
			break;
	}
	vec3(color, 0.0, 0.0, 0.3);
	return MAX_DISTANCE*1.01; // just to be safe
}

void getRay(vec2_t* uv, vec3_t* rd)
{
	vec3_t up2;
	double f = vec2_length(uv);
	f = f/tan(f * 1.17);

	vec3_normalize(vec3_cross(&right, &dir, &up2));

	vec3_copy(&dir, rd);
	vec3_scale(rd, f);

	vec3_scale(&up2, uv->y);
	vec3_add(&up2, rd, rd);

	vec3_copy(&right, &up2);
	vec3_scale(&up2, uv->x);
	vec3_add(&up2, rd, rd);

	vec3_normalize(rd);
}

void raymain(vec2_t* uv, vec3_t* color)
{
	vec3_t rd, ro;
	double d;

	uv->x -= 0.5;
	uv->y -= 0.5;
	uv->y *= 0.75;

	vec3_copy(&pos, &ro);
	getRay(uv, &rd);

	raymarch(&ro, &rd, color);
}

void rayinit()
{
	vec3_normalize(vec3_scale(vec3_cross(&up, &dir, &right), -1.0));
	vec3_normalize(&light);
	vec3_normalize(&dir);
}

void main()
{
	uint16_t x;
	uint8_t y;
	vec2_t uv;
	vec3_t color;

	graphics_clear();

	rayinit();
	for (x=0; x<320; x++)
		for (y=0; y<240; y++)
		{
			uv.x = (double) (x+0.5) / 320.0;
			uv.y = 1.0-(double) (y+0.5) / 240.0;
			raymain(&uv, &color);
			graphics_set_pixel(x, y, graphics_colorv(&color));
		}

	while(1);
	_OS(os_GetKey());
	pgrm_CleanUp();
}

//#include "test.c"
