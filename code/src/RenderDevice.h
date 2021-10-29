#pragma once
#include "headers.h"

#include "HandleManager.h"
//#define BUFFER_SIZE 4096
//#define VAO_BUFFER_SIZE 1024
using namespace pow2;

namespace gfx
{
	namespace RenderDevice
	{
		/*
		// THIS ENGINE WILL HANDLE GL ONLY -- NO TIME TO SPEND ON MULTIPLE GFX APIS AT THE MOMENT	
		GLuint	vbo[BUFFER_SIZE];
		GLuint	vbo_generation[BUFFER_SIZE];
		unsigned	free_vbo[VAO_BUFFER_SIZE]




		GLuint	ibo[BUFFER_SIZE];
		GLuint	ibo_generation[BUFFER_SIZE];
		unsigned	free[VAO_BUFFER_SIZE]

		GLuint	vao[VAO_BUFFER_SIZE];
		GLuint	vao_generation[BUFFER_SIZE];
		unsigned	free[VAO_BUFFER_SIZE]
		
		struct BufferId
		{
			GLuint	glID;

		}


		template <size_t N1, size_t N2>
		struct GenericHandle
		{
			// uint16_t or uint32_t, depending on build type, realized using preprocessor-#ifs
			uint32_t index : N1;
			uint32_t generation : N2;
		};

		typedef GenericHandle<12, 20> VertexBufferHandle;
		typedef GenericHandle<12, 20> IndexBufferHandle;
		typedef GenericHandle<12, 20> VertexArrayObjHandle;
		*/
		
		enum HandleTypes
		{
			VboHandle = 0,
			IboHandle = 1,
			VaoHandle = 2
		};


		typedef struct 
		{
			
		}vbo;
		
		typedef struct 
		{

		}ibo;

		typedef struct 
		{

		}vao;

		
		HandleManager vbo_handle_mgr;

		HandleManager ibo_handle_mgr;

		HandleManager vao_handle_mgr;


		
		struct HandleData
		{
			GLuint id;
		};

		typedef Handle VertexBufferHandle;
		typedef Handle IndexBufferHandle;
		typedef Handle VertexArrayHandle;

		Handle CreateVBO();

		void DestroyVBO(VertexBufferHandle handle);

		IndexBufferHandle CreateIBO();

		void DestroyIBO(IndexBufferHandle handle);

		VertexArrayHandle CreateVAO();

		void DestroyVAO(VertexArrayHandle handle);
	
	}
	
}

