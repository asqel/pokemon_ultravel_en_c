

## object format
	is_air (1 byte)
	if (is_air == 0)
		object_id_idx (8 bytes) (index in the header strings)
		object_mod_id_idx (8 bytes) (index in the header strings)

## Worlds format

world folders location:
	if mod_name == NULL -> game_dir/worlds/world_name/
	else -> game_dir/mods/mod_name/worlds/world_name/

files inside world folder:
	data : contains info about the world (e.g. .is_outside, .background)
	c_X_Y_ : chunk(X, Y) data

data file:
	1 byte (.is_outside)
	1 byte (.background.r)
	1 byte (.background.g)
	1 byte (.background.b)

chunk files c_X_Y_:
	MAGIC_NUMBER (as str)
	SAVE_MAGIC_NUMBER (2 byte)
	header:
		nbr of strings (8 bytes)
		strings (null termiated)
	
	background_obj  (as objects)

	objects (as objects)
	
	objects_foreground (as objects)
	
	dyn_objects (as objects)
	
	dyn_objects_foreground (as objects)

	

species_info:
	is_genderless
	male_ratio (/100)
	sprite {
		sprite (male/female)
		sprite (male) / sprite (female)
		sprite() (custom)
	}
	xp
	base stats
	species name
	move_sets (2 move set can be the same)
	abilities
	hidden abilities
	catch rate
	egg_groups
	'egg_type' (A.K.A. nombre de pas pour eclore)
	types
	special_types()
	evolution_info

evolution_info:
	evolution type
	default_evolution
	femal_evolution
	get_evolution()

pokemon_info:
	gender
	shiny
	ev
	iv
	DO
	surname
	hp
	lvl
	ability
	attacks
	// extra data can be used by
	// 	special types to get the type dynamicaly
	//  custom sprite 
	extra data 1
	extra data 2
	extra data 3
	extra data 4
	extra data 5


## tx_files
a tx file need a png file with the same name to work
### example
	textures.tx
	textures.png

a tx file used to cut and resize and name parts of an image \
each line of a tx file is either an instruction or a comment \
a comment is a line starting with a dash '-'
### example
	- this is a comment
an instruction is composoded of 6 number and an identifier \
it is of this form \
X Y W H N_W N_H $ identifier
X, Y : the coordinate in the image of the texture
W, H : dimesion of the texture in the image
N_W, N_H : the new dimension to which the texture will be resized
identifier : the name of the texture
### example 
	0 0 20 20 60 60 $ grass
the category of the texture is the name of the foler in which the tx file is in



foreground_obj	| on_draw tick
objects			| on_draw tick interact on_walk
background_obj	| on_draw 				on_walk