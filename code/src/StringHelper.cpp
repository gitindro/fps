#include "StringHelper.h"


namespace core
{
	//-----------------------------------------------------------------------

	//ALGO FROM: http://www.azillionmonkeys.com/qed/lHash.html
	// by Paul Hsieh

#define Get16Bits(data) (*((const wchar_t *) (data)))

	unsigned int StringHelper::GetHash(const tString& asStr)
	{
		unsigned int lLen = (unsigned int)asStr.size();
		const char* pData = asStr.c_str();
		unsigned int lHash = lLen, lTemp;
		int lRem;

		if (asStr.empty()) return 0;

		lRem = lLen & 3;
		lLen >>= 2;

		//////////////////////////////////
		//Main loop
		for (; lLen > 0; lLen--)
		{
			lHash += Get16Bits(pData);
			lTemp = (Get16Bits(pData + 2) << 11) ^ lHash;
			lHash = (lHash << 16) ^ lTemp;
			pData += 2 * sizeof(wchar_t);
			lHash += lHash >> 11;
		}

		//////////////////////////////////
		// Handle end cases
		switch (lRem)
		{
		case 3:
			lHash += Get16Bits(pData);
			lHash ^= lHash << 16;
			lHash ^= pData[sizeof(wchar_t)] << 18;
			lHash += lHash >> 11;
			break;
		case 2:
			lHash += Get16Bits(pData);
			lHash ^= lHash << 11;
			lHash += lHash >> 17;
			break;
		case 1:
			lHash += *pData;
			lHash ^= lHash << 10;
			lHash += lHash >> 1;
		}

		//////////////////////////////////
		// Force "avalanching" of final 127 bits
		lHash ^= lHash << 3;
		lHash += lHash >> 5;
		lHash ^= lHash << 4;
		lHash += lHash >> 17;
		lHash ^= lHash << 25;
		lHash += lHash >> 6;

		return lHash;
	}

	//-----------------------------------------------------------------------

	//unsigned int StringHelper::GetHashW(const tWString& asStr)
	//{
	//	unsigned int lLen = (unsigned int)asStr.size();
	//	const wchar_t* pData = asStr.c_str();
	//	unsigned int lHash = lLen, lTemp;
	//	int lRem;

	//	if (asStr.empty()) return 0;

	//	lRem = lLen & 1;
	//	lLen >>= 1;

	//	//////////////////////////////////
	//	//Main loop
	//	for (; lLen > 0; lLen--)
	//	{
	//		lHash += pData[0];
	//		lTemp = (pData[1] << 11) ^ lHash;
	//		lHash = (lHash << 16) ^ lTemp;
	//		pData += 2;
	//		lHash += lHash >> 11;
	//	}

	//	//////////////////////////////////
	//	// Handle end cases
	//	if (lRem)
	//	{
	//		lHash += *pData;
	//		lHash ^= lHash << 10;
	//		lHash += lHash >> 1;
	//	}

	//	//////////////////////////////////
	//	// Force "avalanching" of final 127 bits
	//	lHash ^= lHash << 3;
	//	lHash += lHash >> 5;
	//	lHash ^= lHash << 4;
	//	lHash += lHash >> 17;
	//	lHash ^= lHash << 25;
	//	lHash += lHash >> 6;

	//	return lHash;
	//}

	//-----------------------------------------------------------------------

	tString StringHelper::ToLowerCase(const tString& aString)
	{
		tString sTemp;
		sTemp.resize(aString.size());
		for (int i = 0; i < (int)aString.size(); i++)
		{
			sTemp[i] = tolower(aString[i]);
		}
		return sTemp;
	}
}