#include "platform.h"
#include "headers.h"

namespace core
{

	unsigned long Platform::GetTime()
	{
		return glfwGetTimerValue();
	}
}