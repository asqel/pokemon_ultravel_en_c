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
	u16 pp_max;
	u16 pp_count;

	pk_uint_t attack_id;
};

struct pk_attack_info{
	u8 type1;
	u8 (*get_typ)(pokemon_t *self, pokemon_t *op);
	u16 pp;

	u16 power;
	pk_float_t accuracy; // (/100)
	u8 category;
};

enum POKEMON_ORIGIN {
	pk_origin_natural,
	pk_origin_egg,
	pk_origin_event,
};

struct pokemon_t{
	u8 gender;
	u8 shiny;
	u16 ev[PK_STAT_LEN];
	u16 iv[PK_STAT_LEN];
	u16 status[PK_STAT_LEN];
	char *DO; // will be freed
	char *surname; // will be freed
	u32 hp;
	u32 lvl;
	u32 current_xp;
	u16 ability;
	pk_uint_t item;
	pk_uint_t effect;
	u8 is_confused;
	pk_attack_t attacks[4];
	u8 origin;
	u32 extra_data1;
	u32 extra_data2;
	u32 extra_data3;
	u32 extra_data4;
};

enum SPRITE_TYPES{
	SPRITE_TYPE_NORMAL,
	SPRITE_TYPE_GENDER,
	SPRITE_TYPE_SPECIAL,
};

typedef struct {
	u8 is_genderless;
	u8 sprite_type;
	pk_float_t male_ratio; // (/100) (0 for no male) (100 for no female)
	texture_t sprite_default; // male or female if sprite is unique
	texture_t sprite_female;
	texture_t (*get_sprite)(pokemon_t *self, pokemon_t *op);
	pk_uint_t xp_given;
	pk_uint_t ev_given[PK_STAT_LEN];
	u8 leveling_type;
	pk_uint_t base_stats[PK_STAT_LEN];
	struct moveset_t *moveset;
	u16 *abilities; // will be freed
	u16 *hidden_abilities;
	u8 catch_rate;
	u16 *egg_groups; // will be freed
	u8 egg_hatch_type;

	u8 types[2];
	void (*dynamic_types)(pokemon_t *self, pokemon_t *op, u8 types[2]);
	int evolution_info_len;
	struct evolution_info *evolutions;
} pokemon_species_info;


typedef struct {
	u32 pk_id; 
	u8 type;
	union {
		u8 weather;
		u32 level;
		int (*will_evolve)(pokemon_t *self);
	} condition;
} evolution_info;

enum moveset_conditions {
	moveset_cond_lvl,
	moveset_cond_egg,
	moveset_cond_lvl_egg, // condition & 0xFFFF == lvl
};

struct moveset_t {
	pk_attack_t *moves;
	u8 *conditions_type;
	u32 *conditions;
};

#endif