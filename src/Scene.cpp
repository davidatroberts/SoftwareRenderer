#include "Scene.hpp"

namespace scene {

Component::Component() {
}

Component::~Component() {
}

SceneObject::SceneObject() {
}

void SceneObject::update(float dt) {
  for (auto shared_ptr: components) {
    shared_ptr->update(*this, dt);
  }
}

void SceneObject::add_component(std::shared_ptr<Component> component) {
  components.push_back(component);
}

SceneObject::~SceneObject() {
}

RenderModelComponent::RenderModelComponent(model::Model component_model)
:component_model(component_model) {
}

void RenderModelComponent::update(SceneObject &object, float dt) {
}

RenderModelComponent::~RenderModelComponent() {
}

}
