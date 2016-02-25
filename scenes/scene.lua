-- Display Settings
display = {
	width  = 640,
	height = 480,
	bpp    = 16
}

-- Camera
camera = {
	position = Vector.new(0.0, 0.0, 10.0, 1.0),
	target   = Vector.new(0.0, 0.0, 0.0, 1.0),
	up       = Vector.new(0.0, 1.0, 0.0, 1.0)
}

-- Lights --
-- Point Light
point_lights = {}

-- Directional Light
directional_lights = {
	DirectionalLight.new(
		Vector.new(2.4, 0.0, 0.0, 0.0),
		Vector.new(1.0, 1.0, 1.0, 1.0),
		Vector.new(1.0, 1.0, 1.0, 1.0),
		Vector.new(1.0, 1.0, 1.0, 1.0)
	)
}

-- Spot Light
spot_lights = {}

-- Model
models = {
	-- make_cube()
	make_sphere(3)
}

-- updates the vector of lights
function update_lights(light_size)
	-- for i=0, light_count-1 do
	-- 	local light_ptr = atpos(0)
	-- 	local mx, my, mz, mw = get_model(light_ptr)
	-- end
end
