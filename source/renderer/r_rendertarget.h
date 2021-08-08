#pragma once

#include "GpuTexture.h"

class RenderTarget {
   public:
    enum { MAX_COLOR_ATTACHMENT = 4 };

    virtual void Create( int width, int height );
    void Bind();
    void Unbind();
    void Destroy();
    void CreateDepthAttachment();
    void CheckError();

    const GpuTexture& GetDepthTexture() const { return mDepthAttachment; }
    const GpuTexture& GetColorAttachment( int i ) const { return mColorAttachments[i]; }

    inline GLuint GetHandle() const { return mHandle; }

   protected:
    GLuint mHandle = 0;

    GpuTexture mDepthAttachment;
    GpuTexture mColorAttachments[MAX_COLOR_ATTACHMENT];
    int mColorAttachmentCount = 0;
    int mWidth                = 0;
    int mHeight               = 0;
};

class DepthRenderTarget : public RenderTarget {
   public:
    virtual void Create( int width, int height ) override;
};

class GBuffer : public RenderTarget {
   public:
    virtual void Create( int width, int height ) override;
};

class SSAOBuffer : public RenderTarget {
   public:
    virtual void Create( int width, int height ) override;
};

extern DepthRenderTarget g_shadowRT;
extern GBuffer g_gbufferRT;
extern SSAOBuffer g_ssaoRT;

void R_CreateRT();
void R_DestroyRT();