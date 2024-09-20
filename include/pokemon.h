#ifndef POKEMON_H
#define POKEMON_H

typedef struct pokemon_t pokemon_t;
typedef struct pk_attack_t pk_attack_t;

#include "types.h"
#include "world.h"

#define SURNAME_MAX_LEN 12
#define pk_att_category_physical 0
#define pk_att_category_special 0
#define pk_att_category_status 0


enum {
	PK_STAT_HP,
	PK_STAT_ATTACK,
	PK_STAT_DEFENSE,
	PK_STAT_SP_ATTACK,
	PK_STAT_SP_DEFENSE,
	PK_STAT_SPEED,
	PK_STAT_LEN
};


struct pk_attack_t{
	u8 type1;

	u16 pp_max;
	u16 pp_count;
	
	u16 power;
	pk_float_t accuracy; // 0 - 1
	u8 category;

	u32 attack_id;
};

struct pokemon_t{
	u8 nature;
	pk_uint_t hp;

	char nickname[SURNAME_MAX_LEN]; // no nickname == ""

	pk_attack_t attacks[4];

	pk_uint_t ev[PK_STAT_LEN];
	pk_uint_t iv[PK_STAT_LEN];
	


	u32 species_id; // 0 is no pokemon
	i8 gender; // 0: genderless, 1: male, 2: female
	u32 extra_info;
};

enum {
	SPRITE_TYPE_NORMAL,
	SPRITE_TYPE_GENDER,
	SPRITE_TYPE_SPECIAL,
};

typedef struct {
	u32 species_id;
	u8 male_ratio; // 0-100
	u8 female_ratio; // 0-100
	// gender less if both == 0

	pk_uint_t base_stats[PK_STAT_LEN];
	u8 sprite_type;
	texture_t base_sprite; // or male
	texture_t female_sprite;
	texture_t (*get_sprite)(pokemon_t *self, player_t *owner, pokemon_t *opponent);

} pokemon_species_info;

#endif