#pragma once

// Implementation of 
// Scott bilas - Generic handle based resource manager;
//https://web.archive.org/web/20090426074540/http://www.drizzle.com/~scottb/publish/gpgems1_resourcemgr.htm
#include "SystemTypes.h"
#include <vector>
#include "ppk_assert.h"
#include <map>

namespace resources
{
	template <typename TAG> class  Handle
	{
		union
		{
			enum
			{
				MAX_BITS_INDEX = 16,
				MAX_BITS_MAGIC = 16,

				MAX_INDEX = (1 << MAX_BITS_INDEX) - 1,
				MAX_MAGIC = (1 << MAX_BITS_MAGIC) - 1,
			};

			struct
			{
				u32 m_Index : MAX_BITS_INDEX; //INDEX INTO RESOURCE ARRAY/VECTOR

				u32 m_Magic : MAX_BITS_MAGIC; //MAGIC NUMBER TO CHECK
			};

			u32 m_Handle;
		};


	public:
		Handle(void) : m_Handle(0) {}

		void Init(u32 index);

		u32				GetIndex()		const { return m_Index; }
		u32				GetMagic()		const { return m_Magic; }
		u32				GetHandle()		const { return m_Handle; }
		bool			IsNull()		const { return !m_Handle; }

		operator u32(void)		const { return m_Handle; }

		template <typename TAG>
		inline bool operator != (Handle<TAG> r)
		{
			return (this.GetHandle() != r.GetHandle());
		}

		template <typename TAG>
		inline bool operator == (Handle<TAG> r)
		{
			return (this->GetHandle() == r.GetHandle());
		}
	};


	template <typename DATA, typename HANDLE>
	class  HandleMgr
	{
	private:
		typedef std::vector<DATA>	UserVec;
		typedef std::vector<u32> MagicVec;
		typedef std::vector<u32> FreeVec;

		//Private data
		UserVec		m_UserData;
		MagicVec	m_MagicNumbers;
		FreeVec		m_FreeSlots;

	public:
		HandleMgr() {}
		~HandleMgr() {}

		DATA* Aquire(HANDLE& handle);
		void	Release(HANDLE handle);

		DATA* Dereference(HANDLE handle);
		const DATA* Dereference(HANDLE handle) const;

		unsigned int GetUsedHandleCount() const
		{
			return m_MagicNumbers.size() - m_FreeSlots.size();
		}

		bool HasUsedHandles() const
		{
			return (!GetUsedHandleCount());
		}

	};

	// ---------------------------- Handle implementation-------------------------------------------------
	template <typename TAG>
	void Handle <TAG> ::Init(u32 index)
	{
		PPK_ASSERT(IsNull());
		PPK_ASSERT(index <= MAX_INDEX);

		static u32  s_AutoMagic = 0;
		if (++s_AutoMagic > MAX_MAGIC)
		{
			s_AutoMagic = 1; // 0 USED FOR NULL HANDLES
		}

		m_Index = index;
		m_Magic = s_AutoMagic;
	}


	//
	// ---------------------------- HandleMgr implementation-------------------------------------------------
	template<typename DATA, typename HANDLE>
	DATA* HandleMgr<DATA, HANDLE>::Aquire(HANDLE& handle)
	{
		u32 index;

		if (m_FreeSlots.empty())
		{
			index = static_cast<u32>( m_MagicNumbers.size());
			handle.Init(index);
			m_UserData.push_back(DATA());
			m_MagicNumbers.push_back(handle.GetMagic());
		}
		else
		{
			index = m_FreeSlots.back();
			handle.Init(index);
			m_FreeSlots.pop_back();
			m_MagicNumbers[index] = handle.GetMagic();
		}

		return  &(m_UserData[index]);
	}

	template<typename DATA, typename HANDLE>
	void HandleMgr<DATA, HANDLE>::Release(HANDLE handle)
	{
		u32 index = handle.GetIndex();

		PPK_ASSERT(index < m_UserData.size());
		PPK_ASSERT(m_MagicNumbers[index] == handle.GetMagic());

		//remove now
		m_MagicNumbers[index] = 0;
		m_FreeSlots.push_back(index);
	}

	template<typename DATA, typename HANDLE>
	inline DATA* HandleMgr<DATA, HANDLE>::Dereference(HANDLE handle)
	{
		if (handle.IsNull()) return 0;

		u32 index = handle.GetIndex();

		if (index >= m_UserData.size() || m_MagicNumbers[index] != handle.GetMagic())
		{
			PPK_ASSERT(0);
			return (0);
		}

		return  &(m_UserData[index]);
	}

	template<typename DATA, typename HANDLE>
	inline const DATA* HandleMgr<DATA, HANDLE>::Dereference(HANDLE handle) const
	{
		typedef HandleMgr<DATA, HANDLE> ThisType;

		return (const_cast<ThisType*>(this)->Dereference(handle));
	}

	

}
