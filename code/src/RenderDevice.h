#pragma once
#include "headers.h"

#define BUFFER_SIZE 4096
#define VAO_BUFFER_SIZE 1024

namespace RenderDevice
{

	// THIS ENGINE WILL HANDLE GL ONLY -- NO TIME TO SPEND ON MULTIPLE GFX APIS AT THE MOMENT	
	GLuint	vbo[BUFFER_SIZE];
	GLuint	ibo[BUFFER_SIZE];

	GLuint	vao[VAO_BUFFER_SIZE];



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



	VertexBufferHandle CreateVextexBuffer()
	{

	}

	void DestroyVertexBuffer(VertexBufferHandle handle)
	{
		
		handle.generation++;
	}

	IndexBufferHandle CreateIndexBuffer()
	{

	}


	VertexArrayObjHandle

}
