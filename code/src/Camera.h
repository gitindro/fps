#ifndef     _Camera_h_
#define     _Camera_h_

#include "headers.h"

namespace core
{
    class Camera
    {
        private:

            ICameraController&   mController;
        public:
            Camera(const ICameraController& controller);

            glm::mat4 getViewMatrix()
            {
                return mController.getViewMatrix();
            }

            glm::mat4 getProjectionMatrix()
            {
                return mController.getProjectionMatrix();
            }

            glm::vec3 getPosition()
            {
                return mController.getPosition();
            }

    };
}

#endif //_Camera_h_