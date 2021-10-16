#ifndef _CameraController_h_
#define _CameraController_h_

#include "headers.h"
namespace core
{
    class ICameraController
    {
        public:
            virtual ~ICameraController() = default;

            virtual glm::mat4 getViewMatrix() = 0;

            virtual glm::mat4 getProjectionMatrix() = 0;

            virtual glm::vec3 getPosition() = 0 ;

            virtual void Update() = 0;
    };
}

#endif //_CameraController_h_