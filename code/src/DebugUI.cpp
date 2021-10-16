#include "DebugUI.h"
#include "DebugConsole.h"
namespace DebugUI
{
    const char* glsl_version = "#version 130";
    DebugConsole console;
    bool console_open = true;


    void OnLog(void* user_data, const loguru::Message& message)
    {
        //printf("[%s] %s %d %s", message.preamble, message.filename, message.line, message.message);

        console.AddLog("[%s] %s %d %s", message.preamble, message.indentation, message.line, message.message);
    }

    void init(GLFWwindow* window)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        loguru::add_callback("console_logger", OnLog, NULL, loguru::Verbosity_MAX);

    }




    void begin_frame()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void render_frame()
    {
        console.Draw("console", &console_open);
        ImGui::Render();
    } 


    void end_frame()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }  
}