#include "world.h"
#include "player.h"
#include "keys.h"
#include "uti.h"

clothe_t default_clothes[CLOTHE_TYPE_LEN] = {0};

void init_default_feet() {
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_UP][0] = get_texture("costum_feet", "default_u0");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_UP][1] = get_texture("costum_feet", "default_u1");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_UP][2] = get_texture("costum_feet", "default_u2");

	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_RIGHT][0] = get_texture("costum_feet", "default_r0");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_RIGHT][1] = get_texture("costum_feet", "default_r1");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_RIGHT][2] = get_texture("costum_feet", "default_r2");

	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_DOWN][0] = get_texture("costum_feet", "default_d0");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_DOWN][1] = get_texture("costum_feet", "default_d1");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_DOWN][2] = get_texture("costum_feet", "default_d2");

	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_LEFT][0] = get_texture("costum_feet", "default_l0");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_LEFT][1] = get_texture("costum_feet", "default_l1");
	default_clothes[CLOTHE_TYPE_FEET].frames[DIR_LEFT][2] = get_texture("costum_feet", "default_l2");
}

void init_default_hand() {
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_UP][0] = get_texture("costum_hand", "default_u0");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_UP][1] = get_texture("costum_hand", "default_u1");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_UP][2] = get_texture("costum_hand", "default_u2");

	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_RIGHT][0] = get_texture("costum_hand", "default_r0");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_RIGHT][1] = get_texture("costum_hand", "default_r1");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_RIGHT][2] = get_texture("costum_hand", "default_r2");

	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_DOWN][0] = get_texture("costum_hand", "default_d0");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_DOWN][1] = get_texture("costum_hand", "default_d1");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_DOWN][2] = get_texture("costum_hand", "default_d2");

	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_LEFT][0] = get_texture("costum_hand", "default_l0");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_LEFT][1] = get_texture("costum_hand", "default_l1");
	default_clothes[CLOTHE_TYPE_HAND].frames[DIR_LEFT][2] = get_texture("costum_hand", "default_l2");
}

void init_default_torso() {
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_UP][0] = get_texture("costum_torso", "default_u0");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_UP][1] = get_texture("costum_torso", "default_u1");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_UP][2] = get_texture("costum_torso", "default_u2");

	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_RIGHT][0] = get_texture("costum_torso", "default_r0");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_RIGHT][1] = get_texture("costum_torso", "default_r1");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_RIGHT][2] = get_texture("costum_torso", "default_r2");

	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_DOWN][0] = get_texture("costum_torso", "default_d0");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_DOWN][1] = get_texture("costum_torso", "default_d1");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_DOWN][2] = get_texture("costum_torso", "default_d2");

	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_LEFT][0] = get_texture("costum_torso", "default_l0");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_LEFT][1] = get_texture("costum_torso", "default_l1");
	default_clothes[CLOTHE_TYPE_TORSO].frames[DIR_LEFT][2] = get_texture("costum_torso", "default_l2");
}

void init_default_backpack() {
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_UP][0] = get_texture("costum_backpack", "default_u0");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_UP][1] = get_texture("costum_backpack", "default_u1");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_UP][2] = get_texture("costum_backpack", "default_u2");

	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_RIGHT][0] = get_texture("costum_backpack", "default_r0");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_RIGHT][1] = get_texture("costum_backpack", "default_r1");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_RIGHT][2] = get_texture("costum_backpack", "default_r2");

	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_DOWN][0] = get_texture("costum_backpack", "default_d0");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_DOWN][1] = get_texture("costum_backpack", "default_d1");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_DOWN][2] = get_texture("costum_backpack", "default_d2");

	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_LEFT][0] = get_texture("costum_backpack", "default_l0");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_LEFT][1] = get_texture("costum_backpack", "default_l1");
	default_clothes[CLOTHE_TYPE_BACKPACK].frames[DIR_LEFT][2] = get_texture("costum_backpack", "default_l2");
}

void init_default_head() {
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_UP][0] = get_texture("costum_head", "default_u0");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_UP][1] = get_texture("costum_head", "default_u1");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_UP][2] = get_texture("costum_head", "default_u2");

	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_RIGHT][0] = get_texture("costum_head", "default_r0");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_RIGHT][1] = get_texture("costum_head", "default_r1");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_RIGHT][2] = get_texture("costum_head", "default_r2");

	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_DOWN][0] = get_texture("costum_head", "default_d0");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_DOWN][1] = get_texture("costum_head", "default_d1");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_DOWN][2] = get_texture("costum_head", "default_d2");

	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_LEFT][0] = get_texture("costum_head", "default_l0");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_LEFT][1] = get_texture("costum_head", "default_l1");
	default_clothes[CLOTHE_TYPE_HEAD].frames[DIR_LEFT][2] = get_texture("costum_head", "default_l2");
}

int init_default_clothes() {
	init_default_feet();
	init_default_hand();
	init_default_torso();
	init_default_backpack();
	init_default_head();
	return 0;
}

int init_player_and_world(player_t *player, char *world_name) {
	player->cam_offset.x = 0;
	player->cam_offset.y = 0;
	player->offset.x = 0;
	player->offset.y = 0;
	player->pos = (vec2i_t){.x = 0, .y = 0};
	player->world.is_loaded = 0;
	player_change_world(player, "world_name", player->pos);
	for (int i = 0; i < CLOTHE_TYPE_LEN; i++)
		player->clothes[i] = (clothe_t){.id = 0};
	player->data = NULL;
	player->frame_idx = 0;
	player->team_idx = -1;
	player->dir = DIR_DOWN;
	player->is_moving = 0;
	player->moving_from = (vec2i_t){0, 0};
	player->frame_cooldown = 0;
	player->is_sprinting = 0;
	init_default_clothes();
	return 0;
}
void check_player_chunk(player_t *player) {

}

void tick_player(player_t *player) {
	if (player->is_moving) {
		if (player->dir == DIR_UP) {
			player->offset.y -= PLAYER_SPEED(*player);
			player->offset.y = UTI_MAX(-PLAYER_PX_SIZE, player->offset.y);
			if (player->frame_cooldown == 0) {
				player->frame_cooldown = FRAME_COOLDOWN_MAX(*player);
				player->frame_idx += 1;
				if (player->frame_idx >= 3)
					player->frame_idx = 0;
			}
			player->frame_cooldown -= 1;
			if (player->offset.y == -PLAYER_PX_SIZE) {
				player->offset.y = 0;
				player->offset.x = 0;
				player->pos.y -= 1;
				player->is_moving = 0;
			}
		}
		if (player->dir == DIR_DOWN) {
			player->offset.y += PLAYER_SPEED(*player);
			player->offset.y = UTI_MIN(PLAYER_PX_SIZE, player->offset.y);
			if (player->frame_cooldown == 0) {
				player->frame_cooldown = FRAME_COOLDOWN_MAX(*player);
				player->frame_idx += 1;
				if (player->frame_idx >= 3)
					player->frame_idx = 0;
			}
			player->frame_cooldown -= 1;
			if (player->offset.y == PLAYER_PX_SIZE) {
				player->offset.y = 0;
				player->offset.x = 0;
				player->pos.y += 1;
				player->is_moving = 0;
			}
		}
		if (player->dir == DIR_LEFT) {
			player->offset.x -= PLAYER_SPEED(*player);
			player->offset.x = UTI_MAX(-PLAYER_PX_SIZE, player->offset.x);
			if (player->frame_cooldown == 0) {
				player->frame_cooldown = FRAME_COOLDOWN_MAX(*player);
				player->frame_idx += 1;
				if (player->frame_idx >= 3)
					player->frame_idx = 0;
			}
			player->frame_cooldown -= 1;
			if (player->offset.x == -PLAYER_PX_SIZE) {
				player->offset.y = 0;
				player->offset.x = 0;
				player->pos.x -= 1;
				player->is_moving = 0;
			}
		}
		if (player->dir == DIR_RIGHT) {
			player->offset.x += PLAYER_SPEED(*player);
			player->offset.x = UTI_MIN(PLAYER_PX_SIZE, player->offset.x);
			if (player->frame_cooldown == 0) {
				player->frame_cooldown = FRAME_COOLDOWN_MAX(*player);
				player->frame_idx += 1;
				if (player->frame_idx >= 3)
					player->frame_idx = 0;
			}
			player->frame_cooldown -= 1;
			if (player->offset.x == PLAYER_PX_SIZE) {
				player->offset.y = 0;
				player->offset.x = 0;
				player->pos.x += 1;
				player->is_moving = 0;
			}
		}
		if (!player->is_moving) {
			player->frame_idx = 0;
			player->frame_cooldown = 0;
		}
		check_player_chunk(player);
	}

}

void player_go_up(player_t *player) {
	if (player->is_moving)
		return ;
	player->is_moving = 1;
	player->moving_from = player->pos;
	player->dir = DIR_UP;
	player->offset.x = 0;
	player->offset.y = 0;
}

void player_go_down(player_t *player) {
	if (player->is_moving)
		return ;
	player->is_moving = 1;
	player->moving_from = player->pos;
	player->dir = DIR_DOWN;
	player->offset.x = 0;
	player->offset.y = 0;
}

void player_go_left(player_t *player) {
	if (player->is_moving)
		return ;
	player->is_moving = 1;
	player->moving_from = player->pos;
	player->dir = DIR_LEFT;
	player->offset.x = 0;
	player->offset.y = 0;
}

void player_go_right(player_t *player) {
	if (player->is_moving)
		return ;
	player->is_moving = 1;
	player->moving_from = player->pos;
	player->dir = DIR_RIGHT;
	player->offset.x = 0;
	player->offset.y = 0;
}

#if !defined(WORLD_EDITOR)

void do_key_actions(player_t *player) {
	if (key_pressed[KEY_T_UP] && key_pressed[KEY_T_STAY] && !player->is_moving)
		player->dir = DIR_UP;
	else if (key_pressed[KEY_T_UP] && !player->is_moving)
		player_go_up(player);
	
	if (key_pressed[KEY_T_DOWN] && key_pressed[KEY_T_STAY] && !player->is_moving)
		player->dir = DIR_DOWN;
	else if (key_pressed[KEY_T_DOWN] && !player->is_moving)
		player_go_down(player);
	
	if (key_pressed[KEY_T_LEFT] && key_pressed[KEY_T_STAY] && !player->is_moving)
		player->dir = DIR_LEFT;
	else if (key_pressed[KEY_T_LEFT] && !player->is_moving)
		player_go_left(player);
	
	if (key_pressed[KEY_T_RIGHT] && key_pressed[KEY_T_STAY] && !player->is_moving)
		player->dir = DIR_RIGHT;
	else if (key_pressed[KEY_T_RIGHT] && !player->is_moving)
		player_go_right(player);

	if (key_pressed[KEY_T_SPRINT]) {
		player->is_sprinting = 1;
		DEBUG("%d %d\n", player->pos.x, player->pos.y);
	}
	else
		player->is_sprinting = 0;
}

#else

void do_key_actions(player_t *player) {

}

#endif

void player_change_world(player_t *player, char *name, vec2i_t pos) {
	free_world(player->world);
	player->pos = pos;
	load_world(name, &(player->world));
	vec2i_t chunk_pos = (vec2i_t){.x = player->pos.x / CHUNK_LEN, .y = player->pos.y / CHUNK_LEN};
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			load_chunk(
				&(player->world),
				(vec2i_t){.x = chunk_pos.x + i - 1, .y = chunk_pos.y + k - 1},
				&(player->world.loaded_chunks[i][k])
			);
		}
	}
}