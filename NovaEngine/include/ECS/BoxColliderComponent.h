#pragma once
#include "ECS/Component.h"
#include "ECS/Transform.h"
#include "EngineUtilities/Vectors/Vector3.h"

class BoxColliderComponent : public Component {
public:
  // extents son las "medias medidas" (half-extents) desde el centro. 
  // Un cubo de 2x2x2 tendría extents de 1x1x1.
  EU::Vector3 extents = EU::Vector3(1.0f, 1.0f, 1.0f);
  EU::Vector3 centerOffset = EU::Vector3(0.0f, 0.0f, 0.0f);

  BoxColliderComponent() : Component(ComponentType::BOX_COLLIDER) {}
  ~BoxColliderComponent() = default;

	void
		init() override {};

  void 
    update(float deltaTime) override {}

  void 
    render(DeviceContext& deviceContext) override {}

	void
		destroy() override {};

  EU::TSharedPointer<Component> clone() const override {
    auto cloned = new BoxColliderComponent();
    cloned->extents = this->extents;
    cloned->centerOffset = this->centerOffset;
    return EU::TSharedPointer<Component>(cloned);
  }

  // Helper para obtener los límites de la caja en el mundo real
  void getWorldBounds(Transform* transform, EU::Vector3& outMin, EU::Vector3& outMax) {
    EU::Vector3 worldPos = transform->getPosition();
    // Sumamos el offset
    worldPos.x += centerOffset.x;
    worldPos.y += centerOffset.y;
    worldPos.z += centerOffset.z;

    // Calculamos Min y Max
    outMin = EU::Vector3(worldPos.x - extents.x, worldPos.y - extents.y, worldPos.z - extents.z);
    outMax = EU::Vector3(worldPos.x + extents.x, worldPos.y + extents.y, worldPos.z + extents.z);
  }
};