#ifndef VEC_H_
#define VEC_H_

#include <math.h>
#include <stdio.h>

typedef struct {
  float x;
  float y;
} vf;

vf vf_makeff(float x, float y) { return (vf){.x = x, .y = y}; }

vf vf_makef(float num) { return (vf){.x = num, .y = num}; }

void vf_str(vf v, char *p) { sprintf(p, "(%.1f, %.1f)", v.x, v.y); }

vf vf_add(vf v1, vf v2) { return (vf){.x = v1.x + v2.x, .y = v1.y + v2.y}; }

vf vf_sub(vf v1, vf v2) { return (vf){.x = v1.x - v2.x, .y = v1.y - v2.y}; }

vf vf_mul(vf v1, vf v2) { return (vf){.x = v1.x * v2.x, .y = v1.y * v2.y}; }

vf vf_div(vf v1, vf v2) { return (vf){.x = v1.x / v2.x, .y = v1.y / v2.y}; }

float vf_sqrmag(vf v) { return v.x * v.x + v.y * v.y; }

float vf_mag(vf v) { return sqrt(v.x * v.x + v.y * v.y); }

float vf_dist(vf v1, vf v2) { return vf_mag(vf_sub(v1, v2)); }

float vf_sqrdist(vf v1, vf v2) { return vf_sqrmag(vf_sub(v1, v2)); }

#endif // VEC_H_
