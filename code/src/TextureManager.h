#ifndef _TextureManager_h_
#define _TextureManager_h_


#include <string>
#include <map>
#include <vector>
#include "Resources.h"


namespace resources
{

    struct tagTexture {};
    
    typedef Handle<tagTexture>	HTexture;

    class TextureManager
    {
    public:
        typedef HandleMgr<texture_t, HTexture> HTextureResourceManager;

        struct istring_less
        {
            bool operator() (const std::string& l, const std::string& r) const
            {
                return (strcmp(l.c_str(), r.c_str()) < 0);
            }
        };

        typedef std::map<std::string, HTexture, istring_less>	NameIndex;
        typedef std::pair<NameIndex::iterator, bool> NameIndexInsertRc;

    private:
        HTextureResourceManager mResourceManagerImpl;
        NameIndex mNameIndex;

    public:

        TextureManager() {};
        ~TextureManager();


        HTexture    GetTexture(const char* name, TextureType  type);
        void DeleteTexture(HTexture hTexture);

        const char* GetNme(HTexture res) const
        {
            return (mResourceManagerImpl.Dereference(res)->name);
        }


    };

}

#endif //_TextureManager_h_



