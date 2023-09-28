#include "CesiumTile.h"
#include "CalcBounds.h"
#include "CesiumTransforms.h"
#include "Components/PrimitiveComponent.h"
#include "VecMath.h"

bool UCesiumTile::TileBoundsOverlapsPrimitive(
    const UPrimitiveComponent* Other) const {
  if (IsValid(Other)) {
    return Bounds.GetBox().Intersect(Other->Bounds.GetBox()) &&
           Bounds.GetSphere().Intersects(Other->Bounds.GetSphere());
  } else {
    return true;
  }
}

bool UCesiumTile::PrimitiveBoxFullyContainsTileBounds(
    const UPrimitiveComponent* Other) const {
  if (IsValid(Other)) {
    return Bounds.GetBox().Intersect(Other->Bounds.GetBox()) ||
           Bounds.GetSphere().Intersects(Other->Bounds.GetSphere());
  } else {
    return true;
  }
}

FBoxSphereBounds UCesiumTile::CalcBounds(const FTransform& LocalToWorld) const {
  FBoxSphereBounds bounds = std::visit(
      CalcBoundsOperation{
          LocalToWorld * this->GetComponentTransform(),
          this->_tileTransform},
      _tileBounds);
  return bounds;
}
