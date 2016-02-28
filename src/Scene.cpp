#include "Scene.hpp"

#include "Pipeline.hpp"

namespace scene {

Component::Component() {
}

Component::~Component() {
}

SceneObject::SceneObject() {
}

void SceneObject::update(float dt) {
  for (auto shared_ptr: components_) {
    shared_ptr->update(*this, dt);
  }
}

void SceneObject::add_component(std::shared_ptr<Component> component) {
  components_.push_back(component);
}

SceneObject::~SceneObject() {
}

RenderModelComponent::RenderModelComponent(model::Model component_model,
  Vector& camera_position, Matrix<float>& view_projection,
  std::vector<std::shared_ptr<lighting::Light>>& lights,
  std::vector<model::Model>& model_list)
:component_model_(component_model), camera_position_(camera_position),
view_projection_(view_projection), lights_(lights), model_list_(model_list) {
}

void RenderModelComponent::update(SceneObject &object, float dt) {
  // should be scripted
  Matrix<float> tm = Matrix<float>::translate(
    object.position.x, object.position.y, object.position.z
  );
  Matrix<float> rmz = Matrix<float>::rotate_z(object.rotation.z);
  Matrix<float> rmy = Matrix<float>::rotate_y(object.rotation.y);
  Matrix<float> rmx = Matrix<float>::rotate_x(object.rotation.x);

  Matrix<float> model = ((rmz*rmy*rmx)*tm);

  // projection transform
  Matrix<float> mvp = model * view_projection_;

  // inverse model
  Matrix<float> model_inv = model.inverse();

  // camera position in model space
  Vector camera_pos_model = model_inv.mult_vector(camera_position_);

  // backface culling
  model::Model visible_model = pipeline::backface_cull(component_model_,
    camera_pos_model);

  // transform the vertices
  pipeline::transform_vertices(visible_model, mvp);

  // calculate the lighting
  if (lights_.size() > 0) {
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
      lighting::calculate_lights(lights_, visible_model);

    // transform lightresults to colour
    std::vector<SDL_Color> light_colours =
      lighting::lightresults_to_colours(light_results);

    // replace visible model colours with lighted colours
    visible_model.colours = light_colours;
  }

  // add to the global visible model list
  model_list_.push_back(visible_model);
}

RenderModelComponent::~RenderModelComponent() {
}

}
