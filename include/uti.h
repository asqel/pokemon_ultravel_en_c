#ifndef UTI_H
#define UTI_H
#define NO_STDIO_REDIRECT

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

#if defined(__linux__)
	#include <dirent.h>
	#include <unistd.h>
	#include <limits.h>
	#include <libgen.h>
	#include <sys/stat.h>
	#define PATH_SEP "/"
#elif defined(_WIN32)
	#include <windows.h>
	#include <direct.h>
	#define PATH_SEP "\\"
#elif defined(__APPLE__)
	#include <sys/stat.h>
	#include <mach-o/dyld.h>
	#define PATH_SEP "/"
#else
	#error unsupported os in uti.h
#endif

#define PRINT_ERR SDL_Log
#define DEBUG(...) printf(__VA_ARGS__)


#define UTI_MIN(a, b) ((a) < (b) ? (a) : (b))
#define UTI_MAX(a, b) ((a) > (b) ? (a) : (b))

extern char *game_dir;

char *uti_strdup(const char *str);
int uti_is_dir(const char *path);
int uti_is_file(const char *path);
int uti_path_exists(const char *path);
char *uti_read_file(const char *path);
char *uti_join_path(char **strs);
int uti_init();
void uti_exit();
char **uti_dir_content(char *path);
int uti_ends_with(char *str, char *ending);
int search_or_add_strs(char ***strs, int *len, char *to_search);
int uti_strlen_utf8(char *str);
int uti_number_len(int x);
void uti_mkdir(char *path);

/*
compare path1 and path2
if cmp_ext is 1, compare the full path like strcmp
if cmp_ext is 0, compare the path without the extension

return 0 if the paths are the same
*/
int uti_file_cmp(const char *path1, const char *path2, int cmp_ext);

/*
compare path extension
return 0 if the extension is the same
*/
int uti_cmp_ext(const char *path1, const char *path2);

char *uti_path_replace_ext(char *path, char *ext);

SDL_Surface *uti_read_png(char *path);

#endif