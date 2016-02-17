-- Lights
point_lights = {}

directional_lights = {
	DirectionalLight.new(
		Vector.new(0.0, 0.0, 0.0, 0.0),
		Vector.new(1.0, 1.0, 1.0, 1.0),
		Vector.new(1.0, 1.0, 1.0, 1.0),
		Vector.new(1.0, 1.0, 1.0, 1.0)
	)
}

spot_lights = {}

-- Model
models = {
	-- make_cube()
	make_sphere(3)
}