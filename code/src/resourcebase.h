#include "SystemTypes.h"


namespace core 
{

	class iResourceBase
	{
	public:
		
		iResourceBase(const tString& asName, const tWString& asFullPath,unsigned long alPrio);

		virtual ~iResourceBase();
				
		/**
		 * virtual bool Reload()=0; 
		 * \return true is reload was succesful, else false.
		 */
		virtual bool Reload()=0;

		/**
		 * Free most the memory, save info to get started again. 
		 */
		virtual void Unload()=0;

        /**
         * Free all memory.
         */
        virtual void Destroy()=0;

		const tString& GetName(){return msName;}
		unsigned long GetHandle(){return mlHandle;}
		void SetHandle(unsigned long alHandle){mlHandle=alHandle;}
		
		void SetFullPath(const tString& asPath);
		const tString& GetFullPath(){return msFullPath;}
		
		unsigned long GetTime(){return mlTime;}
		unsigned long GetPrio(){return mlPrio;}
		unsigned long GetSize(){return mlSize;}

		void SetLogDestruction(bool abX){ mbLogDestruction = abX;}
		
		unsigned int GetUserCount(){return mlUserCount;}
		void IncUserCount();
		void DecUserCount(){if(mlUserCount>0)mlUserCount--;}
		bool HasUsers(){ return mlUserCount>0;}

		static bool GetLogCreateAndDelete(){ return mbLogCreateAndDelete;}
		static void SetLogCreateAndDelete(bool abX){ mbLogCreateAndDelete = abX;}

	protected:
		static bool mbLogCreateAndDelete;
		
		tString msName;
		
		unsigned int mlPrio; //dunno if this will be of any use.
		unsigned long mlTime; //Time for creation.
		unsigned long mlSize; //for completion. Not used yet.
		
		unsigned int mlUserCount;
        unsigned long mlHandle;
		bool mbLogDestruction;
	
	private:
		tString msFullPath;
	};

};