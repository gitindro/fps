#ifndef _Plane_h_
#define _Plane_h_

#include "headers.h"


namespace core
{
    class Plane
    {
        private:
            glm::vec3 mNormal;
            glm::vec3   mPt1;
            glm::vec3   mPt2;
            glm::vec3   mPt3;

        public:

            // Point normal / Vector  form
            Plane(glm::vec3 point, glm::vec3 normal)
            {
                mPt1 = point;
                mNormal = normal;
            }

            // Three point form
            Plane(glm::vec3 pt1, glm::vec3 pt2, glm::vec3 pt3)
            {
                mPt1 = pt1;
                mPt2 = pt2;
                mPt3 = pt3;

                glm::vec3 edge1 = mPt1 - mPt2;
                glm::vec3 edge2 = mPt3 - mPt2;

                glm::vec normal = glm::cross(edge1, edge2);

                mNormal = glm::normalize(normal); 
            }


            bool InFront(const glm::vec3 point)
            {
                glm::vec3 point_dir = point - mPt1;

                float dot_res = glm::dot(point_dir, mNormal);

                if (dot_res < 0)
                {
                    return false;
                }
                

                return true;
            }    


    };
}
#endif //_Plane_h_