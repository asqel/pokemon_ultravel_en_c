

## object format
	is_air (1 byte)
	if (is_air == 0)
		object_id_idx (8 bytes) (index in the header strings)
		object_mod_id_idx (8 bytes) (index in the header strings)
		data_key_len (8 byte)

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
	header:
		address background_obj (8 bytes)
		address objects (8 bytes)
		address objects_foreground (8 bytes)
		address dyn_objects (8 bytes)
		address dyn_objects_foreground (8 bytes)
		nbr of strings (8 bytes)
		strings (null termiated)
		background_obj  (as objects)
		objects (as objects)
		objects_foreground (as objects)
		dyn_objects (as objects)
		dyn_objects_foreground (as objects)

	