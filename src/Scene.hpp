#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "Model.hpp"

namespace scene {

  // base class for light
  class SceneObject;
  class Component {
  public:
    Component();

    virtual void update(SceneObject &object, float dt) = 0;

    virtual ~Component() = 0;
  };

  // container object for objects in the scene
  class SceneObject {
  public:
    SceneObject();

    void update(float dt);
    void add_component(std::shared_ptr<Component> component);

    ~SceneObject();

  private:
    std::vector<std::shared_ptr<Component>> components;
  };

  // compoent for rendering 3D models
  class RenderModelComponent: public Component {
  public:
    RenderModelComponent(model::Model component_model);

    void update(SceneObject &object, float dt);

    ~RenderModelComponent();

  private:
    model::Model component_model;
  };
}

#endif
