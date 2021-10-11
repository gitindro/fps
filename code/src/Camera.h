#ifndef     _Camera_h_
#define     _Camera_h_

#include "headers.h"

namespace core
{
    class Camera
    {
        private:
            glm::vec3 mPosition;
            glm::vec3 mRotation;
            glm::vec3 mScale;
            glm::mat4 mViewMatrix;
            glm::mat4 mProjectionMatrix;
        public:
            Camera(const float fov, const glm::vec3& poition,const glm::vec3& lookAt);
            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();    

            glm::vec3 getPosition();
    }
}

#endif //_Camera_h_