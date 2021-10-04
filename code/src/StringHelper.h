#ifndef _StringHelper_h_
#define _StringHelper_h_

#include "SystemTypes.h"

namespace core
{
	
	class  StringHelper
	{
	public:
		static unsigned int GetHash(const tString& asStr);

		//static unsigned int GetHashW(const tWString& asStr);



		static tString ToLowerCase(const tString& aString);
	};


}

#endif //_StringHelper_h_