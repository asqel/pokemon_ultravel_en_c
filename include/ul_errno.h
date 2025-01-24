#ifndef UL_ERRNO_H
#define UL_ERRNO_H

#include "types.h"

#define UL_ERRNO_LEN 256

extern u32 ul_errno[UL_ERRNO_LEN];

enum ERRNOS{
	ERR_NONE,
	ERR_TEXTURE_NOT_FOUND,


	ERRNOS_LEN
};

void ul_add_errno(u32 err);
char *ul_get_errno_str(u32 err);
void init_errno();


#endif