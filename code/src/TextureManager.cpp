#include "TextureManager.h"



namespace resources
{


    //==========================================================================================================

    TextureManager::~TextureManager()
    {
        //Unload all res->textures
        NameIndex::iterator i, begin = mNameIndex.begin(), end = mNameIndex.end();

        for (i = begin; i != end; i++)
        {
            HTexture hs = i->second;
            Texture_t* pTexRes = mResourceManagerImpl.Dereference(hs);
            Texture_unload(pTexRes);
        }
    }

    HTexture TextureManager::GetTexture(const char* name, TextureType type)
    {
        NameIndexInsertRc rc = mNameIndex.insert(std::make_pair(name, HTexture()));
        if (rc.second)
        {
            Texture_t* tex = mResourceManagerImpl.Aquire(rc.first->second);
            GLuint  ret = 0;
            if(type == TextureType::Texture_2D)
            {
                ret = Texture_load2D(tex->name);     
            }
            else if(type == TextureType::Texture_Cube)
            {
                ret = Texture_loadcube(tex->name);     
            }
            else if(type == TextureType::Texture_Cube)
            {
                ret = Texture_load2D(tex->name);     
            }
            if (0 != ret)
            {
                DeleteTexture(rc.first->second);
                rc.first->second = HTexture();
            }
        }

        return rc.first->second;
    }

    void TextureManager::DeleteTexture(HTexture htex)
    {
        Texture_t* tex = mResourceManagerImpl.Dereference(htex);
        if (NULL != tex)
        {
            mNameIndex.erase( mNameIndex.find(tex->name) );
            Texture_unload(tex);
            mResourceManagerImpl.Release(htex);
        }
    }
}
 