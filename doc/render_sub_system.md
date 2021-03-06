
https://blog.molecular-matters.com/2014/11/13/stateless-layered-multi-threaded-rendering-part-2-stateless-api-design/
https://blog.molecular-matters.com/2014/12/16/stateless-layered-multi-threaded-rendering-part-3-api-design-details/




# RENDER DEVICE
	Abstraction for low-level api and any other common functionality	






	

# RENDER CONTEXT
	Dispatchfuntion
	{
	  KeyValuePair (COMMAND_TYPE, (*function))	
	}

	Bucket
	{
		camera - 
		matrix - view proj
		render target
		sort  - back_to_front , front_to_back,
		Command Buffer/List 
		
		function
			sort the list
	}


	Sets device state 
	submit commands to Buckets  (One bucket for meshes / shaodow / ui / post fx)
	

# COMMAND BUFFER / LIST
Commands
{
   COMMAND_TYPE - draw / clear / set param / 
}

example -

namespace commands
{
  struct Draw
  {
    uint32_t vertexCount;
    uint32_t startVertex;
 
    VertexLayoutHandle vertexLayoutHandle;
    VertexBufferHandle vertexBuffer;
    IndexBufferHandle indexBuffer;
  };
 
  struct DrawIndexed
  {
    uint32_t indexCount;
    uint32_t startIndex;
    uint32_t baseVertex;
 
    VertexLayoutHandle vertexLayoutHandle;
    VertexBufferHandle vertexBuffer;
    IndexBufferHandle indexBuffer;
  };
 
  struct CopyConstantBufferData
  {
    ConstantBufferHandle constantBuffer;
    void* data;
    uint32_t size;
  };
}


template <typename U>
U* CommandBucket::AddCommand(Key key)
{
  U* data = AllocateCommand<U>();
 
  // store key and pointer to the data
  AddKey(key);
  AddData(data);
 
  return data;
}

 rendering mesh component in a deffered renderer so the gBuffer Bucket

for (size_t i=0; i < meshComponents.size(); ++i)
{
  MeshComponent* mesh = &meshComponents[i];
 
  commands::DrawIndexed* dc = gBuffer.AddCommand<commands::DrawIndexed>(GenerateKey(mesh->aabb, mesh->material));
  dc->vertexLayoutHandle = mesh->vertexLayout;
  dc->vertexBuffer = mesh->vertexBuffer;
  dc->indexBuffer = mesh->indexBuffer;
  dc->indexCount = mesh->indexCount;
  dc->startIndex = 0u;
  dc->baseVertex = 0u;
}


/// AFTER ALL BUCKET ARE FILLED WITH DATA 

sort all the buckets , which will sort internally backt to front or front to back based
on value of its sort type variable
gBufferBucket.Sort();
lightingBucket.Sort();
deferredBucket.Sort();
postProcessingBucket.Sort();
hudBucket.Sort();


For sorting the commands in the bucket, we can use whatever sorting algorithm we want. 
The one thing to note here is that each CommandBucket::Sort() can be run on a different thread, 
sorting all buckets in parallel.

after all buckets are sorted , we can submit them. submit should be done 
from one thread- main thread or main rendering thread

gBufferBucket.Submit();
lightingBucket.Submit();
deferredBucket.Submit();
postProcessingBucket.Submit();
hudBucket.Submit();



We can submit like this 

----------- naive submit 

void Submit(void)
{
  SetViewMatrix();
  SetProjectionMatrix();
  SetRenderTargets();
 
  for (unsigned int i=0; i < commandCount; ++i)
  {
    Key key = m_keys[i];
    void* data = m_data[i];
    uint16_t id = m_ids[i];
 
    // decode the key, and set shaders, textures, constants, etc. if the material has changed.
    DecodeKey();
 
    switch (id)
    {
      case command::Draw::ID:
        // extract data for a Draw command, and call the backend
        break;
 
      case command::DrawIndexed::ID:
        // extract data for a DrawIndexed command, and call the backend
        break;
 
      ...;
    }
  }
}

---------------------------

but there is better solition then running this switch or if 
i.e function pointer

these dispatch functions forwards the call to the RENDER DEVICE

namespace backendDispatch
{
  void Draw(const void* data)
  {
    const commands::Draw* realData = union_cast<const commands::Draw*>(data);
    RenderDevice::Draw(realData->vertexCount, realData->startVertex);
  }
 
  void DrawIndexed(const void* data)
  {
    const commands::DrawIndexed* realData = union_cast<const commands::DrawIndexed*>(data);
    RenderDevice::DrawIndexed(realData->indexCount, realData->startIndex, realData->baseVertex);
}
 
  void CopyConstantBufferData(const void* data)
  {
    const commands::CopyConstantBufferData* realData = union_cast<const commands::CopyConstantBufferData*>(data);
    RenderDevice::CopyConstantBufferData(realData->constantBuffer, realData->data, realData->size);
  }
}

Each function in the backend dispatch has the same signature, 
hence we can use a typedef to store a pointer to any of those functions:


typedef void (*BackendDispatchFunction)(const void*);


The functions contained in the RenderDevice namespace are still the only 
ones that talk directly to the graphics API, opengl in our case.




CommandPacket 
	pointer to next packet if any
	Actual Command
	Dispatch function for Actual Command
	aux memory

# with command packet AddCommand looks like this now

template <typename U>
U* AddCommand(Key key, size_t auxMemorySize)
{
  CommandPacket packet = commandPacket::Create<U>(auxMemorySize);
 
  // store key and pointer to the data
  {
    // TODO: add some kind of lock or atomic operation here
    const unsigned int current = m_current++;
    m_keys[current] = key;
    m_packets[current] = packet;
  }
 
  commandPacket::StoreNextCommandPacket(packet, nullptr);
  commandPacket::StoreBackendDispatchFunction(packet, U::DISPATCH_FUNCTION);
 
  return commandPacket::GetCommand<U>(packet);
}

# this is and example of Draw command with static(all draw cmds will use the same 
# RenderDevice::Draw function) dispatch function 

struct Draw
{
  static const BackendDispatchFunction DISPATCH_FUNCTION;
 
  uint32_t vertexCount;
  uint32_t startVertex;
 
  VertexLayoutHandle vertexLayoutHandle;
  VertexBufferHandle vertexBuffer;
  IndexBufferHandle indexBuffer;
};
static_assert(std::is_pod<Draw>::value == true, "Draw must be a POD.");
 
const BackendDispatchFunction Draw::DISPATCH_FUNCTION = &backendDispatch::Draw;




# adding new command to existing command buffer
template <typename U, typename V>
U* AppendCommand(V* command, size_t auxMemorySize)
{
  CommandPacket packet = commandPacket::Create<U>(auxMemorySize);
 
  // append this command to the given one
  commandPacket::StoreNextCommandPacket<V>(command, packet);
 
  commandPacket::StoreNextCommandPacket(packet, nullptr);
  commandPacket::StoreBackendDispatchFunction(packet, U::DISPATCH_FUNCTION);
 
  return commandPacket::GetCommand<U>(packet);
}


# New submit with Command packet in place 

void Submit(void)
{
  // ... same as before
  for (unsigned int i=0; i < m_current; ++i)
  {
    // ... same as before
    CommandPacket packet = m_packets[i];
    do
    {
      SubmitPacket(packet);
      packet = commandPacket::LoadNextCommandPacket(packet);
    } while (packet != nullptr);
  }
}
 
void SubmitPacket(const CommandPacket packet)
{
  const BackendDispatchFunction function = commandPacket::LoadBackendDispatchFunction(packet);
  const void* command = commandPacket::LoadCommand(packet);
  function(command);
}



List / Buffer / RingBUffer of Commands -- CommandBuffer
CommandBuffer --- Buffer with commands in it
	Uses RenderDevice
	


# RENDERER 
	Double-buffer all dynamic resources.
	Forward / Forward+
	RenerQueue / Layer 
	Culling
	Material
	LOD
	Shadow
	Scene Graph
	Transform Graph
	LazyLoading
	Animation
	Camera
	PostFX
	SSAO
	.... this list grows 





	
	