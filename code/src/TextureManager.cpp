#include "TextureManager.h"
#include "SOIL2.h"


namespace resources
{

    //========================================= TextureResource ===============================================
    GLuint Texture_load2D(const char* filepath)
    {
        GLuint id = SOIL_load_OGL_texture(filepath,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        

        if(0 == id)
        {
            LOG_F(ERROR, "failed to load texture filepath %s ", filepath);
            
            return 0;
        }


        return id;
    }

    GLuint Texture_loadNorma(const char* filepath)
    {
        GLuint id = SOIL_load_OGL_texture(filepath,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        

        if(0 == id)
        {
            LOG_F(ERROR, "failed to load texture filepath %s ", filepath);
            
            return 0;
        }


        return id;
    }

    GLuint Texture_loadcube(const char* filename)
    {
        GLuint id = SOIL_load_OGL_single_cubemap
        (
            filename,
            "EWUDNS",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS
        );

        if(0 == id)
        {
            LOG_F(ERROR, "failed to load cube texture filepath %s ", filename);
            
            return 0;
        }


        return id;
    }

    void    Texture_unload(Texture_t* tex)
    {
        glDeleteTextures(1, &(tex->glID));
        LOG_F(INFO, "unloaded texture %s", tex->name);
    }

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
 