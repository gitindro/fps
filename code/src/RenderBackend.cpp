
#include "RenderDevice.h"

namespace gfx
{
	
	namespace RenderDevice
	{
		Handle CreateBuffer(GfxBufferType type); ()
		{
			GfxBufferHandleData hdata;

			glCreateBuffers(1, &(hdata.id));
			hdata.type = type; // store buffer type in handle

			Handle handle = gfx_res_handle_mgr.Add((void*)&hdata, static_cast<uint32>(type));

			return handle;
		}

		void DestroyVBO(Handle handle)
		{
			GfxBufferHandleData* hdata;
			void* out;
			bool retVal = gfx_res_handle_mgr.Get(handle, out);

			hdata = static_cast<GfxBufferHandleData*>(out);

			glDeleteBuffers(1, &hdata->id);

			gfx_res_handle_mgr.Remove(handle);
		}

		void BindVBOToVAO(Handle vaoHandle, Handle vboHandle, int index, size_t vertexSize, void* vertexData, BufferUsage usage)
		{
			GfxBufferHandleData* hdata;
			void* out;
			bool retVal = gfx_res_handle_mgr.Get(vaoHandle, out);

			if (retVal)
			{
				hdata = static_cast<GfxBufferHandleData*>(out);

		
				glBindVertexArray(hdata->id); // bind VAO
			
				gfx_res_handle_mgr.Get(vboHandle,out);
				hdata = static_cast<GfxBufferHandleData*>(out);
			
				glBindBuffer(GL_ARRAY_BUFFER, hdata->id);
				glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, (GLenum)usage);
		
				glBindVertexArray(0); // unbind vao
			}
				
		}
		
		void BindIBOToVAO(Handle vaoHandle, Handle iboHandle,size_t indexSize, void* indexData, BufferUsage usage)
		{
			GfxBufferHandleData* hdata;
			void* out;	

			if(gfx_res_handle_mgr.Get(vaoHandle, out))
			{
				hdata = static_cast<GfxBufferHandleData*>(out);
				glBindVertexArray(hdata->id); // bind VAO

				gfx_res_handle_mgr.Get(vboHandle,out);
				hdata = static_cast<GfxBufferHandleData*>(out);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hdata->id);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indexData, (GLenum)usage);

			}
		}

		void BindDrawBuffers(VertexArrayHandle vaoHandle, VertexBufferHandle handle, int vertexSize, void* vertices, int vboFlag,
														IndexBufferHandle iboHandle, int indexSize, void* indices, int iboFlag)
		{
			GfxBufferHandleData* hdata;
			void* out;
			bool retVal = gfx_res_handle_mgr.Get(vaoHandle, out);

			if (retVal)
			{
				hdata = static_cast<GfxBufferHandleData*>(out);
				glBindVertexArray(hdata->id); // bind VAO

				if(gfx_res_handle_mgr.Get(vboHandle,out))
				{
					gfx_res_handle_mgr.Get(vboHandle,out);
					hdata = static_cast<GfxBufferHandleData*>(out);
			
					glBindBuffer(GL_ARRAY_BUFFER, hdata->id);
					glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, (GLenum)usage);
				}

				if(gfx_res_handle_mgr.Get(iboHandle, out))
				{
					gfx_res_handle_mgr.Get(vboHandle,out);
					hdata = static_cast<GfxBufferHandleData*>(out);		

					glBindBuffer(GL_ARRAY_BUFFER, hdata->id);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices,(GLenum)usage);
				}



				glBindVertexArray(0); 
			}
		}
		
	}
}
