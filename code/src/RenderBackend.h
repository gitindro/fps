#pragma once
#include "headers.h"

#include "HandleManager.h"

using namespace pow2;

namespace gfx
{
	namespace backend
	{
		typedef
		struct trigroup
		{
			int vertex_count;
			glm::vec3*	position;
			glm::vec3*	normal;
			glm::vec3*	tangent;
			glm::vec3*	binormal;
			glm::vec3*	color; 			
		}trigroup_t;

		typedef
		struct mesh
		{
			Handle tri_grp;
			Handle vao;
			Handle vbo;
			Handle ibo;
		}mesh_t;

		enum GfxBufferType
		{
			VboHandle = 0,
			IboHandle = 1,
			VaoHandle = 2
		};

		enum  BufferUsage
		{
			STATIC_DRAW = GL_STATIC_DRAW,
			DYNAMIC_DRAW = GL_DYNAMIC_DRAW
		};
		
		HandleManager gfx_res_handle_mgr;
		
		struct GfxBufferHandleData
		{
			GLuint id;
			GfxBufferType type;
		};

		struct GfxTtriGroupData
		{
			trigroup_t* ptrTriGroup;	
		};

		typedef Handle BufferHandle;

		
		Handle CreateBuffer(GfxBufferType type); 
	
		void void BindVBOToVAO(Handle vaoHandle, Handle vboHandle, int index, size_t vertexSize, void* vertexData, BufferUsage usage);
		
		void BindIBOToVAO(Handle vaoHandle, Handle iboHandle,size_t indexSize, void* indexData, BufferUsage usage);
		
		void BindDrawBuffers(VertexArrayHandle vaoHandle, VertexBufferHandle handle, int vertexSize, void* vertices, int vboFlag,
														IndexBufferHandle iboHandle, int indexSize, void* indices, int iboFlag);


		void CreateMesh();

		void DrawMesh(mesh_t* ptrmesh, material_t* ptrMat);
		
	}
	
}

