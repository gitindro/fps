#include "engine.h"

namespace core
{
    Engine::~Engine()
    {

    }
		
    bool Engine::init(const EngineConfig& config,int argc, char* argv[])
    {
         // 1st init logger 
         loguru::init(argc, argv);   
         loguru::add_file("game.log", loguru::Append, loguru::Verbosity_MAX);
         LOG_SCOPE_F(INFO, "Engine: Initialized log system..");

         glfwSetErrorCallback([](int error, const char* desc) {
            LOG_SCOPE_F(ERROR, "Engine error: %d : %s", error, desc);
        });
        
        /* Initialize the library */
        if (!glfwInit())
        {
            return false;
        }
        
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.openglVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.openglVersionMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWmonitor* monitor = NULL;
        if(config.fullscreen)
        {
            monitor = glfwGetPrimaryMonitor();
        }
        /* Create a windowed mode window and its OpenGL context */
        mWindow = glfwCreateWindow(config.window_width, config.window_height, config.name, monitor, NULL);
        if (!mWindow)
        {
            glfwTerminate();
            return false;
        }

    }
		
        
    void Engine::update(float elapsedtime)
    {

    }

		// start the game loop
    bool Engine::run()
    {
        LOG_F(INFO, "Engine run main loop");
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(mWindow))
        {
            double now = glfwGetTime();
            float delta = (now - mPreviousTime);
            mPreviousTime = now;

            // --> Update called every frame is fps dependent 
            // elapsed time is passed for user to write frame independent code
            update(delta);  


            if(delta >= 0.25f) 
                delta = 0.25f;

            mAccumulator += delta;

            while (mAccumulator >= mFixedDeltaTime)
            {
                // fixed update called fixed times in as frame
                fixedUpdate(mFixedDeltaTime);

                mAccumulator -= mFixedDeltaTime;
            }

            float alpha = mAccumulator / mFixedDeltaTime;

            // called every frame with alpha value for user code to do any sort of interpolation
            render(alpha) ;
     

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
		
        
    void Engine::render(float alpha)
    {
        glfwGetFramebufferSize(mWindow, &mWindowWidth, &mWindowHeight);

        glViewport(0, 0, mWindowWidth, mWindowHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* Swap front and back buffers */
        glfwSwapBuffers(mWindow);
    }
		
        
    void Engine::fixedUpdate(float fixedtimedelta)
    {

    }
	
    void Engine::shutdown()
    {

        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

}