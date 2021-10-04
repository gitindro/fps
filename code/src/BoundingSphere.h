#ifndef _BounndingSphere_h_
#define _BounndingSphere_h_



namespace core
{
	class Aabb;

	class BoundingSphere
	{
	public:
		BoundingSphere();
		BoundingSphere(BoundingSphere& sphere);

		void Calculate(glm::vec3* points, int numPoints);
		bool CheckCollision(glm::vec3& point);

		bool CheckCollision(BoundingSphere& sphere);
		bool CheckCollision(Aabb& aabb);

	private:
		glm::vec3 mCenter;
		float mRadius;
	};


}




#endif //_BounndingSphere_h_
