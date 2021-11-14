#ifndef _Resource_h_
#define _Resource_h_


#include "headers.h"
#include "HandleResManager.h"




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
    struct texture_t;
    struct shaderparameter_t;
    struct shader_t;
    struct material_t;
    struct model_t;




    
    //=========================================================================
    // Resource types

    enum TextureType
    {
        Texture_2D,
        Texture_Cube,
        Texture_Normal,
    };


    GLuint  Texture_load2d(const char* filename);
    
    GLuint Texture_loadcube(const char* filename);
    
    GLuint Texture_loadNorma(const char* filename);

    void    Texture_unload(GLuint id);

    enum ShaderType
    {
        Shader_Vertex,
        Shader_Fragment,
        Shader_Geometry,
    };

    
    bool Shader_Load(shader_t* ptrShader, const char* filepath, ShaderType type);
	void Shader_unload(shader_t* shader);
    
    
    void Shader_setparam(shader_t* shader, shaderparameter_t param, int value);
    void Shader_setparam(shader_t* shader, shaderparameter_t param, float value);
    void Shader_setparam(shader_t* shader, shaderparameter_t param, glm::vec2 value);
    void Shader_setparam(shader_t* shader, shaderparameter_t param, glm::vec3 value);
    void Shader_setparam(shader_t* shader, shaderparameter_t param, glm::vec4 value);
    void Shader_setparam(shader_t* shader, shaderparameter_t param, glm::mat3 value);
    void Shader_setparam(shader_t* shader, shaderparameter_t param, glm::mat4 value);

    void Shader_setparam(shader_t* shader, shaderparameter_t param, GLuint texture);

    union ShaderParamValue
    {
        int         integer;
        float       real;
        bool        boolean;
        glm::vec2   float2;
        glm::vec3   float3;
        glm::vec4   float4;

        Check out render e code
    };


    typedef
    struct material
    {        
        HShader  shader;

        // list of params name/location and their vlues
        std::map<GLint, int> 
    }material_t;
    

    material_t* material_load();


    typedef 
    struct model
    {
        char    name[256];
        //list if mesh/sub-mesh group of triangles that can be drawn in one draw call
        std::vector<Handle> tri_groups;     // data read from file
        std::vector<Handle> meshes;         // mesh created using render backend 
        std::vector<Handle> materials       // meterial created 

    }model_t;


    model_t*  model_load(const char* filepath, bool tangent=true);
    void    model_unload(model_t* ptrModel);


    TextureManager              g_textureManager;
    ShaderResourceManager       g_shaderResourceManager;
    ModelResourceManager        g_modelResourceManager;
}

//

#endif //_Resource_h_
