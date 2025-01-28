
Campfire_tx_0 = Ul_get_texture("obj", "campfire0")
Campfire_tx_1 = Ul_get_texture("obj", "campfire1")
Campfire_tx_2 = Ul_get_texture("obj", "campfire2")
Campfire_tx_3 = Ul_get_texture("obj", "campfire3")
Campfire_tx_4 = Ul_get_texture("obj", "campfire4")

Cooldown = 0
Idx = 0

function Campfire_tick(x, y, self)
	Cooldown = Cooldown - 1
	if Cooldown <= 0 then
		Cooldown = 7
		Idx = Idx + 1
		if Idx > 4 then
			Idx = 0
		end
		if Idx == 0 then Ul_set_texture(self, Campfire_tx_0) end
		if Idx == 1 then Ul_set_texture(self, Campfire_tx_1) end
		if Idx == 2 then Ul_set_texture(self, Campfire_tx_2) end
		if Idx == 3 then Ul_set_texture(self, Campfire_tx_3) end
		if Idx == 4 then Ul_set_texture(self, Campfire_tx_4) end
	end
end


Ul_register_obj("grass", "obj", "grass1", 0);
Ul_register_obj("campfire", "obj", "campfire1", 1, nil, nil, nil, Campfire_tick);
Ul_register_obj("tree", "obj", "tree", 1);
Ul_new_animation("campfire", 7, Campfire_tx_0, Campfire_tx_1, Campfire_tx_2, Campfire_tx_3, Campfire_tx_4);
Ul_register_obj("tombstone", "obj", "tombstone", 1);
