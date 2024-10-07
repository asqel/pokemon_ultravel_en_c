#include "world.h"
#include "types.h"
#include "uti.h"
#include "registers.h"
#include <stdio.h>
#include <stdlib.h>
#include "save.h"

/*
Object:
	is_air (1 Byte)
	if (!is_air) {
		id_idx (8 Byte)
		extra (1 Byte)
		//extra: 
			bit 1: has_hitbox
	}

key_values:
	key_str_idx (8 byte)
	value_object

value_object:
	type (1 byte)
	if (type == data_type_int or data_type_uint)
		value (8 byte)
	if (type == data_type_str)
		value string idx (8 byte)
	if (type == data_type_float)
		value as double (8 byte)
	if (type == data_type_char or data_type_uchar)
		value (1 byte)
	if (type == data_type_list)
		list_length  (1 byte)
		values as  value_object
	if (type == data_type_dict)
		value as data
*/


void bytes_append_uint(bytes *res, pk_uint_t x) {
	res->val = realloc(res->val, sizeof(u8) * (res->len + 8));
	for (int i = 0; i < 8; i++)
		res->val[res->len + i] = 0;
	memcpy(&(res->val[res->len]), &x, sizeof(pk_uint_t) > 8 ? 8 : sizeof(pk_uint_t));
	res->len += 8;
}

void bytes_append_short(bytes *res, u16 x) {
	res->val = realloc(res->val, sizeof(u8) * (res->len + 2));
	for (int i = 0; i < 2; i++)
		res->val[res->len + i] = 0;
	memcpy(&(res->val[res->len]), &x, sizeof(u16) > 2 ? 2 : sizeof(u16));
	res->len += 2;
}

void object_to_bytes(object_t *object, bytes *res, char ***strs, int *strs_len) {
	res->len++;
	res->val = realloc(res->val, sizeof(u8) * res->len);
	res->val[res->len - 1] = 0;
	if (object->id == 0) {
		res->val[res->len - 1] = 1;
		return ;
	}
	bytes_append_uint(res, search_or_add_strs(strs, strs_len, get_object_id_str(object->id)));
}

void bytes_append_str(bytes *res, char *str) {
	res->val = realloc(res->val, sizeof(u8) * (res->len + strlen(str) + 1));
	for (int i = 0; str[i] != '\0'; i++) {
		res->val[res->len] = str[i];
		res->len++;
	}
	res->val[res->len] = '\0';
	res->len++;
}

void bytes_cat_bytes(bytes *dest, bytes *src) {
	dest->val = realloc(dest->val, sizeof(u8) * (dest->len + src->len));
	for (int i = 0; i < src->len; i++) {
		dest->val[dest->len] = src->val[i];
		dest->len++;
	}
}

bytes chunk_to_bytes(chunk_t *chunk) {
	bytes back_obj_bytes = {.len = 0, .val = 0};
	bytes obj_bytes = {.len = 0, .val = 0};
	bytes fore_obj_bytes = {.len = 0, .val = 0};
	bytes res = {.len = 0, .val = 0};
	char **strs = NULL;
	int strs_len = 0;

	bytes_append_str(&res, MAGIC_NUMBER);
	bytes_append_short(&res, VERSION_MAGIC_NUMBER(SAVE_DEFAULT));
	for (int y = 0;  y < CHUNK_LEN; y++)
		for (int x = 0;  x < CHUNK_LEN; x++) {
			object_to_bytes(&(chunk->background_obj[y][x]), &back_obj_bytes, &strs, &strs_len);
			object_to_bytes(&(chunk->objects[y][x]), &obj_bytes, &strs, &strs_len);
			object_to_bytes(&(chunk->objects_foreground[y][x]), &fore_obj_bytes, &strs, &strs_len);
		}

	bytes_append_uint(&res, strs_len);
	for (int i = 0; i < strs_len; i++) {
		bytes_append_str(&res, strs[i]);
	}

	bytes_cat_bytes(&res, &back_obj_bytes);
	bytes_cat_bytes(&res, &obj_bytes);
	bytes_cat_bytes(&res, &fore_obj_bytes);

	free(back_obj_bytes.val);
	free(obj_bytes.val);
	free(fore_obj_bytes.val);
	return res;
}

char *get_world_path(world_t *world) {
	return uti_join_path((char *[]){game_dir, "worlds", world->name, NULL});
}

char *get_chunk_path(world_t *world, chunk_t *chunk) {
	char *file_name = malloc(sizeof(char) * (4 + uti_number_len(chunk->pos.x) + uti_number_len(chunk->pos.x) + 1));// c_X_Y_
	sprintf(file_name, "c_%d_%d_", chunk->pos.x, chunk->pos.y);
	char *dir_path = get_world_path(world);
	char *res = uti_join_path((char *[]){dir_path, file_name, NULL});
	free(dir_path);
	free(file_name);
	return res;
}

void save_chunk(world_t *world, chunk_t *chunk) {
	char *dir_path = get_world_path(world);
	char *chunk_path = get_chunk_path(world, chunk);
	bytes chunk_bytes = chunk_to_bytes(chunk);
	uti_mkdir(dir_path);
	FILE *f = fopen(chunk_path, "w");
	fwrite(chunk_bytes.val, sizeof(u8), chunk_bytes.len, f);
	fclose(f);
	free(chunk_bytes.val);
	free(dir_path);
	free(chunk_path);
}

pk_uint_t bytes_read_u64(u8 *bytes) {
	pk_uint_t res = 0;
	memcpy(&res, bytes, sizeof(pk_uint_t) > 8 ? 8 : sizeof(pk_uint_t));
	return res;
}


void decode_chunk(world_t *world, chunk_t *chunk, u8 *bytes) {
	if (strcmp(bytes, MAGIC_NUMBER)) {
		new_empty_chunk(world, chunk->pos, chunk);
		return ;
	}
	bytes += MAGIC_NUMBER_LEN;
	bytes += 2; // skip save version

	int strs_len = bytes_read_u64(bytes);
	char **strs = malloc(sizeof(char *) * strs_len);
	bytes += 8;

	int i = 0;
	while (i < strs_len) {
		strs[i] = uti_strdup(bytes);
		bytes += strlen(bytes) + 1;
		i++;
	}
	for (int y = 0; y < CHUNK_LEN; y++)
		for (int x = 0; x < CHUNK_LEN; x++) {
			if (*bytes == 1) {
				chunk->background_obj[y][x] = object_air;
				bytes++;
				continue;
			}
			bytes++;
			chunk->background_obj[y][x] = get_object(strs[bytes_read_u64(bytes)]);
			bytes += 8;
		}
	for (int y = 0; y < CHUNK_LEN; y++)
		for (int x = 0; x < CHUNK_LEN; x++) {
			if (*bytes == 1) {
				chunk->objects[y][x] = object_air;
				bytes++;
				continue;
			}
			bytes++;
			chunk->objects[y][x] = get_object(strs[bytes_read_u64(bytes)]);
			bytes += 8;
		}
	for (int y = 0; y < CHUNK_LEN; y++)
		for (int x = 0; x < CHUNK_LEN; x++) {
			if (*bytes == 1) {
				chunk->objects_foreground[y][x] = object_air;
				bytes++;
				continue;
			}
			bytes++;
			chunk->objects_foreground[y][x] = get_object(strs[bytes_read_u64(bytes)]);
			bytes += 8;
		}
	
}