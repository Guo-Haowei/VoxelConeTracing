#pragma once
#include <glad/glad.h>

#include <string>
#include <vector>

#include "GpuTexture.h"

#include "Base/Logger.h"
#include "Core/GeomMath.hpp"

#include "cbuffer.shader.hpp"

static constexpr int kMaxShaderName = 128;

struct MaterialData {
    GpuTexture albedoMap;
    GpuTexture materialMap;
    GpuTexture normalMap;
    vec4 albedoColor;
    float metallic;
    float roughness;
    float reflectPower;
    int textureMapIdx;
};

void R_CreateQuad();
void R_DrawQuad();

namespace gl {

template<typename T>
void NamedBufferStorage( GLuint buffer, const std::vector<T>& data )
{
    glNamedBufferStorage( buffer, sizeof( T ) * data.size(), data.data(), 0 );
}

static inline void BindToSlot( GLuint buffer, int slot, int size )
{
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glVertexAttribPointer( slot, size, GL_FLOAT, GL_FALSE, size * sizeof( float ), 0 );
    glEnableVertexAttribArray( slot );
}

//------------------------------------------------------------------------------
// Constant Buffer
//------------------------------------------------------------------------------

GLuint CreateAndBindConstantBuffer( int slot, size_t sizeInByte );
void UpdateConstantBuffer( GLuint handle, const void* ptr, size_t sizeInByte );

template<typename T>
struct ConstantBuffer {
    void Destroy()
    {
        if ( mHandle != 0 ) {
            LOG_DEBUG( "[opengl] destroy cbuffer %u", mHandle );
            glDeleteBuffers( 1, &mHandle );
        }
        mHandle = 0;
    }

    void CreateAndBind( int slot )
    {
        mHandle = CreateAndBindConstantBuffer( slot, sizeof( T ) );
    }

    void Update()
    {
        UpdateConstantBuffer( mHandle, &cache, sizeof( T ) );
    }

    T cache;
    GLuint mHandle = 0;
};

static inline GLuint64 MakeTextureResident( GLuint texture )
{
    GLuint64 ret = glGetTextureHandleARB( texture );
    glMakeTextureHandleResidentARB( ret );
    return ret;
}

}  // namespace gl
