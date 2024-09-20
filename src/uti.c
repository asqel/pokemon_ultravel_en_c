#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "uti.h"
#include "types.h"

char *game_dir = NULL;

char *uti_strdup(char *str) {
	char *res = NULL;
	int len = 0;
	int i = 0;

	if (str == NULL)
		return NULL;
	while (str[len] != '\0')
		len++;
	res = malloc(sizeof(char) * (1 + len));
	if (res == NULL)
		return NULL;
	while (str[i] != '\0') {
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

int uti_is_dir(char *path) {
	#if defined(__linux__)
		DIR* dir = opendir(path);

		if (dir) {
			closedir(dir);
			return 1;
		}
		return 0;
	#elif defined(_WIN32)
		WIN32_FIND_DATA find_file_data;
		HANDLE handler_find = FindFirstFile(path, &find_file_data);
		int is_directory = 0;
	
		if (handler_find == INVALID_HANDLE_VALUE)
			return 0;
		is_directory = (find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;	
		FindClose(handler_find); // Ferme la recherche
		return is_directory;
	#elif defined(__APPLE__)
		struct stat path_stat;
	
		if (stat(path, &path_stat) != 0)
			return 0;
		return S_ISDIR(path_stat.st_mode);
	#else
		#error unsupported os in uti.c ( uti_is_dir() )
	#endif
	return 0;
}

int uti_is_file(char *path) {
	FILE *f = fopen(path, "r");
	if (f == NULL)
		return 0;
	fclose(f);
	return 1;
}

int uti_path_exists(char *path) {
	return uti_is_dir(path) || uti_is_file(path);
}

char *uti_read_file(char *path) {
	FILE *f = NULL;
	int len = 0;
	char *res = NULL;

	if (path == NULL)
		return NULL;
	f = fopen(path, "rb");
	if (f == NULL)
		return NULL;
	
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);

	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL) {
		fclose(f);
		return NULL;
	}
	fread(res, sizeof(char), len, f);
	res[len] = '\0';

	fclose(f);
	return res;
}

char *uti_join_path(char **strs) {
	int total_len = 0;
	int i = 0;
	int k = 0;
	char *res = NULL;

	while (strs[i] != NULL) {
		total_len += strlen(strs[i]);
		if (strs[i + 1] != NULL)
			total_len += strlen(PATH_SEP);
		i++;
	}

	res = (char *)malloc(total_len + 1);
	if (res == NULL)
		return NULL;

	i = 0;
	res[0] = '\0';
	while (strs[i] != NULL) {
		strcat(res, strs[i]);
		if (strs[i + 1] != NULL)
			strcat(res, PATH_SEP);
		i++;
	}
	return res;
}

char* get_game_location() {
	#ifdef _WIN32
		char buffer[MAX_PATH] = {0};
		DWORD length = GetModuleFileNameA(NULL, buffer, MAX_PATH);

		if (length == 0 || length == MAX_PATH)
			return NULL;

		return uti_strdup(buffer);
	#elif __linux__
		char buffer[PATH_MAX] = {0};
		ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);

		if (length == -1)
			return NULL;

		buffer[length] = '\0';
		return uti_strdup(buffer);
	#elif __APPLE__
		char buffer[PATH_MAX] = {0};
		uint32_t size = sizeof(buffer);

		if (_NSGetExecutablePath(buffer, &size) != 0)
			return NULL;

		path = realpath(buffer, NULL);
		if (path == NULL)
			return NULL;
		return path;
	#else
		#error Error unsuported os in uti.c ( uti_get_abs_path() )
	#endif
}

// return directory content without prefix
char **uti_dir_content(char *path) {
	#if defined(_WIN32)
		WIN32_FIND_DATA findFileData;
        HANDLE hFind;
        char search_path[MAX_PATH];
        char **file_list = NULL;
        int count = 0;

        snprintf(search_path, MAX_PATH, "%s\\*", path);
        hFind = FindFirstFile(search_path, &findFileData);
        if (hFind == INVALID_HANDLE_VALUE) {
            return NULL;
        }

        do {
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                char **temp = realloc(file_list, sizeof(char*) * (count + 1));
                if (temp == NULL) {
                    for (int i = 0; i < count; i++)
                        free(file_list[i]);
                    free(file_list);
                    FindClose(hFind);
                    return NULL;
                }
                file_list = temp;
                file_list[count] = strdup(findFileData.cFileName);
                if (file_list[count] == NULL) {
                    for (int i = 0; i < count; i++)
                        free(file_list[i]);
                    free(file_list);
                    FindClose(hFind);
                    return NULL;
                }
                count++;
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);

        char **temp = realloc(file_list, sizeof(char*) * (count + 1));
        if (temp == NULL) {
            for (int i = 0; i < count; i++)
                free(file_list[i]);
            free(file_list);
            return NULL;
        }
        file_list = temp;
        file_list[count] = NULL;
        return file_list;	
	#elif defined(__linux__)
		DIR *dir;
		struct dirent *entry;
		char **file_list = NULL;
		int count = 0;

		dir = opendir(path);
		if (dir == NULL)
			return NULL;

		entry = readdir(dir);
		while (entry != NULL) {
			char **temp = NULL;

			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				temp = realloc(file_list, sizeof(char*) * (count + 1));
				if (temp == NULL) {
					for (int i = 0; i < count; i++)
						free(file_list[i]);
					free(file_list);
					closedir(dir);
					return NULL;
				}
				file_list = temp;
				file_list[count] = strdup(entry->d_name);
				if (file_list[count] == NULL) {
					for (int i = 0; i < count; i++)
						free(file_list[i]);
					free(file_list);
					closedir(dir);
					return NULL;
				}
				count++;
			}
			entry = readdir(dir);
		}
		closedir(dir);

		char **temp = realloc(file_list, sizeof(char*) * (count + 1));
		if (temp == NULL) {
			for (int i = 0; i < count; i++)
				free(file_list[i]);
			free(file_list);
			return NULL;
		}
		file_list = temp;
		file_list[count] = NULL;
		return file_list;
	#else
		#error Error unsuported os in uti.c ( uti_dir_content() )
	#endif

}

char *uti_dirname(char *path) {
	#if  defined(_WIN32)
		char *res = uti_strdup(path);
		int len = strlen(path);
		while (res[len -1] == '\\' && len > 0) {
			res[len - 1] = '\0';
			len--;
		}
		while (res[len - 1] != '\\' && len > 0) {
			res[len - 1] = '\0';
			len--;
		}
		while (res[len -1] == '\\' && len > 0) {
			res[len - 1] = '\0';
			len--;
		}
		return realloc(res, sizeof(char) * (strlen(res) + 1));
	#elif defined(__linux__)
		if (path == NULL)
			return NULL;
		char *res = uti_strdup(path);
		dirname(res);
		return realloc(res, sizeof(char) * (strlen(res) + 1));
	#else
		#error Error unsuported os in uti.c ( uti_dirname() )
	#endif
}

int uti_ends_with(char *str, char *ending) {
	int len1 = strlen(str);
	int len2 = strlen(ending);
	if (len2 > len1)
		return 0;
	if (len2 == len1)
		return strcmp(str, ending) == 0;
	return strcmp(&(str[len1 - len2]), ending) == 0;
}

int search_or_add_strs(char ***strs, int *len, char *to_search) {
	for (int i = 0; i < *len; i++) {
		if (!strcmp((*strs)[i], to_search))
			return i;
	}
	(*strs) = realloc(*strs, sizeof(char *) * (*len + 1));
	(*strs)[*len] = uti_strdup(to_search);
	(*len)++;
	return (*len) - 1;
}

int uti_init() {
	char *game = get_game_location();
	game_dir = uti_dirname(game);
	free(game);
	return 0;
}

void uti_exit() {
	free(game_dir);
}


int uti_strlen_utf8(char *str) {
	int len = 0;
	int i = 0;
	while (str[i] != '\0') {
		if (!(0b10000000 & str[i])) {
			i++;
			len++;
		}
		else if (0b110 == (((u8)str[i]) >> 5)) {
			i += 2;
			len++;
		}
		else if (0b1110 ==  (((u8)str[i]) >> 4)) {
			i += 3;
			len++;
		}
		else if (0b11110 ==  (((u8)str[i]) >> 3)) {
			i += 4;
			len++;
		}
		else {
			len++;
			i++;
		}
	}
	return len;
}

