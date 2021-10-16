#ifndef _Application_h_
#define _Application_h_

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "headers.h"
#include "SystemTypes.h"

#define EDITOR 1

namespace Application
{
    #define MAX_WINDOWS 8


    typedef struct windata_tag
    {
        std::string         title;
        int                 windowWidth;
        int                 windowHeight;
        static GLFWwindow*     window;

    }WindowData;


    typedef struct
    {
        tString title;
        int width;
        int height;
        bool fullscreen;
    } WindowConfig;

    static WindowData __app_windows[MAX_WINDOWS];      // 0 - main window , closing 0 will close all
    static int windowsCount = 0;


    static int GetWindowWidth(int whichWindow = 0 ) {return __app_windows[whichWindow].windowWidth;} 
    static int GetWindowHeight(int whichWindow = 0 ) { return __app_windows[whichWindow].windowWidth; }

    static GLFWwindow* CreateWindow(const WindowConfig& config);

    static void __internal_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


    static bool Initialize(const WindowConfig& config);
    static void StartLoop();
    static void Shutdown();
   
}

#endif 