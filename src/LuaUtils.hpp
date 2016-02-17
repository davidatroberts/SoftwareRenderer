#ifndef LuaUtils
#define LuaUtils

#include "selene.h"
#include "Lighting.hpp"
#include "Model.hpp"
#include "Vector.hpp"

using namespace lighting;

namespace lu {
	int table_size(sel::State &state, std::string tbl_name) {
		std::string cmd = "tbl_size = #" + tbl_name;
		state(cmd.c_str());
		int tbl_size = state["tbl_size"];

		return tbl_size;
	}

	void initialise(sel::State &state) {
		state["Vector"].SetClass<Vector, double, double, double, double>();
		state["Attenuation"].SetClass<Attenuation, double,
			double, double>();
		state["DirectionalLight"].SetClass<lighting::DirectionalLight,
			Vector, Vector, Vector, Vector>();
		state["PointLight"].SetClass<lighting::PointLight,
			Vector, Vector, Vector, Vector, Attenuation>();
		state["PointLight"].SetClass<lighting::SpotLight, 
			Vector, Vector, Vector, Vector, Attenuation, Vector,
			double, double>();
		// state["Surface"].SetClass<lighting::Surface, Vector, Vector, Vector, 
		// 	double>();
	}

	void initialise_model(sel::State &state) {
		state["Model"].SetClass<model::Model>();

		state["make_cube"] = &model::cube;
		state["make_octahedron"] = &model::octahedron;
		state["make_sphere"] = &model::sphere;
	}

	template<typename T, typename BaseT>
	void read_obj_array(sel::State &state, 
		std::vector<std::shared_ptr<BaseT>> &arr, std::string tbl_name) {
		// get the table size of the arr
		int tbl_size = table_size(state, tbl_name);

		// read the lights
		for (int i=1; i<=tbl_size; i++) {
			auto obj_sel = state[tbl_name.c_str()][i];

			sel::Pointer<T> obj_ptr = obj_sel;
			std::shared_ptr<BaseT> obj(std::make_shared<T>(*obj_ptr.get()));

			arr.push_back(obj);
		}
	}
}

#endif