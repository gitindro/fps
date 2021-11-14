#include "Resources.h"
#include "SOIL2.h"
#include "assim "
#include "HandleManager.h"
#include "physfs.h"

namespace resources
{
    pow2::HandleManager resourceHandleManager;

    

    //========================================= TextureResource ===============================================
    
    typedef 
    struct 
    {
        char        name[32];
        TextureType type;
        GLuint      glID;
        u32         width;
        u32         height;
        u32         pixelformat;
    }texture_t;


    GLuint texture_load2D(const char* filepath)
    {
        PHYSFS_file* filePtr =  PHYSFS_openRead(filepath);


        unsigned char* buffer;
        int size = PHYSFS_fileLength(filePtr);
        buffer = new unsigned char[size];
        int length_read = PHYSFS_read(filePtr, buffer, 1, size);

        if(length_read == 0)
        {
            LOG_F(ERROR, "failed to read  texture filepath %s ", filepath);
            return 0;
        }

        //int w, h, c; // widhth, height, channels

        //SOIL_load_image_from_memory(buffer, size, &w ,&h, &c, SOIL_LOAD_AUTO);

        GLuint id = SOIL_load_OGL_texture_from_memory(buffer, size, SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,
                                                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | 
                                                        SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);


        //GLuint id = SOIL_load_OGL_texture(filepath,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,
        //SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        
        
        if(0 == id)
        {
            LOG_F(ERROR, "failed to load texture filepath %s ", filepath);
            
            return 0;
        }

        int w, h;
        int miplevel = 0;

        Texture_t    tex;
        strcpy(&tex.name[0], filepath);
        tex.glID = id;
        
        //TODO:: get tex dimensions and format from soil

        resourceHandleManager.

        return id;
    }

    GLuint texture_loadNorma(const char* filepath)
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

    GLuint texture_loadcube(const char* filename)
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

    void    texture_unload(texture_t* tex)
    {
        glDeleteTextures(1, &(tex->glID));
        LOG_F(INFO, "unloaded texture %s", tex->name);
    }
    //===============================================================================

    //====================== Shader ==============================================
    enum ParamType
    {
        INTEGER,
        FLOAT,
        BOOL,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        MATRIX3X3,
        MATRIX4X4,

        TEXTURE,
        COLOR
    };

    typedef
    struct ShaderParameter
    {
        char        name[64]; //max supported uniform name char count is 64
        GLint       location;
        ParamType   type;

    }ShaderParameter_t;

    typedef
    struct Shader
    {
		char*		name;
        ShaderType  type;
        GLuint      glId;
        ShaderParameter   paramters[16];
    }Shader_t;

    Handle Shader_Load(const char* filepath, ShaderType type)
	{
		
        return true;
	}
	
	void Shader_Unload(Shader_t* shader)
    {
        
    }


    Handle  model_load(const char* filepath, bool tangent=true)
    {

    }


    void    model_unload(Handle meshHandle)
    {

    }
}