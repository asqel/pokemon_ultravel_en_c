#ifndef SAVE_H
#define SAVE_H

enum SAVE_VERSIONS {
	SAVE_000,

	SAVE_LEN
};

#define SAVE_DEFAULT SAVE_LEN - 1

#define VERSION_MAGIC_NUMBER(VERSION) ((unsigned short int)(0xFFFF - VERSION))
#define MAGIC_NUMBER "PK_UL"
#define MAGIC_NUMBER_LEN 6

void save_chunk(world_t *world, chunk_t *chunk);
char *get_chunk_path(world_t *world, chunk_t *chunk);
void decode_chunk(world_t *world, chunk_t *chunk, u8 *bytes);

#endif