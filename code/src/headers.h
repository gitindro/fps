
#ifndef _Headers_h_
#define _Headers_h_


#include <stdio.h>
#include <stdlib.h>


//-----------------------------------------------------------------------------
// opengl and glfw headers
//-----------------------------------------------------------------------------
#include <glad/gl.h>
#include <GLFW/glfw3.h>

//-----------------------------------------------------------------------------
// Common math headers
//-----------------------------------------------------------------------------
#include <glm/glm.hpp>
#include <glm/ext.hpp>


#include "loguru.hpp"
#include "MemoryManager.h"
#include "platform.h"
#include "resourcebase.h"
#include "resourcemanager.h"
#include "Aabb.h"
#include "BoundingSphere.h"

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#define SAFE_DELETE( p )       { if( p ) { delete ( p );     ( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p );   ( p ) = NULL; } }
#define SAFE_RELEASE( p )      { if( p ) { ( p )->Release(); ( p ) = NULL; } }



#endif