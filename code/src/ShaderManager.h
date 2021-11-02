#pragma once

#include "Resources.h"
#include <glm/glm.hpp> 
#include <string>
#include <map>
#include <vector>
#include <glm/gtc/matrix_transform.hpp> 

namespace resources
{


	
	bool Shader_Load(const char* filepath, ShaderType type);
	void Shader_Unload();

	class  ShaderResourceManager
	{
	public:



		typedef HandleMgr<Shader_t, HShader> HShaderResourceManager;



		struct istring_less
		{
			bool operator() (const tString& l, const tString& r) const
			{
				return (strcmp(l.c_str(), r.c_str()) < 0);
			}
		};

		typedef std::map< tString, HShader, istring_less>	NameIndex;
		typedef std::pair<NameIndex::iterator, bool> NameIndexInsertRc;

	private:
		HShaderResourceManager	mResourceManagerImpl;
		NameIndex mNameIndex;

	public:
		ShaderResourceManager() {}
		~ShaderResourceManager();

		HShader GetShader(const tString& name, ShaderType shaderType);
		void DeleteShader(HShader hShader);
		 
		const char* GetName(HShader res) const
		{
			return (mResourceManagerImpl.Dereference(res)->name);
		}

		const ShaderType  GetType(HShader res) const
		{
			return (mResourceManagerImpl.Dereference(res)->type);
		}
	};

}
