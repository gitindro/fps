
#include "engine.h"



int main()
{


	core::EngineConfig config;

    config.name = "demo";
    config.fullscreen = 0;
    config.openglVersionMajor = 4;
    config.openglVersionMinor = 0;
    config.targetFps = 30;
    config.window_width = 1024;
    config.window_height = 768;

    config.fixedTimedelta = 0.02f;


    
    core::Engine engine;

    if (!engine.init(config))
    {
        printf("failed to init engine");
        exit(EXIT_FAILURE);
    }
   

    engine.run();

    return 0;
}