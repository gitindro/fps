#include "headers.h"

namespace core
{
	BoundingSphere::BoundingSphere()
	{
		mCenter = glm::vec3(0, 0, 0);
		mRadius = 0.0f;
	}

	BoundingSphere::BoundingSphere(BoundingSphere& sphere)
	{
		mCenter = sphere.mCenter;
		mRadius = sphere.mRadius;
	}

	void BoundingSphere::Calculate(glm::vec3* points, int numPoints)
	{

	}

	bool BoundingSphere::CheckCollision(glm::vec3& point)
	{

		return false;
	}

	bool BoundingSphere::CheckCollision(BoundingSphere& sphere)
	{
		return false;
	}

	bool BoundingSphere::CheckCollision(Aabb& aabb)
	{
		return false;
	}
}
