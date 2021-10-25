#pragma once
#include "RenderDevice.h"

namespace gfx
{
	
	namespace RenderDevice
	{
		VertexBufferHandle CreateVBO()
		{
			HandleData hdata;

			glCreateBuffers(1, &(hdata.id));

			auto handle = vbo_handle_mgr.Add(&hdata, HandleTypes::VboHandle);

			return handle;
		}

		void DestroyVBO(VertexBufferHandle handle)
		{
			HandleData* hdata;
			void* out;
			bool retVal = vbo_handle_mgr.Get(handle, out);

			hdata = static_cast<HandleData*>(out);

			glDeleteBuffers(1, &hdata->id);

			vbo_handle_mgr.Remove(handle);
		}
	}
}