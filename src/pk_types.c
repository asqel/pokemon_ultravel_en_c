#include "pk_types.h"

double table_types[PK_T_LEN][PK_T_LEN] = {{0}};

void init_table_types() {
	for (int i = 0; i < PK_T_LEN; i++) {
		for (int k = 0; k < PK_T_LEN; k++) {
			table_types[i][k] = 1;
		}
	}

	table_types[PK_T_NORMAL][PK_T_ROCK] = 0.5;
	table_types[PK_T_NORMAL][PK_T_GHOST] = 0;
	table_types[PK_T_NORMAL][PK_T_STEEL] = 0.5;
	table_types[PK_T_NORMAL][PK_T_LIGHT] = 0;
	table_types[PK_T_NORMAL][PK_T_SUGAR] = 0.5;
	table_types[PK_T_NORMAL][PK_T_PLASTIC] = 2;

	table_types[PK_T_GRASS][PK_T_GRASS] = 0.5;
	table_types[PK_T_GRASS][PK_T_FIRE] = 0.5;
	table_types[PK_T_GRASS][PK_T_WATER] = 2;
	table_types[PK_T_GRASS][PK_T_POISON] = 0.5;
	table_types[PK_T_GRASS][PK_T_GROUND] = 2;
	table_types[PK_T_GRASS][PK_T_FLYING] = 0.5;
	table_types[PK_T_GRASS][PK_T_BUG] = 0.5;
	table_types[PK_T_GRASS][PK_T_ROCK] = 2;
	table_types[PK_T_GRASS][PK_T_DRAGON] = 0.5;
	table_types[PK_T_GRASS][PK_T_STEEL] = 0.5;
	table_types[PK_T_GRASS][PK_T_LIGHT] = 2;
	table_types[PK_T_GRASS][PK_T_PLASTIC] = 0.5;

	table_types[PK_T_FIRE][PK_T_GRASS] = 2;
	table_types[PK_T_FIRE][PK_T_FIRE] = 0.5;
	table_types[PK_T_FIRE][PK_T_WATER] = 0.5;
	table_types[PK_T_FIRE][PK_T_ICE] = 2;
	table_types[PK_T_FIRE][PK_T_BUG] = 2;
	table_types[PK_T_FIRE][PK_T_ROCK] = 0.5;
	table_types[PK_T_FIRE][PK_T_DRAGON] = 0.5;
	table_types[PK_T_FIRE][PK_T_STEEL] = 2;
	table_types[PK_T_FIRE][PK_T_LIGHT] = 0;
	table_types[PK_T_FIRE][PK_T_SUGAR] = 2;
	table_types[PK_T_FIRE][PK_T_PLASTIC] = 2;

	table_types[PK_T_WATER][PK_T_GRASS] = 0.5;
	table_types[PK_T_WATER][PK_T_FIRE] = 2;
	table_types[PK_T_WATER][PK_T_WATER] = 0.5;
	table_types[PK_T_WATER][PK_T_GROUND] = 2;
	table_types[PK_T_WATER][PK_T_ROCK] = 2;
	table_types[PK_T_WATER][PK_T_DRAGON] = 0.5;
	table_types[PK_T_WATER][PK_T_SUGAR] = 0.5;
	table_types[PK_T_WATER][PK_T_PLASTIC] = 0.5;

	table_types[PK_T_ELECTRIC][PK_T_GRASS] = 0.5;
	table_types[PK_T_ELECTRIC][PK_T_WATER] = 2;
	table_types[PK_T_ELECTRIC][PK_T_ELECTRIC] = 0.5;
	table_types[PK_T_ELECTRIC][PK_T_GROUND] = 0;
	table_types[PK_T_ELECTRIC][PK_T_FLYING] = 2;
	table_types[PK_T_ELECTRIC][PK_T_DRAGON] = 0.5;
	table_types[PK_T_ELECTRIC][PK_T_PLASTIC] = 0;

	table_types[PK_T_ICE][PK_T_GRASS] = 2;
	table_types[PK_T_ICE][PK_T_FIRE] = 0.5;
	table_types[PK_T_ICE][PK_T_WATER] = 0.5;
	table_types[PK_T_ICE][PK_T_ICE] = 0.5;
	table_types[PK_T_ICE][PK_T_GROUND] = 2;
	table_types[PK_T_ICE][PK_T_FLYING] = 2;
	table_types[PK_T_ICE][PK_T_DRAGON] = 2;
	table_types[PK_T_ICE][PK_T_STEEL] = 0.5;
	table_types[PK_T_ICE][PK_T_LIGHT] = 0.5;

	table_types[PK_T_FIGHT][PK_T_NORMAL] = 2;
	table_types[PK_T_FIGHT][PK_T_ICE] = 2;
	table_types[PK_T_FIGHT][PK_T_POISON] = 0.5;
	table_types[PK_T_FIGHT][PK_T_FLYING] = 0.5;
	table_types[PK_T_FIGHT][PK_T_PSYCHIC] = 0.5;
	table_types[PK_T_FIGHT][PK_T_BUG] = 0.5;
	table_types[PK_T_FIGHT][PK_T_ROCK] = 2;
	table_types[PK_T_FIGHT][PK_T_GHOST] = 0;
	table_types[PK_T_FIGHT][PK_T_DARK] = 2;
	table_types[PK_T_FIGHT][PK_T_STEEL] = 2;
	table_types[PK_T_FIGHT][PK_T_FAIRY] = 0.5;
	table_types[PK_T_FIGHT][PK_T_LIGHT] = 0.5;


	table_types[PK_T_POISON][PK_T_GRASS] = 2;
	table_types[PK_T_POISON][PK_T_POISON] = 0.5;
	table_types[PK_T_POISON][PK_T_GROUND] = 0.5;
	table_types[PK_T_POISON][PK_T_ROCK] = 0.5;
	table_types[PK_T_POISON][PK_T_GHOST] = 0.5;
	table_types[PK_T_POISON][PK_T_STEEL] = 0;
	table_types[PK_T_POISON][PK_T_FAIRY] = 2;
	table_types[PK_T_POISON][PK_T_SUGAR] = 2;

	table_types[PK_T_GROUND][PK_T_GRASS] = 0.5;
	table_types[PK_T_GROUND][PK_T_FIRE] = 2;
	table_types[PK_T_GROUND][PK_T_ELECTRIC] = 2;
	table_types[PK_T_GROUND][PK_T_POISON] = 2;
	table_types[PK_T_GROUND][PK_T_FLYING] = 0;
	table_types[PK_T_GROUND][PK_T_BUG] = 0.5;
	table_types[PK_T_GROUND][PK_T_ROCK] = 2;
	table_types[PK_T_GROUND][PK_T_STEEL] = 2;

	table_types[PK_T_FLYING][PK_T_GRASS] = 2;
	table_types[PK_T_FLYING][PK_T_ELECTRIC] = 0.5;
	table_types[PK_T_FLYING][PK_T_FIGHT] = 2;
	table_types[PK_T_FLYING][PK_T_BUG] = 2;
	table_types[PK_T_FLYING][PK_T_ROCK] = 0.5;
	table_types[PK_T_FLYING][PK_T_STEEL] = 0.5;
	table_types[PK_T_FLYING][PK_T_LIGHT] = 0.5;
	table_types[PK_T_FLYING][PK_T_PLASTIC] = 0.5;

	table_types[PK_T_PSYCHIC][PK_T_FIGHT] = 2;
	table_types[PK_T_PSYCHIC][PK_T_POISON] = 2;
	table_types[PK_T_PSYCHIC][PK_T_PSYCHIC] = 0.5;
	table_types[PK_T_PSYCHIC][PK_T_DARK] = 0;
	table_types[PK_T_PSYCHIC][PK_T_STEEL] = 0.5;
	table_types[PK_T_PSYCHIC][PK_T_LIGHT] = 0.5;
	table_types[PK_T_PSYCHIC][PK_T_SUGAR] = 0.5;
	table_types[PK_T_PSYCHIC][PK_T_PLASTIC] = 2;

	table_types[PK_T_BUG][PK_T_GRASS] = 2;
	table_types[PK_T_BUG][PK_T_FIRE] = 0.5;
	table_types[PK_T_BUG][PK_T_FIGHT] = 0.5;
	table_types[PK_T_BUG][PK_T_POISON] = 0.5;
	table_types[PK_T_BUG][PK_T_FLYING] = 0.5;
	table_types[PK_T_BUG][PK_T_PSYCHIC] = 2;
	table_types[PK_T_BUG][PK_T_GHOST] = 0.5;
	table_types[PK_T_BUG][PK_T_DARK] = 2;
	table_types[PK_T_BUG][PK_T_STEEL] = 0.5;
	table_types[PK_T_BUG][PK_T_FAIRY] = 0.5;
	table_types[PK_T_BUG][PK_T_PLASTIC] = 0.5;

	table_types[PK_T_ROCK][PK_T_FIRE] = 2;
	table_types[PK_T_ROCK][PK_T_ICE] = 2;
	table_types[PK_T_ROCK][PK_T_FIGHT] = 0.5;
	table_types[PK_T_ROCK][PK_T_GROUND] = 0.5;
	table_types[PK_T_ROCK][PK_T_FLYING] = 2;
	table_types[PK_T_ROCK][PK_T_BUG] = 2;
	table_types[PK_T_ROCK][PK_T_STEEL] = 0.5;

	table_types[PK_T_GHOST][PK_T_NORMAL] = 0;
	table_types[PK_T_GHOST][PK_T_PSYCHIC] = 2;
	table_types[PK_T_GHOST][PK_T_GHOST] = 2;
	table_types[PK_T_GHOST][PK_T_DARK] = 0.5;
	table_types[PK_T_GHOST][PK_T_LIGHT] = 0;
	table_types[PK_T_GHOST][PK_T_SUGAR] = 2;

	table_types[PK_T_DRAGON][PK_T_DRAGON] = 2;
	table_types[PK_T_DRAGON][PK_T_STEEL] = 0.5;
	table_types[PK_T_DRAGON][PK_T_FAIRY] = 0;
	table_types[PK_T_DRAGON][PK_T_LIGHT] = 0.5;

	table_types[PK_T_DARK][PK_T_FIGHT] = 0.5;
	table_types[PK_T_DARK][PK_T_PSYCHIC] = 2;
	table_types[PK_T_DARK][PK_T_GHOST] = 2;
	table_types[PK_T_DARK][PK_T_DARK] = 0.5;
	table_types[PK_T_DARK][PK_T_FAIRY] = 0.5;
	table_types[PK_T_DARK][PK_T_LIGHT] = 2;
	table_types[PK_T_DARK][PK_T_SUGAR] = 0.5;

	table_types[PK_T_STEEL][PK_T_FIRE] = 0.5;
	table_types[PK_T_STEEL][PK_T_WATER] = 0.5;
	table_types[PK_T_STEEL][PK_T_ELECTRIC] = 0.5;
	table_types[PK_T_STEEL][PK_T_ICE] = 2;
	table_types[PK_T_STEEL][PK_T_ROCK] = 2;
	table_types[PK_T_STEEL][PK_T_STEEL] = 0.5;
	table_types[PK_T_STEEL][PK_T_FAIRY] = 2;
	table_types[PK_T_STEEL][PK_T_LIGHT] = 2;
	table_types[PK_T_STEEL][PK_T_PLASTIC] = 2;

	table_types[PK_T_FAIRY][PK_T_FIRE] = 0.5;
	table_types[PK_T_FAIRY][PK_T_FIGHT] = 2;
	table_types[PK_T_FAIRY][PK_T_POISON] = 0.5;
	table_types[PK_T_FAIRY][PK_T_DRAGON] = 2;
	table_types[PK_T_FAIRY][PK_T_DARK] = 2;
	table_types[PK_T_FAIRY][PK_T_STEEL] = 0.5;
	table_types[PK_T_FAIRY][PK_T_SUGAR] = 0.5;
	table_types[PK_T_FAIRY][PK_T_PLASTIC] = 0.5;

	table_types[PK_T_LIGHT][PK_T_NORMAL] = 0.5;
	table_types[PK_T_LIGHT][PK_T_GRASS] = 0.5;
	table_types[PK_T_LIGHT][PK_T_FIRE] = 0;
	table_types[PK_T_LIGHT][PK_T_ELECTRIC] = 0.5;
	table_types[PK_T_LIGHT][PK_T_ICE] = 2;
	table_types[PK_T_LIGHT][PK_T_BUG] = 0.5;
	table_types[PK_T_LIGHT][PK_T_ROCK] = 0.5;
	table_types[PK_T_LIGHT][PK_T_GHOST] = 2;
	table_types[PK_T_LIGHT][PK_T_DARK] = 2;
	table_types[PK_T_LIGHT][PK_T_LIGHT] = 0.5;

	table_types[PK_T_SUGAR][PK_T_NORMAL] = 2;
	table_types[PK_T_SUGAR][PK_T_FIRE] = 0.5;
	table_types[PK_T_SUGAR][PK_T_WATER] = 0.5;
	table_types[PK_T_SUGAR][PK_T_FIGHT] = 2;
	table_types[PK_T_SUGAR][PK_T_PSYCHIC] = 2;
	table_types[PK_T_SUGAR][PK_T_ROCK] = 0.5;
	table_types[PK_T_SUGAR][PK_T_DRAGON] = 0.5;
	table_types[PK_T_SUGAR][PK_T_STEEL] = 0;
	table_types[PK_T_SUGAR][PK_T_FAIRY] = 2;
	table_types[PK_T_SUGAR][PK_T_LIGHT] = 0.5;

	table_types[PK_T_PLASTIC][PK_T_GRASS] = 2;
	table_types[PK_T_PLASTIC][PK_T_FIRE] = 0.5;
	table_types[PK_T_PLASTIC][PK_T_WATER] = 2;
	table_types[PK_T_PLASTIC][PK_T_ELECTRIC] = 2;
	table_types[PK_T_PLASTIC][PK_T_POISON] = 0.5;
	table_types[PK_T_PLASTIC][PK_T_GROUND] = 2;
	table_types[PK_T_PLASTIC][PK_T_ROCK] = 0.5;
	table_types[PK_T_PLASTIC][PK_T_DRAGON] = 0.5;
	table_types[PK_T_PLASTIC][PK_T_STEEL] = 0.5;
	table_types[PK_T_PLASTIC][PK_T_PLASTIC] = 0.5;
}