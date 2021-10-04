#ifndef _Engine_h_
#define _Engine_h_

#include "headers.h"

namespace core
{
	typedef struct
	{
		char*	name;
		int		window_width;
		int		window_height;
		bool	fullscreen;
		int 	openglVersionMinor;
		int 	openglVersionMajor;
		int 	targetFps;
		float	fixedTimedelta;
	} EngineConfig;

	class Engine
	{
		private:
			GLFWwindow* mWindow;
			int			mWindowWidth;
			int 		mWindowHeight;
			int			mTargetFps;
			int			mFullScreen;
			float		mElapsedTimeDelta;
			float		mElaspsedFixedTimeDelta;
			float		mPreviousTime;
			float		mAccumulator;
			int			mUpdatesPerSecond;
			float		mFixedDeltaTime;

			Engine(){}


		public:
		
		~Engine();
		
		bool init(const EngineConfig& config, int argc, char* argv[]);
		void update(float elapsedtime);

		// start the game loop
		bool run();
		void render(float alpha);
		void fixedUpdate(float fixedtimedelta);
		void shutdown();

	};
}

#endif _Engine_h_