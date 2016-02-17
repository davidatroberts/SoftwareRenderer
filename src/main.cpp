#include <iostream>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "selene.h"
#include "Debug.hpp"
#include "Graphics.hpp"
#include "Lighting.hpp"
#include "LuaUtils.hpp"
#include "Matrix.hpp"
#include "Model.hpp" 
#include "Pipeline.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "Vector.hpp"

#define SCREEN_WIDTH 	320 
#define SCREEN_HEIGHT 	240
#define SCREEN_BPP 		16

#define UP_BTN 				SDLK_UP
#define DOWN_BTN 			SDLK_DOWN
#define LEFT_BTN 			SDLK_LEFT
#define RIGHT_BTN 			SDLK_RIGHT
#define A_BTN 				SDLK_LCTRL
#define B_BTN 				SDLK_LALT
#define X_BTN 				SDLK_SPACE
#define Y_BTN 				SDLK_LSHIFT
#define LEFT_SHOULDER_BTN 	SDLK_TAB
#define RIGHT_SHOULDER_BTN 	SDLK_BACKSPACE
#define SELECT_BTN 			SDLK_ESCAPE
#define START_BTN 			SDLK_RETURN

bool quit = false;

// view settings
Vector camera_pos(0.0f, 0.0f, 10.0f);
Vector target(0.0f, 0.0f, 0.0f);
Vector up(0.0f, 1.0f, 0.0f);

float rotate_y = 90.0f;
float rotate_x = 0.0f;
float rotate_light_y = 0.0;

Vector light_pos(2.4, 0, 0);

// calculating FPS
int frame_count = 0;
float fps = 0;
Timer fps_timer;	
Timer caption_update_timer;	

void handle_event(const SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SELECT_BTN:
				break;
			case START_BTN:
				// exit if start was pressed
				quit = true;
				break;
			case RIGHT_BTN:
				light_pos.x +=0.2;
				break;
			case LEFT_BTN:
				light_pos.x -=0.2;
				break;
			case UP_BTN:
				light_pos.y +=0.2;
				break;
			case DOWN_BTN:
				light_pos.y -=0.2;
				break;
			case A_BTN:
				light_pos.z +=0.2;
				break;
			case B_BTN:
				light_pos.z -=0.2;
				break;
			default:
				break;
		}
	}
}

int main(int argc, char *argv[]) {
	// check for all arguments
	if (argc < 2) {
		std::cerr << "No scene file given" << std::endl;
		return 1;
	}

	// load the scene file
	sel::State scene;
	lu::initialise(scene);
	lu::initialise_model(scene);
	if (!scene.Load(std::string(argv[1]))) {
		std::cerr << "Error loading scene file" << std::endl;
		return 1;
	}

	// add the lights to the scene
	std::vector<std::shared_ptr<lighting::Light>> lights;
	lu::read_obj_array<lighting::PointLight, lighting::Light>(scene, lights, 
		"point_lights");
	lu::read_obj_array<lighting::DirectionalLight, lighting::Light>(scene, lights, 
		"directional_lights");
	lu::read_obj_array<lighting::SpotLight, lighting::Light>(scene, lights, 
		"spot_lights");

	// load the models
	std::vector<std::shared_ptr<model::Model>> models;
	lu::read_obj_array<model::Model, model::Model>(scene, models, "models");
	
	// init SDL
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) == -1) {
		std::cerr << "Failed initialize SDL" << std::endl;
		return 1;
	}

	// setup the screen
	SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 
		SCREEN_BPP, SDL_SWSURFACE);
	if (!screen) {
		std::cerr << "Failed to initialize SDL video mode" << std::endl;
		return 1;
	}

	// setup text output
	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialize TTF" << std::endl;
		return 1;
	}

	// load the font
	TTF_Font *font = TTF_OpenFont("../assets/font.ttf", 14);
	if (!font) {
		std::cerr << "Failed to load the font" << TTF_GetError() << std::endl;
		return 1;
	}

	// hide the cursor
	SDL_ShowCursor(SDL_DISABLE);

	// update the screen
	if (SDL_Flip(screen) == -1) {
		std::cerr << "Failed to flip the screen" << std::endl;
		return 1;
	}

	// create the Graphics to render
	SDL_PixelFormat* pixel_format = screen->format;
	Graphics graphics((uint16_t*)screen->pixels, SCREEN_WIDTH, SCREEN_HEIGHT,
		pixel_format);

	// create Text to render
	SDL_Colour font_colour = {255, 255, 255};
	Text text(screen);

	// view transform
	Matrix<float> projection = Matrix<float>::perspective(
		0.78f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
		0.01f, 1.0f);

	// camera transform
	Matrix<float> view = Matrix<float>::lookat(camera_pos, 
		target, up);

	// create the model
	// model::Model mesh = model::cube();
	// model::Model mesh = model::octahedron();
	// model::Model mesh = model::sphere(3);
	model::Model mesh = *models[0].get();
	mesh.surface_attribute =  {
		Vector(0.0, 0.0, 1.0),	// ambient
		Vector(0.0, 0.0, 1.0), 	// diffuse
		Vector(0.0, 0.0, 0.5),	// specular
		0.01f 					// shineness
	};

	// set the model position
	Vector mesh_position(0.0f, 0.0f, 0.0f);

	// timing
	uint32_t old_time, current_time;
	float dt = 0.0f;
	current_time = SDL_GetTicks();

	// start the frame timer
	fps_timer.start();

	// start the update timer
	caption_update_timer.start();

	// event loop
	while (!quit) {
		// update the frame
		frame_count++;

		// update time
		old_time = current_time;
		current_time = SDL_GetTicks();
		dt = (current_time - old_time) / 1000.0f;

		// handle events
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			handle_event(event);
		}

		// world model transform
		Matrix<float> tm = Matrix<float>::translate(
			mesh_position.x, mesh_position.y, mesh_position.z);
		// rotate_y += (20.0f*dt);
		Matrix<float> rmy = Matrix<float>::rotate_y(rotate_y);
		Matrix<float> rmx = Matrix<float>::rotate_x(rotate_x); 
		Matrix<float> model = ((rmy*rmx)*tm);

		// update light position
		rotate_light_y += (5.0f*dt);
		Matrix<float> lrm = Matrix<float>::rotate_y(rotate_light_y);
		lights[0]->view_position = lrm.mult_vector(light_pos);

		// model view matrix
		Matrix <float> mv = model * view;

		// projection transform
		Matrix<float> mvp = mv * projection;

		// inverse model transform
		Matrix<float> model_inv = model.inverse();

		// camera position in model space
		Vector camera_pos_model = model_inv.mult_vector(camera_pos);

		// copy of original
		model::Model visible_model = mesh;

		// backface culling
		visible_model = pipeline::backface_cull(mesh, camera_pos_model);

		// transform vertices
		pipeline::transform_vertices(visible_model, mvp);

		// calculate lighting (if any)
		if (lights.size() > 0) {
			// calculate transpose of inverse mvp matrix
			Matrix<float> mvp_inv = mvp.inverse();
			Matrix<float> mvp_inv_tra = mvp_inv.transpose();

			// transform normals
			Matrix<float>::transform_vertices(visible_model.triangle_normals, 
				mvp_inv_tra);
			Vector::project_to_3d(visible_model.triangle_normals);

			// transform face centers
			Matrix<float>::transform_vertices(visible_model.triangle_centers,
				mvp);
			Vector::project_to_3d(visible_model.triangle_centers);

			// calculate lighting
			std::vector<lighting::LightResult> light_results = 
				lighting::calculate_lights(lights, visible_model);

			// transform lightresults to colour
			std::vector<SDL_Color> light_colours = 
				lighting::lightresults_to_colours(light_results);

			// replace visible model colours with lighted colours
			visible_model.colours = light_colours;
		}

		// map to screen coordinates
		std::vector<Fragment> frags = pipeline::to_screen_coordinates(
			graphics, visible_model);

		// lock screen
		if (SDL_MUSTLOCK(screen))
			SDL_LockSurface(screen);

		// clear the old screen
		graphics.clear();

		// clear the old depth buffer
		graphics.clear_zbuffer();

		// rasterise the triangles
		pipeline::rasterise(graphics, visible_model, frags);

		// calculate FPS
		if (caption_update_timer.ticks() > 1000) {
			fps = ((float)frame_count /
				((float)fps_timer.ticks() / 1000.0f));
		}
		std::stringstream msg_str;
		msg_str << "FPS: " << fps;
		text.render_string(0, 0, font, font_colour, msg_str.str()); 

		// display angle
		std::stringstream info_str;
		info_str << "light x:" << lights[0]->view_position.x << 
			" y: " << lights[0]->view_position.y << " z: " 
			<< lights[0]->view_position.z << std::endl;
		text.render_string(0, 15, font, font_colour, info_str.str());

		// unlock screen
		if (SDL_MUSTLOCK(screen))
			SDL_UnlockSurface(screen);

		// update the screen
		if (SDL_Flip(screen) == -1) {
			std::cerr << "Failed to flip the screen" << std::endl;
			return 1;
		}
	}

	// quit SDL
	SDL_Quit();

	return 0;
}