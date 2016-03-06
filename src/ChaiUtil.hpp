#ifndef CHAI_UTIL
#define CHAI_UTIL

#include <chaiscript/chaiscript.hpp>
#include "Lighting.hpp"
#include "Matrix.hpp"
#include "Model.hpp"
#include "Scene.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Vector2.hpp"

namespace ch {
  void initialise(chaiscript::ChaiScript &chai) {
    chai.add(chaiscript::user_type<Vector>(), "Vector4");
    chai.add(chaiscript::constructor<Vector(float, float, float, float)>(),
      "Vector4");
    chai.add(chaiscript::fun(&Vector::x), "x");
    chai.add(chaiscript::fun(&Vector::y), "y");
    chai.add(chaiscript::fun(&Vector::z), "z");
    chai.add(chaiscript::fun(&Vector::w), "w");
    chai.add(chaiscript::fun(&Vector::operator=), "=");

		chai.add(chaiscript::user_type<Vector2>(), "Vector2");
		chai.add(chaiscript::constructor<Vector2(float, float)>(),
			"Vector2");
		chai.add(chaiscript::fun(&Vector2::x), "x");
		chai.add(chaiscript::fun(&Vector2::y), "y");
		chai.add(chaiscript::bootstrap::standard_library::vector_type<
  		std::vector<Vector2>>("Vector2List"));

    chai.add(chaiscript::user_type<Matrix<float>>(), "Matrix");
    chai.add(chaiscript::constructor<Matrix<float>()>(), "Matrix");
    chai.add(chaiscript::fun(&Matrix<float>::mult_vector), "mult_vector");
    chai.add(chaiscript::fun(&Matrix<float>::transpose), "transpose");
    chai.add(chaiscript::fun(&Matrix<float>::identity), "Matrix_identity");
    chai.add(chaiscript::fun(&Matrix<float>::translate), "Matrix_translate");
    chai.add(chaiscript::fun(&Matrix<float>::rotate_x), "Matrix_rotate_x");
    chai.add(chaiscript::fun(&Matrix<float>::rotate_y), "Matrix_rotate_y");
    chai.add(chaiscript::fun(&Matrix<float>::rotate_z), "Matrix_rotate_z");
    chai.add(chaiscript::fun(&Matrix<float>::scale), "Matrix_scale");

    chai.add(chaiscript::user_type<lighting::Attenuation>(), "Attenuation");
    chai.add(chaiscript::constructor<lighting::Attenuation(
      float, float, float)>(), "Attenuation");

    chai.add(chaiscript::user_type<lighting::Light>(), "Light");
    chai.add(chaiscript::fun(&lighting::Light::model_position),
      "model_position");
    chai.add(chaiscript::fun(&lighting::Light::view_position),
      "view_position");

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

		// Texture
		chai.add(chaiscript::user_type<Texture>(), "Texture");
		chai.add(chaiscript::constructor<Texture()>(), "Texture");
		chai.add(chaiscript::fun(&Texture::load), "load");

    // Model
    chai.add(chaiscript::user_type<model::Model>(), "Model");
    chai.add(chaiscript::fun(&model::Model::surface_attribute),
      "surface_attribute");
		chai.add(chaiscript::fun(&model::Model::texture), "texture");
		chai.add(chaiscript::fun(&model::Model::uv_coordinates),
			"uv_coordinates");

    chai.add(chaiscript::bootstrap::standard_library::vector_type<
      std::vector<model::Model>>("ModelList"));

    chai.add(chaiscript::fun(&model::cube), "make_cube");
    chai.add(chaiscript::fun(&model::octahedron), "make_octahedron");
    chai.add(chaiscript::fun(&model::sphere), "make_sphere");

    // Scene
    chai.add(chaiscript::user_type<scene::Component>(), "Component");

    chai.add(chaiscript::user_type<scene::SceneObject>(), "SceneObject");
    chai.add(chaiscript::constructor<scene::SceneObject()>(), "SceneObject");
    chai.add(chaiscript::fun(&scene::SceneObject::add_component),
      "add_component");
    chai.add(chaiscript::fun(&scene::SceneObject::position), "position");
    chai.add(chaiscript::fun(&scene::SceneObject::scale), "scale");
    chai.add(chaiscript::fun(&scene::SceneObject::rotation), "rotation");

    chai.add(chaiscript::bootstrap::standard_library::vector_type<
      std::vector<scene::SceneObject>>("SceneList"));

    chai.add(chaiscript::user_type<scene::RenderModelComponent>(),
      "RenderModelComponent");
    chai.add(chaiscript::base_class<scene::Component,
      scene::RenderModelComponent>());
    chai.add(chaiscript::constructor<scene::RenderModelComponent(
      model::Model, Vector&, Matrix<float>&,
      std::vector<std::shared_ptr<lighting::Light>>&,
      std::vector<model::Model>&)>(), "RenderModelComponent");
  }
}

#endif
