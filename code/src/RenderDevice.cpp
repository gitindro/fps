#pragma once
#include "RenderDevice.h"

namespace gfx
{
	
	namespace RenderDevice
	{
		Handle CreateVBO()
		{
			HandleData hdata;

			glCreateBuffers(1, &(hdata.id));

			Handle handle = vbo_handle_mgr.Add((void*)&hdata, static_cast<uint32>(HandleTypes::VboHandle));

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