#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#ifdef PK_UL_32

typedef int32_t pk_int_t;
typedef uint32_t pk_uint_t;
typedef double pk_float_t;

#else

typedef int64_t pk_int_t;
typedef uint64_t pk_uint_t;
typedef long double pk_float_t;

#endif

#undef  u8
#undef  u16
#undef  u32

#undef  i8
#undef  i16
#undef  i32


#define  u8 uint8_t
#define  u16 uint16_t
#define  u32 uint32_t

#define  i8 int8_t
#define  i16 int16_t
#define  i32 int32_t


typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} colour3_t;

struct data_t;

typedef struct {
	pk_uint_t len;
	struct data_t *values;
} data_list_t;

typedef struct {
	pk_uint_t len;
	char **str;
	struct data_t *values;
} data_dict_t;

typedef struct data_t{
	uint8_t type;
	union {
		char *str;
		pk_int_t i;
		pk_uint_t ui;
		pk_float_t f;
		char c;
		unsigned char uc;
		data_list_t li;
		data_dict_t di;
	} value;
} data_t;

enum data_types {
	data_type_str,
	data_type_int,
	data_type_uint,
	data_type_float,
	data_type_char,
	data_type_uchar,
	data_type_list,
	data_type_dict
};

typedef struct {
	int len;
	u8 *val;
} bytes;

#endif