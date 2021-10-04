#include "resourcebase.h"
#include "headers.h"

namespace core
{
	bool iResourceBase::mbLogCreateAndDelete = false;

	//-----------------------------------------------------------------------
	iResourceBase::iResourceBase(const tString& asName, const tWString& asFullPath, unsigned long alPrio) {
		mlTime = (unsigned long)time(NULL);
		mlPrio = alPrio;
		mlHandle = 0;
		mlUserCount = 0;
		msName = asName;
		mbLogDestruction = false;
		msFullPath = asFullPath;
	}

	iResourceBase::~iResourceBase()
	{
		if (mbLogDestruction && mbLogCreateAndDelete)
			LOG_F(INFO, "  Destroyed resource '%s'\n", msName.c_str());
	}
	//-----------------------------------------------------------------------

	void iResourceBase::IncUserCount()
	{
		mlUserCount++;
		mlTime = (unsigned long)time(NULL);
	}

	//-----------------------------------------------------------------------

	void iResourceBase::SetFullPath(const tWString& asPath)
	{
		msFullPath = asPath;
	}

	//-----------------------------------------------------------------------
}