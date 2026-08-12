#pragma once
#include "ECS/Component.h"
#include "EngineUtilities/Vectors/Vector3.h"

class RigidbodyComponent : public Component {
public:
  EU::Vector3 velocity = EU::Vector3(0.0f, 0.0f, 0.0f);
  EU::Vector3 angularVelocity = EU::Vector3(0.0f, 0.0f, 0.0f); // Nueva velocidad rotacional

  float mass = 1.0f;
  bool useGravity = true;
  bool isKinematic = false;

  // Constraints estilo Unity
  bool freezePosX = false, freezePosY = false, freezePosZ = false;
  bool freezeRotX = false, freezeRotY = false, freezeRotZ = false;

  RigidbodyComponent() : Component(ComponentType::RIGIDBODY) {}
  ~RigidbodyComponent() = default;

  void
    init() override {};

  void
    update(float deltaTime) override {}

  void
    render(DeviceContext& deviceContext) override {}

  void
    destroy() override {};

  EU::TSharedPointer<Component> clone() const override {
    auto cloned = new RigidbodyComponent();
    cloned->velocity = this->velocity;
    cloned->angularVelocity = this->angularVelocity;
    cloned->useGravity = this->useGravity;
    cloned->isKinematic = this->isKinematic;
    cloned->freezePosX = this->freezePosX; cloned->freezePosY = this->freezePosY; cloned->freezePosZ = this->freezePosZ;
    cloned->freezeRotX = this->freezeRotX; cloned->freezeRotY = this->freezeRotY; cloned->freezeRotZ = this->freezeRotZ;
    return EU::TSharedPointer<Component>(cloned);
  }
};