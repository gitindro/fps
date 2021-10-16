#include "Application.h"
#include "DebugUI.h"

namespace Application
{
		static void window_error_callback(int errorCode, const char* description)
        {

        }


		static void __internal_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{

		}

		static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) 
		{
			if (type == GL_DEBUG_TYPE_ERROR)
			{
				LOG_F(ERROR, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
					(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
					type, severity, message);
			}
			else
			{
				LOG_F(INFO, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
					(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
					type, severity, message);
			}
		}

		static void OnLog(void* user_data, const loguru::Message& message)
		{
			printf("[%s] %s %d %s", message.preamble, message.filename , message.line , message.message);
		}

		static GLFWwindow* CreateWindow(const WindowConfig& config)
		{
			loguru::add_file("core.log", loguru::Append, loguru::Verbosity_MAX);

			loguru::add_callback("engine_logger", OnLog, NULL, loguru::Verbosity_MAX);

			LOG_F(INFO, "App init --- Start of app");

			LOG_F(INFO, "Create Window");

			glfwSetErrorCallback([](int error, const char* desc)
				{
					window_error_callback(error, desc);
				});

			/* Initialize the library */
			if (!glfwInit())
			{
				LOG_F(ERROR, "Failed to initialize glfw app quiting");
				return NULL;
			}
				

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			/* Create a windowed mode window and its OpenGL context */
			GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL, NULL);

			__app_windows[windowsCount].window = window;
			if (!window)
			{
				glfwTerminate();
				LOG_F(ERROR, "glfwCreateWindow failed app quiting");
				return NULL;
			}

			LOG_F(INFO, "Created application window ", config.title);
			glfwSetKeyCallback(window, __internal_key_callback);

			/* Make the window's context current */
			glfwMakeContextCurrent(window);

			gladLoadGL(glfwGetProcAddress);

			glfwSwapInterval(1);
			// During init, enable debug output
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(MessageCallback, 0);

			++windowsCount;
		}


		static bool Initialize(const WindowConfig& config)
		{
			auto window = CreateWindow(config);

			DebugUI::init(window);
			
		}

        static void StartLoop()
        {
			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(__app_windows[0].window))
			{
				DebugUI::begin_frame();
				glfwGetFramebufferSize(__app_windows[0].window, &__app_windows[0].windowWidth, &__app_windows[0].windowHeight);

				glViewport(0, 0, __app_windows[0].windowWidth, __app_windows[0].windowHeight);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				DebugUI::end_frame();
				/* Swap front and back buffers */
				glfwSwapBuffers(__app_windows[0].window);

				DebugUI::end_frame();
				/* Poll for and process events */
				glfwPollEvents();
			}


			
        }

		static void Shutdown()
		{
			DebugUI::shutdown();

			for (size_t i = 0; i < Application::windowsCount; i++)
			{
				glfwDestroyWindow(Application::__app_windows[i].window);
			}
			
			glfwTerminate();
		}

}