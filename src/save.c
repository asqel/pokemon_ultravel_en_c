#include "world.h"
#include "types.h"
#include "uti.h"


/*
Object:
	is_air (1 Byte)
	if (!is_air) {
		id_idx (8 Byte)
		extra
		//extra: 
			bit 0: is_top_layer
			bit 1: has_hitbox
		data
	}

data:
	nbr_key_value_pairs (8 byte)
	key_values

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


//void bytes_append_uint(bytes *res, pk_uint_t x) {
//	res->val = realloc(res->val, sizeof(u8) * (res->len + 8));
//	for (int i = 0; i < 8; i++)
//		res->val[res->len + i] = 0;
//	memcpy(&(res->val[res->len]), &x, sizeof(pk_uint_t) > 8 ? 8 : sizeof(pk_uint_t));
//	res->len += 8;
//}
//
//void object_to_bytes(object_t *object, bytes *res, char ***strs, int *strs_len) {
//	res->len++;
//	res->val = realloc(res->val, sizeof(u8) * res->len);
//	res->val[res->len - 1] = 1;
//	if (object->id == NULL) {
//		res->val[res->len - 1] = 0;
//		return ;
//	}
//	bytes_append_uint(res, search_or_add_strs(strs, strs_len, object->id));
//	bytes_append_uint(res, search_or_add_strs(strs, strs_len, object->mod_id));
//	res->len++;
//	res->val = realloc(res->val, sizeof(u8) * res->len);
//	res->val[res->len - 1] = 0;
//	if (object->is_top_layer)
//		res->val[res->len - 1] |= 0b01;
//	if (object->has_hitbox)
//		res->val[res->len - 1] |= 0b10;
//	// TODO : implent save data
//	bytes_append_uint(res, 0); // considere 0 keys for now
//}