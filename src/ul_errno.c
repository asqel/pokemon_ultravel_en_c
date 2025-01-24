#include "ul_errno.h"
#include <stdlib.h>

u32 ul_errno[UL_ERRNO_LEN] = {0};
int ul_errno_len = 0;

char *ul_errno_str[ERRNOS_LEN + 1] = {0};

void ul_add_errno(u32 err) {
	if (err == ERR_NONE)
		return ;
	if (ul_errno_len >= UL_ERRNO_LEN) {
		for (int i = 1; i < ul_errno_len; i++)
			ul_errno[i - 1] = ul_errno[i];
		ul_errno[ul_errno_len - 1] = err;
		return ;
	}
	ul_errno[ul_errno_len++] = err;
}

char *ul_get_errno_str(u32 err) {
	if (err < ERRNOS_LEN)
		return ul_errno_str[err];
	return "Invalid error code";
}

void init_errno() {
	ul_errno_str[ERR_NONE] = "No error";
	ul_errno_str[ERR_TEXTURE_NOT_FOUND] = "texture not found";
}