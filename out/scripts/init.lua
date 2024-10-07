
campfire_tx_0 = ul_get_texture("obj", "campfire0")
campfire_tx_1 = ul_get_texture("obj", "campfire1")
campfire_tx_2 = ul_get_texture("obj", "campfire2")
campfire_tx_3 = ul_get_texture("obj", "campfire3")
campfire_tx_4 = ul_get_texture("obj", "campfire4")

cooldown = 0
idx = 0

function campfire_tick(x, y, self)
	cooldown = cooldown - 1
	if cooldown <= 0 then
		cooldown = 7
		idx = idx + 1
		if idx > 4 then
			idx = 0
		end
		if idx == 0 then ul_set_texture(self, campfire_tx_0) end
		if idx == 1 then ul_set_texture(self, campfire_tx_1) end
		if idx == 2 then ul_set_texture(self, campfire_tx_2) end
		if idx == 3 then ul_set_texture(self, campfire_tx_3) end
		if idx == 4 then ul_set_texture(self, campfire_tx_4) end
	end
end


ul_register_obj("grass", "obj", "grass1", 0);
ul_register_obj("campfire", "obj", "campfire1", 0, nil, nil, nil, campfire_tick);

