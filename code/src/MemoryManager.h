#ifndef _MemoryManager_h_ 
#define _MemoryManager_h_ 


#ifdef MEMORY_MANAGER_ACTIVE

#define coreNew(classType, constructor) \
			( classType *)hpl::cMemoryManager::AddPointer(hpl::cAllocatedPointer(new classType constructor ,__FILE__,__LINE__,sizeof(classType)))

#define coreNewNewArray(classType, amount) \
			( classType *) hpl::cMemoryManager::AddPointer(hpl::cAllocatedPointer(new classType [ amount ] ,__FILE__,__LINE__,amount * sizeof(classType)))

#define coreMalloc(amount) \
			hpl::cMemoryManager::AddPointer(hpl::cAllocatedPointer(malloc( amount ) ,__FILE__,__LINE__,amount))

#define coreRealloc(data, amount) \
		hpl::cMemoryManager::UpdatePointer(data, hpl::cAllocatedPointer(realloc( data, amount ) ,__FILE__,__LINE__,amount))


#define coreDelete(data){ \
			hpl::cMemoryManager::RemovePointer(hpl::cMemoryManager::DeleteAndReturn(data),__FILE__,__LINE__); \
			}//delete data;


#define coreDeleteArray(data){ \
			hpl::cMemoryManager::RemovePointer(hpl::cMemoryManager::DeleteArrayAndReturn(data),__FILE__,__LINE__); \
			}//delete [] data;

#define coreFree(data){ \
			hpl::cMemoryManager::RemovePointer(hpl::cMemoryManager::FreeAndReturn(data),__FILE__,__LINE__); \
			}//free(data);


#else
#define coreNew(classType, constructor) \
			new classType constructor 

#define coreNewArray(classType, amount) \
			new classType [ amount ] 

#define coreMalloc(amount) \
			malloc( amount )

#define coreRealloc(data, amount) \
			realloc( data, amount )

#define coreDelete(data) \
		delete data;

#define coreDeleteArray(data) \
		delete [] data;

#define coreFree(data) \
		free(data);

#endif

#endif // ! _MemoryManager_h_

