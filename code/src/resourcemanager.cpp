
#include "StringHelper.h"
#include "headers.h"
#include <algorithm>


namespace core
{
	//////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

	iResourceManager::iResourceManager()
	{
		//mpFileSearcher = apFileSearcher;
		//mpLowLevelResources = apLowLevelResources;
		//mpLowLevelSystem = apLowLevelSystem;
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	iResourceBase* iResourceManager::GetResource(const tString& asFullPath)
	{
		unsigned int lHash = StringHelper::GetHash(asFullPath);

		tResourceBaseMapIt it = m_mapResources.find(lHash);
		if (it == m_mapResources.end())return NULL;

		size_t lCount = m_mapResources.count(lHash);
		for (size_t i = 0; i < lCount; ++i, ++it)
		{
			iResourceBase* pResource = it->second;

			if (pResource->GetFullPath() == asFullPath) return pResource;
		}

		return NULL;
	}

	//-----------------------------------------------------------------------

	cResourceBaseIterator iResourceManager::GetResourceBaseIterator()
	{
		return m_mapResources.begin();
	}

	//-----------------------------------------------------------------------

	class cSortResources
	{
	public:
		bool operator()(iResourceBase* apResourceA, iResourceBase* apResourceB)
		{
			if (apResourceA->GetUserCount() != apResourceB->GetUserCount())
			{
				return apResourceA->GetUserCount() > apResourceB->GetUserCount();
			}

			return apResourceA->GetTime() > apResourceB->GetTime();
		}
	};

	//-----------------------------------------------------------------------

	void iResourceManager::DestroyUnused(int alMaxToKeep)
	{
		//Log("Start Num Of: %d\n",m_mapHandleResources.size());
		//Check if there are too many resources.
		if ((int)m_mapResources.size() <= alMaxToKeep) return;

		//Add resources to a vector
		std::vector<iResourceBase*> vResources;
		vResources.reserve(m_mapResources.size());

		tResourceBaseMapIt it = m_mapResources.begin();
		for (; it != m_mapResources.end(); ++it)
		{
			vResources.push_back(it->second);
		}

		//Sort the sounds according to num of users and then time.
		std::sort(vResources.begin(), vResources.end(), cSortResources());

		//Log("-------------Num: %d-----------------\n",vResources.size());
		for (size_t i = alMaxToKeep; i < vResources.size(); ++i)
		{
			iResourceBase* pRes = vResources[i];
			//Log("%s count:%d time:%d\n",pRes->GetName().c_str(), 
			//							pRes->GetUserCount(), 
			//							pRes->GetTime());

			if (pRes->HasUsers() == false)
			{
				RemoveResource(pRes);
				coreDelete(pRes);
			}
		}
		//Log("--------------------------------------\n");
		//Log("End Num Of: %d\n",m_mapHandleResources.size());

	}

	//-----------------------------------------------------------------------

	void iResourceManager::DestroyAll()
	{
		tResourceBaseMapIt it = m_mapResources.begin();
		while (it != m_mapResources.end())
		{
			//Log("Start destroy...");

			iResourceBase* pResource = it->second;

			//Log(" res: %d ...", pResource);
			//Log(" res: '%s' / '%s': %d ...",pResource->GetName().c_str(), cString::To8Char(pResource->GetFullPath()).c_str(),pResource->GetUserCount());

			while (pResource->HasUsers()) pResource->DecUserCount();

			Destroy(pResource);

			it = m_mapResources.begin();

			//Log(" Done!\n");
		}
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PROTECTED METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	void iResourceManager::BeginLoad(const tString& asFile)
	{
		mlTimeStart = Platform::GetTime();

		//Log("Begin resource: %s\n",asFile.c_str());

		mlTabCount++;
	}

	//-----------------------------------------------------------------------

	void iResourceManager::EndLoad()
	{
		mlTabCount--;
	}

	//-----------------------------------------------------------------------

	iResourceBase* iResourceManager::FindLoadedResource(const tString& asName, tString& asFilePath, int* apEqualCount)
	{
		//asFilePath = mpFileSearcher->GetFilePath(asName, apEqualCount);

		iResourceBase* pResource = GetResource(asFilePath);
		if (pResource != NULL)
		{
			asFilePath = "";
		}

		return pResource;
	}

	//-----------------------------------------------------------------------

	tString iResourceManager::GetTabs()
	{
		tString sTabs = "";
		for (int i = 0; i < mlTabCount; ++i) sTabs += "  ";
		return sTabs;
	}

	void iResourceManager::AddResource(iResourceBase* apResource, bool abLog, bool abAddToSet)
	{
		tString sName = StringHelper::ToLowerCase(apResource->GetName());

		if (abAddToSet)
		{
			int lHash = StringHelper::GetHash(apResource->GetFullPath());
			m_mapResources.insert(tResourceBaseMap::value_type(lHash, apResource));
		}

		//Log("Adding %d, '%s' hash: %u\n",apResource,cString::To8Char(apResource->GetFullPath()).c_str(), lHash);

		if (abLog && iResourceBase::GetLogCreateAndDelete())
		{
			unsigned long lTime = Platform::GetTime() - mlTimeStart;

			LOG_F(INFO, "%sLoaded resource %s in %d ms\n", GetTabs().c_str(), apResource->GetName().c_str(), lTime);

			apResource->SetLogDestruction(true);
		}

		//Log("End resource: %s\n",apResource->GetName().c_str());
	}

	//-----------------------------------------------------------------------

	void iResourceManager::RemoveResource(iResourceBase* apResource)
	{
		//Log("Removing resource name: '%s' path: '%s' ", apResource->GetName().c_str(), cString::To8Char(apResource->GetFullPath()).c_str());

		unsigned int lHash = StringHelper::GetHash(apResource->GetFullPath());

		tResourceBaseMapIt it = m_mapResources.find(lHash);
		if (it == m_mapResources.end())
		{
			//Log("%d was not removed! '%s' Hash: %u\n", apResource, cString::To8Char(apResource->GetFullPath()).c_str(),lHash);

			//Log("...not found!\n");
			return;
		}

		size_t lCount = m_mapResources.count(lHash);
		for (size_t i = 0; i < lCount; ++i, ++it)
		{
			iResourceBase* pResource = it->second;

			if (pResource == apResource)
			{
				//Log("...done!\n");
				m_mapResources.erase(it);
				return;
			}
		}
	}

	//-----------------------------------------------------------------------
}