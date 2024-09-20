#ifndef VEC_H
#define VEC_H

#include "types.h"

typedef struct {
	pk_int_t x;
	pk_int_t y;
} vec2i_t;

typedef struct {
	pk_uint_t x;
	pk_uint_t y;
} vec2u_t;

typedef struct {
	pk_float_t x;
	pk_float_t y;
} vec2f_t;

#endif