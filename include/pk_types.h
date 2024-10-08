#ifndef PK_TYPES_H
#define PK_TYPES_H

#include "types.h"

enum {
	PK_T_NORMAL,
	PK_T_GRASS,
	PK_T_FIRE,
	PK_T_WATER,
	PK_T_ELECTRIC,
	PK_T_ICE,
	PK_T_FIGHT,
	PK_T_POISON,
	PK_T_GROUND,
	PK_T_FLYING,
	PK_T_PSYCHIC,
	PK_T_BUG,
	PK_T_ROCK,
	PK_T_GHOST,
	PK_T_DRAGON,
	PK_T_DARK,
	PK_T_STEEL,
	PK_T_FAIRY,
	PK_T_LIGHT,
	PK_T_SUGAR,
	PK_T_PLASTIC,

	PK_T_LEN,

	PK_T_NONE
};

extern double table_types[PK_T_LEN][PK_T_LEN];

#endif