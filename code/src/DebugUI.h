#ifndef _DebugUI_h_
#define _DebugUI_h_

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace DebugUI
{

    void init(GLFWwindow* window);


    void begin_frame();


    void render_frame();


    void end_frame();


    void shutdown();

} 

#endif //_DebugUI_h_