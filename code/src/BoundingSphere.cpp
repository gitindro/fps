#include "headers.h"

namespace core
{
	BoundingSphere::BoundingSphere()
	{
		mCenter = glm::vec3(0, 0, 0);
		mRadius = 0f;
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

	}

	bool BoundingSphere::CheckCollision(BoundingSphere& sphere)
	{

	}

	bool BoundingSphere::CheckCollision(Aabb& aabb)
	{

	}
}
