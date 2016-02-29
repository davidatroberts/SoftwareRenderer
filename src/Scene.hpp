#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "Lighting.hpp"
#include "Matrix.hpp"
#include "Model.hpp"
#include "Vector.hpp"

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

    Vector position;
    Vector rotation;
    Vector scale;

  private:
    std::vector<std::shared_ptr<Component>> components_;
  };

  // compoent for rendering 3D models
  class RenderModelComponent: public Component {
  public:
    RenderModelComponent(model::Model component_model,
      Vector& camera_position, Matrix<float>& view_projection_,
      std::vector<std::shared_ptr<lighting::Light>>& lights,
      std::vector<model::Model>& model_list);

    void update(SceneObject &object, float dt);

    ~RenderModelComponent();

  private:
    model::Model component_model_;
    Vector& camera_position_;
    Matrix<float>& view_projection_;
    std::vector<std::shared_ptr<lighting::Light>>& lights_;
    std::vector<model::Model>& model_list_;
  };
}

#endif
