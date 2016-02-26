#ifndef CHAI_UTIL
#define CHAI_UTIL

#include <chaiscript/chaiscript.hpp>
#include "Lighting.hpp"
#include "Model.hpp"
#include "Vector.hpp"

namespace ch {
  void initialise(chaiscript::ChaiScript &chai) {
    chai.add(chaiscript::user_type<Vector>(), "Vector4");
    chai.add(chaiscript::constructor<Vector(float, float, float, float)>(),
      "Vector4");
    chai.add(chaiscript::fun(&Vector::x), "x");
    chai.add(chaiscript::fun(&Vector::y), "y");
    chai.add(chaiscript::fun(&Vector::z), "z");
    chai.add(chaiscript::fun(&Vector::w), "w");

    chai.add(chaiscript::user_type<lighting::Attenuation>(), "Attenuation");
    chai.add(chaiscript::constructor<lighting::Attenuation(
      float, float, float)>(), "Attenuation");

    chai.add(chaiscript::user_type<lighting::Light>(), "Light");
    chai.add(chaiscript::fun(&lighting::Light::model_position),
      "model_position");

    chai.add(chaiscript::user_type<lighting::PointLight>(), "PointLight");
    chai.add(chaiscript::base_class<lighting::Light, lighting::PointLight>());
    chai.add(chaiscript::constructor<lighting::PointLight(Vector, Vector,
      Vector, Vector, lighting::Attenuation)>(), "PointLight");

    chai.add(chaiscript::user_type<lighting::DirectionalLight>(),
      "DirectionalLight");
    chai.add(chaiscript::base_class<lighting::Light,
      lighting::DirectionalLight>());
    chai.add(chaiscript::constructor<lighting::DirectionalLight(Vector,
      Vector, Vector, Vector)>(), "DirectionalLight");

    chai.add(chaiscript::user_type<lighting::SpotLight>(), "SpotLight");
    chai.add(chaiscript::base_class<lighting::Light, lighting::SpotLight>());
    chai.add(chaiscript::constructor<lighting::SpotLight(Vector, Vector,
      Vector, Vector, lighting::Attenuation, Vector, float, float)>(),
      "SpotLight");

    chai.add(chaiscript::bootstrap::standard_library::vector_type<
  		std::vector<std::shared_ptr<lighting::Light>>>("LightList"));

    chai.add(chaiscript::user_type<lighting::Surface>(), "Surface");
    chai.add(chaiscript::constructor<lighting::Surface(Vector, Vector,
      Vector, float)>(), "Surface");
    chai.add(chaiscript::fun(&lighting::Surface::operator=), "=");


    // Model
    chai.add(chaiscript::user_type<model::Model>(), "Model");
    chai.add(chaiscript::fun(&model::Model::surface_attribute),
      "surface_attribute");

    chai.add(chaiscript::bootstrap::standard_library::vector_type<
      std::vector<model::Model>>("ModelList"));

    chai.add(chaiscript::fun(&model::cube), "make_cube");
    chai.add(chaiscript::fun(&model::octahedron), "make_octahedron");
    chai.add(chaiscript::fun(&model::sphere), "make_sphere");

  }
}

#endif
