#ifndef  _BoundingBox_h_
#define _BoundingBox_h_

#include "headers.h"
namespace core
{
	class  AABB
	{
	public:
		 AABB();
		 AABB(AABB& aabb);

		 void Calculate(glm::vec3* points, int numPoints);
		 void Expand(float amount);

		 void Translate(glm::vec3& delta);

		 bool CollisionCheck(glm::vec3& point);
		 bool CollisionCheck(AABB& aabb);
		 
;

	private:
		glm::vec3	mMin;
		glm::vec3	mMax;
		glm::vec3	mCenter;
		glm::vec3	mCachedSize;
	};

}
#endif // ! _BoundingBox_h_

