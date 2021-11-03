#include "Resources.h"
#include "ShaderManager.h"

namespace resources
{
	bool Shader_Load(const char* filepath, ShaderType type)
	{
		
        return true;
	}
	
	void Shader_Unload(Shader_t* shader)
    {
        
    }
	
	/*
	bool ShaderResourceManager::ShaderResource::Load(const str& name, kinc_g4_shader_type_t type)
	{
        kinc_file_reader_t file;
        
        bool ret_value = kinc_file_reader_open(&file, name.c_str(), KINC_FILE_TYPE_ASSET);

        if (!ret_value)
        {
            kinc_log(kinc_log_level_t::KINC_LOG_LEVEL_ERROR, "Error: %s %s", "failed to open file", name.c_str());
            return false;
        }

        size_t data_size = kinc_file_reader_size(&file);

        if (data_size <= 0)
        {
            kinc_log(kinc_log_level_t::KINC_LOG_LEVEL_ERROR, "Error: %s %s", "opened file has not content", name.c_str());
            return false;
        }

        uint8_t* data = (uint8_t*)(g_ResourceLoadMemoryPool.Allocate(data_size));
        kinc_file_reader_read(&file, data, data_size);
        kinc_file_reader_close(&file);
        kinc_g4_shader_init(&(this->mResoure), data, data_size, type);

        g_ResourceLoadMemoryPool.Free(data);

        return true;
	}

    void ShaderResourceManager::ShaderResource::UnLoad()
    {
        kinc_g4_shader_destroy(&(this->mResoure));
    }
    */

    ShaderResourceManager::~ShaderResourceManager()
    {
        NameIndex::iterator i, begin = mNameIndex.begin(), end = mNameIndex.end();

        for (i = begin; i != end; i++)
        {
            HShader hs = i->second;
            Shader_t* pShaderRes = mResourceManagerImpl.Dereference(hs);
            Shader_Unload(pShaderRes);
        }

    }


    HShader ShaderResourceManager::GetShader(const tString& name, ShaderType shaderType)
    {
        std::pair<const char*, HShader> a = std::make_pair(name, HShader());

        NameIndexInsertRc rc = mNameIndex.insert(a);

        if (rc.second)
        {
            Shader_t* sh = mResourceManagerImpl.Aquire(rc.first->second);
            if (! Shader_Load(sh, name, shaderType))
            {
                DeleteShader(rc.first->second);
                rc.first->second = HShader();
            }
        }
        
        return rc.first->second;
    }

    void ShaderResourceManager::DeleteShader(HShader hShader)
    {
        Shader_t* tex = mResourceManagerImpl.Dereference(hShader);
        if (NULL != tex)
        {
            mNameIndex.erase(mNameIndex.find(tex->name));
            Shader_Unload(tex);
            mResourceManagerImpl.Release(hShader);
        }
    }


}
