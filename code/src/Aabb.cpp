#include "Aabb.h"


namespace core
{
	AABB::AABB()
	{
		mMin = glm::vec3(INFINITY, INFINITY, INFINITY);
		mMax = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
	}


	AABB::AABB(AABB& aabb)
	{
		mMin = aabb.mMin;
		mMax = aabb.mMax;
		mCenter = aabb.mCenter;
		mCachedSize = aabb.mCachedSize;
	}


	void AABB::Calculate(glm::vec3* points, int numPoints)
	{
		for (size_t i = 0; i < numPoints; i++)
		{

			// Find min x y z 
			if (mMin.x > points[i].x)
			{
				mMin.x = points[i].x;
			}

			if (mMin.y > points[i].y)
			{
				mMin.y = points[i].y;
			}

			if (mMin.z > points[i].z)
			{
				mMin.z = points[i].z;
			}


			// Find max x y z
			if (mMax.x < points[i].x)
			{
				mMax.x = points[i].x;
			}
			if (mMax.y < points[i].y)
			{
				mMax.y = points[i].y;
			}
			if (mMax.z < points[i].z)
			{
				mMax.z = points[i].z;
			}

		}
	}


	void AABB::Expand(float amount)
	{
		mMax += glm::vec3(amount, amount, amount);
		mMin -= glm::vec3(amount, amount, amount);
	}

	void AABB::Translate(glm::vec3& delta)
	{
		mMax += delta;
		mMin += delta;
		mCenter += delta;
	}

	bool  AABB::CollisionCheck(glm::vec3& point)
	{
		if (mMax.x <= point.x) return false;
		if (mMax.y <= point.y) return false;
		if (mMax.z <= point.z) return false;

		if (mMin.x >= point.x) return false;
		if (mMin.y >= point.y) return false;
		if (mMin.z >= point.z) return false;

		return true;
	}

	bool AABB::CollisionCheck(AABB& aabb)
	{
		glm::vec3 a(aabb.mMin.x, aabb.mMax.y, aabb.mMin.z);
		glm::vec3 b(aabb.mMax.x, aabb.mMax.y, aabb.mMin.z);
		glm::vec3 c(aabb.mMax.x, aabb.mMin.y, aabb.mMin.z);
		glm::vec3 d(aabb.mMin.x, aabb.mMin.y, aabb.mMax.z);
		glm::vec3 e(aabb.mMin.x, aabb.mMax.y, aabb.mMax.z);
		glm::vec3 f(aabb.mMax.x, aabb.mMin.y, aabb.mMax.z);



		if (CollisionCheck(aabb.mMin))
		{
			return true;
		}
		if (CollisionCheck(aabb.mMax))
		{
			return true;
		}

		if (CollisionCheck(a))
		{
			return true;
		}
		if (CollisionCheck(b))
		{
			return true;
		}
		if (CollisionCheck(c))
		{
			return true;
		}
		if (CollisionCheck(d))
		{
			return true;
		}
		if (CollisionCheck(e))
		{
			return true;
		}
		if (CollisionCheck(f))
		{
			return true;
		}


		return false;
	}
}
