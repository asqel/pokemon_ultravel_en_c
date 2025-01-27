#ifndef UL_ERRNO_H
#define UL_ERRNO_H

#include "types.h"

#define UL_ERRNO_LEN 256

extern u32 ul_errno[UL_ERRNO_LEN];
extern u32 ul_last_errno;

#define UL_LAST_ERRNO() ul_last_errno

enum ERRNOS{
	ERR_NONE,
	ERR_TEXTURE_NOT_FOUND,
	ERR_ANIMATION_NOT_FOUND,


	ERRNOS_LEN
};

void ul_add_errno(u32 err);
char *ul_get_errno_str(u32 err);
void init_errno();


#endif