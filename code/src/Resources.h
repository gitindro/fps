#ifndef _Resource_h_
#define _Resource_h_


#include "headers.h"
#include "HandleResManager.h"
#include "physfs.h"



namespace resources
{
	
	bool Resources_Init();
    void Resources_Shutdown();

	
    enum ResourceType
    {
        Resource_None,
        Resource_Texture,
        Resource_Shader,
        Resource_Model,
        Resource_Xml,
        Resource_Max
    };

    //=======================================================================






    
    //=========================================================================
    // Resource types

    enum TextureType
    {
        Texture_2D,
        Texture_Cube,
        Texture_Normal,
    };

    typedef 
    struct 
    {
        char*       name;
        TextureType type;
        GLuint      glID;
        u32         width;
        u32         height;
        u32         pixelformat;
    }Texture_t;

    struct tagTexture
    {
        const char* type = "texture";
    };
    typedef Handle<tagTexture>  HTexture;


    enum ShaderType
    {
        Shader_Vertex,
        Shader_Fragment,
        Shader_Geometry,
    };

    typedef
    struct Shader
    {
		char*		name;
        ShaderType  type;
        GLuint      glId;
    }Shader_t;
    
    
    struct  tagShader
	{
		const char* type = "shader";
	};
	typedef Handle< tagShader> HShader;


    typedef
    struct Material
    {
        HTexture    albedoTexture;
        HTexture    specularTexture;
        HTexture    NormalTexture;
        

    }Material_t;
    
    struct  tagMaterial
	{
		const char* type = "material";
	};
	typedef Handle< tagMaterial> HMaterial;
}

#endif //_Resource_h_
